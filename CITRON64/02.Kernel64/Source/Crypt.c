#include "Crypt.h"

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

