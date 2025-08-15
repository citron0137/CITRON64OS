#include "Descriptor.h"
#include "Utility.h"

void kInitializeGDTTableAndTSS( void )
{
    GDTR* pstGDTR;
    GDTENTRY8* pstEntry;
    TSSSEGMENT* pstTSS;
    int i;

    // 1. GDTR 초기화
    pstGDTR = (GDTR*) GDTR_STARTADDRESS;
    pstEntry = (GDTENTRY8*) (GDTR_STARTADDRESS + sizeof( GDTR ));
    pstGDTR->wLimit = GDT_TABLESIZE - 1;
    pstGDTR->qwBaseAddress = ( QWORD ) pstEntry; 
    
    pstTSS = (TSSSEGMENT*) ((QWORD) pstEntry + GDT_TABLESIZE);
    kSetGDTEntry8( &( pstEntry[0]), 0, 0, 0, 0, 0 );
    kSetGDTEntry8( &( pstEntry[1]), 0, 0xFFFFF, \
        GDT_FLAGS_UPPER_CODE, \
        GDT_FLAGS_LOWER_KERNELCODE, \
        GDT_TYPE_CODE );
    kSetGDTEntry8( &( pstEntry[2]), 0, 0xFFFFF, \
        GDT_FLAGS_UPPER_DATA, \
        GDT_FLAGS_LOWER_KERNELDATA, \
        GDT_TYPE_DATA );

    kSetGDTEntry16( (GDTENTRY16* ) &( pstEntry[3]), (QWORD) pstTSS, TSS_SEGMENTSIZE - 1, 
        GDT_FLAGS_UPPER_TSS, \
        GDT_FLAGS_LOWER_TSS, \
        GDT_TYPE_TSS );

    kInitializeTSSSegment( pstTSS );
}

void kSetGDTEntry8( \
    GDTENTRY8* pstEntry, \
    DWORD dwBaseAddress, \
    DWORD dwLimit, \
    BYTE bUppeFlags, \
    BYTE bLowerFlags, \
    BYTE bType \
){
    pstEntry->wLowerLimit = (dwLimit & 0xFFFF);
    pstEntry->wLowerBaseAddress = (dwBaseAddress & 0xFFFF);
    pstEntry->bUpperBaseAddress1 = (BYTE) ((dwBaseAddress >> 16) & 0xFF);
    pstEntry->bTypeAndLowerFlag = (BYTE) (bLowerFlags | bType);
    pstEntry->UpperLimitAndUpperFlag = (BYTE) ((dwLimit >> 16) & 0x0F) | bUppeFlags;
    pstEntry->bUpperBaseAddress2 = (BYTE) ((dwBaseAddress >> 24) & 0xFF);
}

void kSetGDTEntry16( \
    GDTENTRY16* pstEntry, \
    QWORD qwBaseAddress, \
    DWORD dwLimit, \
    BYTE bUpperFlags, \
    BYTE bLowerFlags, \
    BYTE bType \
){
    pstEntry->wLowerLimit = (dwLimit & 0xFFFF);
    pstEntry->wLowerBaseAddress = (DWORD) (qwBaseAddress & 0xFFFF);
    pstEntry->bMiddleBaseAddress1 = (BYTE) ((qwBaseAddress >> 16) & 0xFF);
    pstEntry->bTypeAndLowerFlag = (BYTE) (bLowerFlags | bType);
    pstEntry->bUpperLimitAndUpperFlag = (BYTE) ((dwLimit >> 16) & 0x0F) | bUpperFlags;
    pstEntry->bMiddleBaseAddress2 = (BYTE) ((qwBaseAddress >> 24) & 0xFF);
    pstEntry->dwUpperBaseAddress = (DWORD) ((qwBaseAddress >> 32) & 0xFFFFFFFF);
    pstEntry->dwReserved = 0;
}

void kInitializeTSSSegment( TSSSEGMENT* pstTSS ){
    kMemSet( pstTSS, 0, TSS_SEGMENTSIZE );
    pstTSS->qwIST[ 0 ] = (QWORD) IST_STARTADDRESS + IST_SIZE;
    pstTSS->wIOMapBaseAddress = 0xFFFF;
}

void kInitializeIDTTables( void)
{
    IDTR* pstIDTR;
    IDTENTRY* pstEntry;
    int i;

    pstIDTR = (IDTR*) IDTR_STARTADDRESS;
    pstEntry = (IDTENTRY*) IDT_STARTADDRESS + sizeof(IDTR);
    pstIDTR->qwBaseAddress = (QWORD) pstEntry;
    pstIDTR->wLimit = IDT_TABLESIZE - 1;

    for( i = 0; i < IDT_MAXENTRYCOUNT; i++ ){
        kSetIDTEntry( &( pstEntry[i]), kDummyHandler, \
            0x08, \
            IDT_FLAGS_IST1, \
            IDT_FLAGS_KERNEL, \
            IDT_TYPE_INTERRUPT );
    }
}

void kSetIDTEntry( \
    IDTENTRY* pstEntry, \
    void* pvHandlerAddress, \
    WORD wSelector, \
    BYTE bIST, \
    BYTE bFlags, \
    BYTE bType \
){
    pstEntry->wLowerBaseAddress = (DWORD) (QWORD) pvHandlerAddress & 0xFFFF;
    pstEntry->wSegmentSelector = wSelector;
    pstEntry->bIST = bIST & 0x3;
    pstEntry->bTypeAndFlags = (BYTE) (bFlags | bType);
    pstEntry->wMiddleBaseAddress = (DWORD) ((QWORD) pvHandlerAddress >> 16) & 0xFFFF;
    pstEntry->dwUpperBaseAddress = (DWORD) pvHandlerAddress >> 32;
    pstEntry->dwReserved = 0;
}

void kDummyHandler( void ){
    kPrintString( 0, 0, "=====================================");
    kPrintString( 0, 1, "         Dummy Handler               ");
    kPrintString( 0, 2, "   Interrupt or Exception Occur      ");
    kPrintString( 0, 3, "=====================================");
    while(1);
}