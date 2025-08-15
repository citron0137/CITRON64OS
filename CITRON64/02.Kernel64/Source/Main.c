#include "Types.h"
#include "Keyboard.h"
#include "Descriptor.h"

void kPrintString( int iX, int iY, const char* pcString );
void kPrintStringWithCheckBox( int iY, const char* pcString );
void kFillCheckBox( int iY, const char* pcString );

void Main( void ){
    kFillCheckBox( 10, "Pass" );

    char vcTemp[2] = {0,};
    BYTE bFlags, bTemp;
    int i =0;

    kPrintStringWithCheckBox( 11, "GDT Initailize And Switch For IA-32e Mode" );
    kInitializeGDTTableAndTSS();
    kLoadGDTR( (QWORD) GDTR_STARTADDRESS );
    kFillCheckBox( 11, "Pass" );

    kPrintStringWithCheckBox( 12, "TSS Segment Load" );
    kLoadTR( GDT_TSSSEGMENT );
    kFillCheckBox( 12, "Pass" );

    kPrintStringWithCheckBox( 13, "IDT Initailize And Switch For IA-32e Mode" );
    kInitializeIDTTables();
    kLoadIDTR( (QWORD) IDTR_STARTADDRESS );
    kFillCheckBox( 13, "Pass" );

    kPrintStringWithCheckBox( 14, "Keyboard Activate" );
    if(kActivateKeyboard() == TRUE){
        kFillCheckBox(14, "Pass");
        kChangeKeyboardLED(FALSE, FALSE, FALSE);
    }
    else{
        kFillCheckBox(14, "Fail");
        while(1);
    }

    while(1){
        if(kIsOutputBufferFull() == TRUE){
            bTemp = kGetKeyboardScanCode();
            if(kConvertScanCodeToASCIICode(bTemp, &(vcTemp[0]), &bFlags)==TRUE)
                if(bFlags & KEY_FLAGS_DOWN){
                    kPrintString(i++, 15, vcTemp);
                    if( vcTemp[0] == '0' ){
                        bTemp = bTemp / 0;
                    }
                }
        }
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
