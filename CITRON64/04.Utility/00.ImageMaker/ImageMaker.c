#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define BYTESOFSECTOR 512

int copyFile( int iSourceFd, int iTargetFd );
int adjustInSectorSize( int iFd, int iSourceSize );
void writeKernelInformation( int iTargetFd, int iKernelSectorCount );

int main(int argc, char* argv[])
{
    int iSourceFd;
    int iTargetFd;
    int iBooLoaderSize;
    int iKernel32SectorCount;
    int iSourceSize;

    if( argc < 3)
    {
        fprintf(stderr, "[ERROR] ImageMaker Bootloader.bin Kernel32.bin\n");
        exit( -1 );
    }

    if( ( iTargetFd = open( "Disk.img", 02 /*O_RDWR*/ | 0100 /*O_CREAT*/ | 01000 /*O_TRUNC*/ /* | O_BINARY*/, __S_IREAD | __S_IWRITE ) ) == -1 )
    {
        fprintf(stderr, "[ERROR] Disk.img open fail.\n"); 
        exit( -1 );
    }


    //----------------------
    // 부트로더파일을 열어서 모든 내용을 디스크 이미지 파일로 복사
    //----------------------
    printf("[INFO] Copy boot loader to image file\n");
    if( ( iSourceFd = open( argv[ 1 ], O_RDONLY /*| O_BINARY*/ ) ) == -1 )
    {
        fprintf(stderr, "[ERROR] %s open fail.\n", argv[ 1 ]);
        exit( -1 );
    }
    iSourceSize = copyFile( iSourceFd, iTargetFd );
    close( iSourceFd );
    iKernel32SectorCount = adjustInSectorSize( iTargetFd, iSourceSize );
    printf("[INFO] %s size = [%d] and sector count = [%d]\n",
            argv[ 1 ], iSourceSize, iKernel32SectorCount );
    
    //----------------------
    // 부트로더파일을 열어서 모든 내용을 디스크 이미지 파일로 복사
    //----------------------
    printf("[INFO] Copy protected mode kernel to image file\n");
    if( ( iSourceFd = open( argv[ 2 ], O_RDONLY /*| O_BINARY*/ ) ) == -1 )
    {
        fprintf(stderr, "[ERROR] %s open fail.\n", argv[ 2 ]);
        exit( -1 );
    }
    iSourceSize = copyFile( iSourceFd, iTargetFd );
    close( iSourceFd );
    iKernel32SectorCount = adjustInSectorSize( iTargetFd, iSourceSize );
    printf("[INFO] %s size = [%d] and sector count = [%d]\n",
            argv[ 2 ], iSourceSize, iKernel32SectorCount );


    //----------------------
    // 디스크 이미지에 커널 정보를 갱신
    //----------------------
    printf("[INFO] Start to write kernel information\n");
    writeKernelInformation( iTargetFd, iKernel32SectorCount );
    printf("[INFO] Image file create complete\n");

    close( iTargetFd );
    return 0;
}

int copyFile( int iSourceFd, int iTargetFd)
{
    int iSourceFileSize;
    int iRead;
    int iWrite;
    char vcBuffer[ BYTESOFSECTOR ];

    iSourceFileSize = 0;
    while( 1 ){
        iRead = read( iSourceFd, vcBuffer, sizeof( vcBuffer) );
        iWrite = write( iTargetFd, vcBuffer, iRead );
        
        if( iRead != iWrite )
        {
            fprintf( stderr, "[ERROR] iRead != iWrite.. \n");
            exit(-1);
        }
        iSourceFileSize += iRead;

        if( iRead != sizeof( vcBuffer ))
        {
            break;
        }
    }
    return iSourceFileSize;
}

int adjustInSectorSize( int iFd, int iSourceSize )
{
    int i;
    int iAdjustSizeToSector;
    char cCh;
    int iSectorCount;

    iAdjustSizeToSector = iSourceSize % BYTESOFSECTOR;
    cCh = 0x00;

    if( iAdjustSizeToSector )
    {
        iAdjustSizeToSector = 512 - iAdjustSizeToSector;
        printf("[INFO] File size [%lu] and fill [%u] byte \n", iSourceSize, iAdjustSizeToSector );
        for( i = 0; i< iAdjustSizeToSector ; i++)
        {
            write( iFd, &cCh, 1);
        }
    }
    else
    {
        printf("[INFO] File size is aligned 512 byte\n");
    }

    iSectorCount = ( iSourceSize + iAdjustSizeToSector ) / BYTESOFSECTOR;
    return iSectorCount;
}

void writeKernelInformation( int iTargetFd, int iKernelSectorCount )
{
    unsigned short usData;
    long lPosition;

    lPosition = lseek( iTargetFd, (off_t)5, SEEK_SET );
    if( lPosition == -1 )
    {
        fprintf( stderr, "lseek fail. Reurn value = %ld, errorno = %d, %d\n",
                lPosition, errno, SEEK_SET );
        exit( -1 );
    }

    usData = ( unsigned short ) iKernelSectorCount;
    write( iTargetFd, &usData, 2);

    printf("[INFO] Total sector count except boot loader [%d]\n",
            iKernelSectorCount );
}
