#include "Types.h"
#include "Page.h"
#include "ModeSwitch.h"

void kPrintString( int iX, int iY, const char* pcString );
BOOL kInitializeKernel64Area(void);
BOOL kIsMemoryEnough(void);
void kCopyKernel64ImageTo2Mbyte(void);

void Main( void ){
    DWORD i;
    DWORD dwEAX, dwEBX, dwECX, dwEDX;
    char vcVendorString[13]={0,};

    kPrintString(0, 3, "Protected Mod C Lang Kernel Started...................[Pass]");
    kPrintString(0, 4, "Minimum Memory Size Check.............................[    ]");
    if(kIsMemoryEnough() == FALSE){
        kPrintString(55, 4, "Fail");
        kPrintString(0, 5, "Not Enough Memory ( Citron64 OS Requires Over 64Mbyte Memory )");
        while(1);        
    }
    kPrintString(55, 4, "Pass");
    
    
    kPrintString(0, 5, "IA-32e Kernel Area Initialization.....................[    ]");
    if(kInitializeKernel64Area() == FALSE){
        kPrintString(55, 5, "Fail");
        kPrintString(0, 6, "Kernel Area Initialization Fail");
        while(1);        
    }
    kPrintString(55, 5, "Pass");
    
    kPrintString(0, 6, "IA-32e Page Tables Initialize.........................[    ]");
    kInitializePageTables();
    kPrintString(55, 6, "Pass");

    kReadCPUID(0x00, &dwEAX, &dwEBX, &dwECX, &dwEDX);
    *(DWORD *) vcVendorString = dwEBX;
    *((DWORD *) vcVendorString+1) = dwEDX;
    *((DWORD *) vcVendorString+2) = dwECX;
    kPrintString(0, 7, "Processor Vendor String...............................[            ]");
    kPrintString(55, 7, vcVendorString);

    kReadCPUID(0x80000001, &dwEAX, &dwEBX, &dwECX, &dwEDX);
    kPrintString(0, 8, "64bit Mode Support Check..............................[    ]");
    if(dwEDX & (1 << 29)){
        kPrintString(55, 8, "Pass");
    }
    else{
        kPrintString(55, 8, "Fail");
        kPrintString(0, 9, "This Processor does not support 64bit mode");
        while(1);
    }

    kPrintString(0, 9, "Copy IA-32e Kernel To 2M address......................[    ]");
    kCopyKernel64ImageTo2Mbyte();
    kPrintString(55, 9, "Pass");

    kPrintString(0, 10, "Switch To IA-32e Mode.................................[    ]");
    kSwitchAndExecute64bitKernel();
    kPrintString(55, 10, "Fail");
    while(1);
    
}

void kPrintString(int iX, int iY, const char * pcString ){
    CHARACTER *pstScreen = (CHARACTER *) 0xB8000;
    int i;
    pstScreen += (iY * 80)+iX;
    for(i = 0; pcString[i]!=0; i++){
        pstScreen[i].bCharactor = pcString[i];
    } 
}

BOOL kInitializeKernel64Area(void){
    DWORD *pdwCurrentAddress;
    
    pdwCurrentAddress = (DWORD *) 0x100000;

    while((DWORD)pdwCurrentAddress < 0x600000){
        *pdwCurrentAddress = 0x00;

        if(*pdwCurrentAddress != 0x00){
            return FALSE;
        }
        pdwCurrentAddress++;
    }
    return TRUE;
}

BOOL kIsMemoryEnough(void){
    DWORD *pdwCurrentAddress;
    pdwCurrentAddress = (DWORD *)0x100000;

    while((DWORD)pdwCurrentAddress < 0x4000000 ){
        *pdwCurrentAddress = 0x12345678;
        if(*pdwCurrentAddress != 0x12345678){
            return FALSE;
        }
        pdwCurrentAddress+=(0x100000/4);
    }
    return TRUE;
}

void kCopyKernel64ImageTo2Mbyte(void){
    WORD wKernel32SectorCount, wTotalKernelSectorCount;
    DWORD *pdwSourceAddress, *pdwDestinationAddress;
    int i;

    wTotalKernelSectorCount = *( (WORD *)0x7C05);    // 총 커널 섹터 수
    wKernel32SectorCount = *( (WORD *)0x7C07);       // 보호보드 커널 섹터 수 

    pdwSourceAddress = (DWORD *)(0x10000 + (wKernel32SectorCount*512));
    pdwDestinationAddress = (DWORD *)0x200000;

    for(i=0;i<512*(wTotalKernelSectorCount - wKernel32SectorCount)/4;i++){
        *pdwDestinationAddress = *pdwSourceAddress;
        pdwDestinationAddress++;
        pdwSourceAddress++;
    }
}