#include "Types.h"
#include "Keyboard.h"
#include "Descriptor.h"
#include "PIC.h"
#include "Crypt.h"

void kPrintString(int iX, int iY, const char * pcString );

void Main(void){

    char vcTemp[2] = {0,};
    BYTE bFlags;
    BYTE bTemp;
    int i = 0;

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
    
    
    kPrintString(0, 15, "Keyboard Activate.....................................[    ]");
    
    if(kActivateKeyboard() == TRUE){
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
    // clear page
    for(int i =0; i < 16; i++){
        kPrintString(0,i, "                                                            ");
    }
    // crypto
    int keylen = 80;
    unsigned char key1[11] = "\x3b\x4a\x2d\x58\x32\x5c\x3c\x1c\x41\x42";
    unsigned char ciphertext[100] = "welcome to mbr level reversing, this operating system is made by dochoon. I wish you love it.0Az";
    unsigned char ciphertextForPrint[200] = {0x00,};
    for(int i =0; i < 50; i++){
        for(int i = 0; i < 7; i++) lfsr_next(key1,keylen);
        ciphertext[i] ^= lfsr_next(key1,keylen);
    }
    for(int i =0; i < 50; i++){
        ciphertextForPrint[2*i] = ciphertext[i]>>4;
        if(ciphertextForPrint[2*i] >= 10) ciphertextForPrint[2*i] += 'A'-10;
        else ciphertextForPrint[2*i] += '0';
        ciphertextForPrint[2*i+1] = ciphertext[i]&0xf;
        if(ciphertextForPrint[2*i+1] >= 10) ciphertextForPrint[2*i+1] += 'A'-10;
        else ciphertextForPrint[2*i+1] += '0';
    }
    // print crypted string
    kPrintString(0, 1, "This is a crypted message");
    kPrintString(0, 2, ciphertextForPrint);
  

    // print question

    kPrintString(0, 6, "This is another crypted message");
    kPrintString(0, 7, "Find plain text of this");

    while(1){
        if( kIsOutputBufferFull() == TRUE){
            bTemp = kGetKeyboardScanCode();

            if(kConvertScanCodeToASCIICode(bTemp, &(vcTemp[0]),&bFlags) == TRUE){
                if((bFlags & KEY_FLAGS_DOWN)){
                    kPrintString(i++, 17, vcTemp);
                    if(vcTemp[0] == '0'){
                        bTemp = bTemp/0;
                    }
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
