#include "Types.h"
#include "stdio.h"
#include "Keyboard.h"
#include "Descriptor.h"
#include "PIC.h"

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

    kPrintStringWithCheckBox( 13, "IDT Initailize" );
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

    kPrintStringWithCheckBox( 15, "PIC Controller And Interrupt Enable" );
    kInitializePIC();
    kMaskPICInterrupt( 0 );  // 0x0002 비트만 0으로 설정 (IRQ1 활성화)
    kEnableInterrupt();
    kFillCheckBox( 15, "Pass" );

    while(1){
        if(kIsOutputBufferFull() == TRUE){
            bTemp = kGetKeyboardScanCode();
            if(kConvertScanCodeToASCIICode(bTemp, &(vcTemp[0]), &bFlags)==TRUE)
                if(bFlags & KEY_FLAGS_DOWN){
                    kPrintString(i++, 16, vcTemp);
                    if( vcTemp[0] == '0' ){
                        bTemp = bTemp / 0;
                    }
                }
        }
    }
    while(1);
}
