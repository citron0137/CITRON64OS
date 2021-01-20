#include <stdio.h>
#define b1 10
#define b2 20
#define b3 30
#define b4 40
#define b5 50

unsigned char lfsr_next(unsigned char * key, int len){
    int prevShift = 0;
    int shift  = 0;
    int lastXor = 0;
    for(int i = 0; i < len/8; i++){
        shift = key[i]/128;
        key[i] <<= 1;
        key[i] += prevShift;
        prevShift = shift;
        if(b1/8 == i) lastXor ^= key[i]>>(b1%8) & 0x1;
        if(b2/8 == i) lastXor ^= key[i]>>(b2%8) & 0x1;
        if(b3/8 == i) lastXor ^= key[i]>>(b3%8) & 0x1;
        if(b4/8 == i) lastXor ^= key[i]>>(b4%8) & 0x1;
        if(b5/8 == i) lastXor ^= key[i]>>(b5%8) & 0x1;
    }
    key[0] += prevShift ^ lastXor;
    return key[len/8 -1];
}

int main(){
    int keylen = 80;
    unsigned char key1[11] = "\x3b\x4a\x2d\x58\x32\x5c\x3c\x1c\x41\x42";
    unsigned char key2[11] = "\x3b\x4a\x2d\x58\x32\x5c\x3c\x1c\x41\x42";
    //unsigned char ciphertext[300] = "welcome to reversing world, this operating system is made by dochoon. I wish you love it.0Az";
    unsigned char ciphertext[300] = "SSF{H0w_4b0ut_rnaking_0peratin9_3ystem_w1th_me}";
    unsigned char ciphertextForPrint[300] = {0x00,};
    
    //for(int i =0; i < 10; i++) printf("\\x%02x",key[i]); printf("\n");
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
    printf("%s\n",ciphertextForPrint);
    //for(int i =0; i < 101; i++){printf("%02x",ciphertext[i]);} printf("\n");
    
    for(int i =0; i < 100; i++){
        for(int i = 0; i < 7; i++) lfsr_next(key2,keylen);
        ciphertext[i] ^= lfsr_next(key2,keylen);
    }
    for(int i =0; i < 100; i++){printf("%c",ciphertext[i]);} printf("\n");   
    
}