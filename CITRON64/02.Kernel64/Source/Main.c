#include "Types.h"
#include "Keyboard.h"
#include "Descriptor.h"
#include "PIC.h"

void kPrintString(int iX, int iY, const char * pcString );

void Main(void){

    char vcTemp[2] = {0,};
    BYTE bFlags;
    BYTE bTemp;
    int i = 0;
    KEYDATA stData;

    kPrintString(54, 10, "[Success]");
    kPrintString(0, 11, "IA-32e C Language Kernel Start........................[Pass]");

    kPrintString(0, 12, "GDT Initialize and Switch For IA-32e Mode.............[    ]");
    kInitializeGDTTableAndTSS();
    kLoadGDTR(GDTR_STARTADDRESS);
    kPrintString(55, 12, "Pass");

    kPrintString(0, 13, "TSS Segment Load......................................[    ]");
    kLoadTR(GDT_TSSSEGMENT);
    kPrintString(55, 13, "Pass");

    kPrintString(0, 14, "IDT Initialize........................................[    ]");
    kInitializeIDTTables();
    kLoadIDTR(IDTR_STARTADDRESS);
    kPrintString(55, 14, "Pass");
    
    
    kPrintString(0, 15, "Keyboard Activate And Queue Initialize................[    ]");
    
    if(kInitializeKeyboard() == TRUE){
        kPrintString(55, 15, "Pass");
        kChangeKeyboardLED(FALSE, FALSE, FALSE);
    }
    else{
        kPrintString(55, 15, "Fail");
        while(1);
    }

    kPrintString(0, 16, "PIC Controller And Interrupt Initialize...............[    ]");
    kInitializePIC();
    kMaskPICInterrupt(0);
    kEnableInterrupt();
    kPrintString(55, 16, "Pass");
  

    while(1){
        if(kGetKeyFromKeyQueue(&stData) == TRUE){
            if(stData.bFlags & KEY_FLAGS_DOWN){
                vcTemp[0] = stData.bASCIICode;
                kPrintString(i++, 17,vcTemp);
                if(vcTemp[0]=='0'){
                    bTemp = bTemp/0;
                }
            }
        }
    }
}

void kPrintString(int iX, int iY, const char * pcString ){
    CHARACTER *pstScreen = (CHARACTER *) 0xB8000;
    int i;
    pstScreen += (iY * 80)+iX;
    for(i = 0; pcString[i]!=0; i++){
        pstScreen[i].bCharactor = pcString[i];
    } 
}
