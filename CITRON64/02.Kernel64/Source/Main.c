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
    for(int i =0; i < 20; i++){
        kPrintString(0,i, "                                                                      ");
    }
    // crypto
    int keylen = 80;
    unsigned char key1[11] = "\x3b\x4a\x2d\x58\x32\x5c\x3c\x1c\x41\x42";
    unsigned char ciphertext[100] = "welcome to reversing world, this operating system is made by dochoon. I wish you love it.0Az";
    unsigned char ciphertextForPrint[200] = {0x00,};
    for(int i =0; i < 100; i++){
        for(int i = 0; i < 7; i++) lfsr_next(key1,keylen);
        ciphertext[i] ^= lfsr_next(key1,keylen);
    }
    for(int i =0; i < 100; i++){
        ciphertextForPrint[2*i] = ciphertext[i]>>4;
        if(ciphertextForPrint[2*i] >= 10) ciphertextForPrint[2*i] += 'A'-10;
        else ciphertextForPrint[2*i] += '0';
        ciphertextForPrint[2*i+1] = ciphertext[i]&0xf;
        if(ciphertextForPrint[2*i+1] >= 10) ciphertextForPrint[2*i+1] += 'A'-10;
        else ciphertextForPrint[2*i+1] += '0';
    }
    // print welcome
//
// _  _ __, _,   _,  _, _, _ __,
// |  | |_  |   / ` / \ |\/| |_ 
// |/\| |   | , \ , \ / |  | |  
// ~  ~ ~~~ ~~~  ~   ~  ~  ~ ~~~
                              

    kPrintString(0, 0, " _  _ __, _,   _,  _, _, _ __,");
    kPrintString(0, 1, " |  | |_  |   / ` / \\ |\\/| |_ ");
    kPrintString(0, 2, " |/\\| |   | , \\ , \\ / |  | |  ");
    kPrintString(0, 3, " ~  ~ ~~~ ~~~  ~   ~  ~  ~ ~~~");
    kPrintString(0, 4, "");
    
    // print crypted string
    kPrintString(0, 5, "This is an encrypted message :");
    kPrintString(0, 6, ciphertextForPrint);
    
    // print question
    kPrintString(0, 10, "This is another encrypted message :");
     
    kPrintString(0, 11, "124F7A277A685A150F3FE43A2A8E83996FF74448897A6206C93BC0450116B9AB2CC1518051BC7414542265A3EC8B42EA4A496247469C006AE0F394AF99DFD1E3A853B0B235B7AC03232CDB9AFF24D908F3259A4BE2E18914226715A77D35E15B17073D18");
    
    kPrintString(0, 15, "Find plain text of second encrypted message");
    kPrintString(0, 17, "+) Cryptographic routines are hidden in this operating system.");

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
