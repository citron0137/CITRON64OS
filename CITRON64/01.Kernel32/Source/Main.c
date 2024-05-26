#include "Types.h"

void kPrintString( int iX, int iY, const char* pcString );
void kPrintStringWithCheckBox( int iY, const char* pcString );
void kFillCheckBox( int iY, const char* pcString );
BOOL kInitializeKernel64Area( void );
BOOL kIsMemoryEnough( void );

void Main( void ){
    DWORD i;

    kPrintStringWithCheckBox( 3, "Start C Kernel" );
    kFillCheckBox( 3, "PASS" );
    
    kPrintStringWithCheckBox( 4, "Check minimum memory size" );
    if(kIsMemoryEnough() == FALSE){
        kFillCheckBox( 4, "Fail" );
        kPrintString( 0, 5, "NotEnoughMemory ( > 64Mb )" );
        while( 1 );
    }
    else{
        kFillCheckBox( 4, "Pass" );
    }

    kPrintStringWithCheckBox( 5, "Initialize IA-32e Kernel Area" );
    kInitializeKernel64Area();
    if(kInitializeKernel64Area() == FALSE){
        kFillCheckBox( 5, "FAIL" );
        kPrintString( 0, 6, "Failed to initialize IA-32e Kernel Area" );
        while( 1 );
    }
    else{
        kFillCheckBox( 5, "PASS" );
    }
    
    while(1);
}

void kPrintString( int iX, int iY, const char* pcString ){
    CHARACTER* pstScreen = ( CHARACTER* ) 0xB8000; 
    pstScreen += ( iY * 80 ) + iX;
    for( int i = 0; pcString[i] != 0; i++ )
    {
        pstScreen[ i ].bCharactor = pcString[ i ];
    }
}
void kPrintStringWithCheckBox( int iY, const char* pcString ){
    kPrintString( 0, iY, "............................................[    ]"); 
    kPrintString( 0, iY, pcString );
}

void kFillCheckBox( int iY, const char* pcString ){
    kPrintString( 45, iY, pcString );
}

BOOL kInitializeKernel64Area( void ){
    DWORD* pdwCurrentAddress;
    pdwCurrentAddress = ( DWORD* ) 0x100000;
    while( pdwCurrentAddress <= ( DWORD* ) 0x600000 ){
        *pdwCurrentAddress = 0x00;
        if( *pdwCurrentAddress != 0 ) return FALSE;
        pdwCurrentAddress++;
    }
    return TRUE;
}

BOOL kIsMemoryEnough( void ){
    DWORD* pdwCurrentAddress = ( DWORD* ) 0x100000;
    while( pdwCurrentAddress <= ( DWORD* ) 0x400000 ){
        *pdwCurrentAddress = 0x12345678;
        if( *pdwCurrentAddress != 0x12345678 ) return FALSE;
        pdwCurrentAddress += ( 0x100000 / 4 );
    }
    return TRUE;
}