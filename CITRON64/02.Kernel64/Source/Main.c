#include "Types.h"
#include "Keyboard.h"

void kPrintString( int iX, int iY, const char* pcString );
void kPrintStringWithCheckBox( int iY, const char* pcString );
void kFillCheckBox( int iY, const char* pcString );

void Main( void ){
    kFillCheckBox( 10, "Pass" );
    kPrintStringWithCheckBox(11, "Activate Keyboard");
    if(kActivateKeyboard() == TRUE){
        kFillCheckBox(11, "Pass");
        kChangeKeyboardLED(FALSE, FALSE, FALSE);
    }
    else{
        kFillCheckBox(11, "Fail");
        while(1);
    }

    char vcTemp[2] = {0,};
    BYTE bFlags, bTemp;
    int i =0;
    while(1){
        if(kIsOutputBufferFull() == TRUE){
            bTemp = kGetKeyboardScanCode();
            if(kConvertScanCodeToASCIICode(bTemp, &(vcTemp[0]), &bFlags)==TRUE)
                if(bFlags & KEY_FLAGS_DOWN)
                    kPrintString(i++, 12, vcTemp);
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
