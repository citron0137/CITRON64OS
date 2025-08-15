#include "Descriptor.h"
#include "Utility.h"
#include "ISR.h"

void kInitializeGDTTableAndTSS( void )
{
    GDTR* pstGDTR;
    GDTENTRY8* pstEntry;
    TSSSEGMENT* pstTSS;
    int i;

    // 1. GDTR 초기화
    pstGDTR = (GDTR*) GDTR_STARTADDRESS;
    pstEntry = (GDTENTRY8*) (GDTR_STARTADDRESS + sizeof( GDTR ));
    pstGDTR->qwBaseAddress = ( QWORD ) pstEntry; 
    pstGDTR->wLimit = GDT_TABLESIZE - 1;
    
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

    kSetIDTEntry( &( pstEntry[0]), kISRDivideError, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[1]), kISRDebug, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[2]), kISRNMI, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[3]), kISRBreakPoint, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[4]), kISROverflow, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[5]), kISRBoundRangeExceeded, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[6]), kISRInvalidOpcode, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[7]), kISRDeviceNotAvailable, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[8]), kISRDoubleFault, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[9]), kISRCoprocessorSegmentOverrun, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[10]), kISRInvalidTSS, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[11]), kISRSegmentNotPresent, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[12]), kISRStackSegmentFault, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[13]), kISRGeneralProtection, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[14]), kISRPageFault, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[15]), kISR15, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[16]), kISRFPUError, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[17]), kISRAlignmentCheck, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[18]), kISRMachineCheck, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[19]), kISRSIMDError, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[20]), kISRETCException, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    for( i = 21; i < 32; i++ ){
        kSetIDTEntry( &( pstEntry[i]), kISRETCException, \
            0x08, \
            IDT_FLAGS_IST1, \
            IDT_FLAGS_KERNEL, \
            IDT_TYPE_INTERRUPT );
    }

    kSetIDTEntry( &( pstEntry[32]), kISRTimer, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[33]), kISRKeyboard, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[34]), kISRSlavePIC, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[35]), kISRSerial2, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[36]), kISRSerial1, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[37]), kISRParallel2, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[38]), kISRFloppy, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[39]), kISRParallel1, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[40]), kISRRTC, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[41]), kISRReserved, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[42]), kISRNotUsed1, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[43]), kISRNotUsed2, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[44]), kISRMouse, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[45]), kISRCoprocessor, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[46]), kISRHDD1, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    kSetIDTEntry( &( pstEntry[47]), kISRHDD2, \
        0x08, \
        IDT_FLAGS_IST1, \
        IDT_FLAGS_KERNEL, \
        IDT_TYPE_INTERRUPT );

    for( i = 48; i < IDT_MAXENTRYCOUNT; i++ ){
        kSetIDTEntry( &( pstEntry[i]), kISRETCInterrupt, \
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