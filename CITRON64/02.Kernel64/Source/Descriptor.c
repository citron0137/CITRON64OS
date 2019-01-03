#include "Descriptor.h"
#include "Utility.h"

//==============================
//  GDT 및 TSS
//==============================

//  GDT 테이블을 초기화
void kInitializeGDTTableAndTSS( void ){
    GDTR *pstGDTR;
    GDTENTRY8 *pstEntry;
    TSSSEGMENT *pstTSS;
    int i;

    //GDTR설정
    pstGDTR = (GDTR *)GDTR_STARTADDRESS;
    pstEntry = (GDTENTRY8 *)(GDTR_STARTADDRESS + sizeof(GDTR));
    pstGDTR->wLimit = GDT_TABLESIZE -1;
    pstGDTR->qwBaseAddress = (QWORD)pstEntry;
    //  TSS 영역 설정
    pstTSS = (TSSSEGMENT *)((QWORD) pstEntry + GDT_TABLESIZE);
    // NULL, 64bit Code/Data, TSS
    kSetGDTEntry8( &(pstEntry[0]), 0, 0, 0, 0, 0);
    kSetGDTEntry8( &(pstEntry[1]), 0, 0xFFFFFF, GDT_FLAGS_UPPER_CODE, GDT_FLAGS_LOWER_KERNELCODE, GDT_TYPE_CODE);
    kSetGDTEntry8( &(pstEntry[2]), 0, 0xFFFFFF, GDT_FLAGS_UPPER_DATA, GDT_FLAGS_LOWER_KERNELDATA, GDT_TYPE_DATA);
    kSetGDTEntry16( (GDTENTRY16 *)&(pstEntry[3]), (QWORD)pstTSS, sizeof(TSSSEGMENT) - 1, GDT_FLAGS_UPPER_TTS, GDT_FLAGS_LOWER_TSS,GDT_TYPE_TSS);

    kInitializeTSSSegment(pstTSS);
}

// setting value on GDT Entry (8byte size)
// used to set code/data segment discriptor
void kSetGDTEntry8( GDTENTRY8 *pstEntry, DWORD dwBaseAddress, DWORD dwLimit, BYTE bUpperFlags, BYTE bLowerFlags, BYTE bType ){
    pstEntry->wLowerLimit = dwLimit & 0xFFFF;
    pstEntry->wLowerBaseAddress = dwBaseAddress & 0xFFFF;
    pstEntry->bUpperBaseAddress1 = (dwBaseAddress >> 16) & 0xFF;
    pstEntry->bTypeAndLowerFlag = bLowerFlags | bType;
    pstEntry->bUpperLimitAndUpperFlag = ((dwLimit >> 16) & 0x0F ) | bUpperFlags;
    pstEntry->bUpperBaseAddress2 = (dwBaseAddress >> 24) &0xFF;
}

// setting value on GDT Entry (16byte size)
// used to set TSS segment discriptor
void kSetGDTEntry16( GDTENTRY16 *pstEntry, QWORD qwBaseAddress, DWORD dwLimit, BYTE bUpperFlags, BYTE bLowerFlags, BYTE bType ){
    pstEntry->wLowerLimit = dwLimit & 0xFFFF;
    pstEntry->wLowerBaseAddress = qwBaseAddress & 0xFFFF;
    pstEntry->bMiddleBaseAddress1 = (qwBaseAddress >> 16) & 0xFF;
    pstEntry->bTypeAndLowerFlag = bLowerFlags | bType;
    pstEntry->bUpperLimitAndUpperFlag = ((dwLimit >> 16) & 0x0F) | bUpperFlags;
    pstEntry->bMiddleBaseAddress2 = (qwBaseAddress >> 24) & 0xFF;
    pstEntry->dwUpperBaseAddress = qwBaseAddress>>32;
    pstEntry->dwReserved = 0;
}

// TSS 세그멘트의 정보를 초기화
void kInitializeTSSSegment( TSSSEGMENT *pstTSS){
    kMemset(pstTSS, 0, sizeof(TSSSEGMENT));
    pstTSS->qwIST[0] = IST_STARTADDRESS + IST_SIZE;
    //IO를 TSS의 limit 보다 크게 설정해서 IO map을 사용 안하도록 설정
    pstTSS->wIOMapBaseAddress = 0xFFFF;
}

//=========================================
//  IDT
//=========================================
//  IDT 테이블을 초기화
void kInitializeIDTTables( void ){
    IDTR *pstIDTR;
    IDTENTRY *pstEntry;
    int i;

    //IDTR의 시작 어드레스
    pstIDTR = (IDTR *)IDTR_STARTADDRESS;
    pstEntry = (IDTENTRY *)(IDTR_STARTADDRESS + sizeof(IDTR));
    pstIDTR->qwBaseAddress = (QWORD)pstEntry;
    pstIDTR->wLimit = IDT_TABLESIZE - 1;

    for( i = 0; i < IDT_MAXENTRYCOUNT ; i++){
        kSetIDTEntry(&(pstEntry[i]), kDummyHandler, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    }
}

void kSetIDTEntry( IDTENTRY *pstEntry, void *pvHandler, WORD wSelector, BYTE bIST, BYTE bFlags, BYTE bType){
    pstEntry->wLowerBaseAddress = (QWORD)pvHandler & 0xFFFF;
    pstEntry->wSegmentSelector = wSelector;
    pstEntry->bIST = bIST&0x3;
    pstEntry->bTypeAndFlags = bType | bFlags;
    pstEntry->wMiddleBaseAddress = ((QWORD)pvHandler >> 16)&0xFFFF;
    pstEntry->dwReserved = 0;
}

void kDummyHandler( void ){
    kPrintString( 0, 0, "===================================================");
    kPrintString( 0, 1, "         Dummy Interrupt Handler Execute           ");
    kPrintString( 0, 2, "           Interrupt or Exception Occur            ");
    kPrintString( 0, 3, "===================================================");

    while(1);
}
