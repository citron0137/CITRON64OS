#ifndef __DESCRIPTOR_H__
#define __DESCRIPTOR_H__

#include "Types.h"

//매크로
//=====================================
// GDT
//=====================================

#define GDT_TYPE_CODE           0x0A
#define GDT_TYPE_DATA           0x02
#define GDT_TYPE_TSS            0x09

#define GDT_FLAGS_LOWER_S       0x10
#define GDT_FLAGS_LOWER_DPL0    0x00
#define GDT_FLAGS_LOWER_DPL1    0x20
#define GDT_FLAGS_LOWER_DPL2    0x40
#define GDT_FLAGS_LOWER_DPL3    0x60
#define GDT_FLAGS_LOWER_P       0x80

#define GDT_FLAGS_UPPER_L       0x20
#define GDT_FLAGS_UPPER_DB      0x40
#define GDT_FLAGS_UPPER_G       0x80

#define GDT_FLAGS_LOWER_KERNELCODE ( \
    GDT_TYPE_CODE | \
    GDT_FLAGS_LOWER_S | \
    GDT_FLAGS_LOWER_DPL0 | \
    GDT_FLAGS_LOWER_P \
)

#define GDT_FLAGS_LOWER_KERNELDATA ( \
    GDT_TYPE_DATA | \
    GDT_FLAGS_LOWER_S | \
    GDT_FLAGS_LOWER_DPL0 | \
    GDT_FLAGS_LOWER_P \
)

#define GDT_FLAGS_LOWER_TSS ( \
    GDT_FLAGS_LOWER_DPL0 | \
    GDT_FLAGS_LOWER_P \
)

#define GDT_FLAGS_LOWER_USERCODE ( \
    GDT_TYPE_CODE | \
    GDT_FLAGS_LOWER_S | \
    GDT_FLAGS_LOWER_DPL3 | \
    GDT_FLAGS_LOWER_P \
)

#define GDT_FLAGS_LOWER_USERDATA ( \
    GDT_TYPE_DATA | \
    GDT_FLAGS_LOWER_S | \
    GDT_FLAGS_LOWER_DPL3 | \
    GDT_FLAGS_LOWER_P \
)

#define GDT_FLAGS_UPPER_CODE ( \
    GDT_FLAGS_UPPER_L | \
    GDT_FLAGS_UPPER_G \
)

#define GDT_FLAGS_UPPER_DATA ( \
    GDT_FLAGS_UPPER_L | \
    GDT_FLAGS_UPPER_G \ 
)

#define GDT_FLAGS_UPPER_TSS ( \
    GDT_FLAGS_UPPER_G  \
)

#define GDT_KERNELCODESEGMENT 0x08
#define GDT_KERNELDATASEGMENT 0x10
#define GDT_TSSSEGMENT        0x18

#define GDTR_STARTADDRESS 0x142000
#define GDT_MAXENTRY8COUNT 3
#define GDT_MAXENTRY16COUNT 1

#define GDT_TABLESIZE ( \
    (sizeof(GDTENTRY8) * GDT_MAXENTRY8COUNT) + \
    (sizeof(GDTENTRY16) * GDT_MAXENTRY16COUNT) \
)

#define TSS_SEGMENTSIZE (sizeof(TSSSEGMENT))


//================================================
// IDT  
//================================================

#define IDT_TYPE_INTERRUPT     0x0E
#define IDT_TYPE_TRAP          0x0F
#define IDT_FLAGS_DPL0    0x00
#define IDT_FLAGS_DPL1    0x20
#define IDT_FLAGS_DPL2    0x40
#define IDT_FLAGS_DPL3    0x60
#define IDT_FLAGS_P       0x80
#define IDT_FLAGS_IST0          0
#define IDT_FLAGS_IST1          1

#define IDT_FLAGS_KERNEL      (IDT_FLAGS_DPL0 | IDT_FLAGS_P)
#define IDT_FLAGS_USER        (IDT_FLAGS_DPL3 | IDT_FLAGS_P)

#define IDT_MAXENTRYCOUNT 100
#define IDTR_STARTADDRESS ( \
    GDTR_STARTADDRESS + \ 
    sizeof( GDTR ) + \ 
    GDT_TABLESIZE + \
    TSS_SEGMENTSIZE \
)

#define IDT_STARTADDRESS ( IDTR_STARTADDRESS + sizeof( IDTR ))

#define IDT_TABLESIZE (IDT_MAXENTRYCOUNT * sizeof(IDTENTRY))

#define IST_STARTADDRESS 0x700000
#define IST_SIZE 0x100000

#pragma pack( push, 1 )

typedef struct kGDTRStruct
{
    WORD wLimit;
    QWORD qwBaseAddress;
    WORD wPading;
    DWORD dwPading;
} GDTR, IDTR;

typedef struct kGDTEntry8Struct
{
    WORD wLowerLimit;
    WORD wLowerBaseAddress;
    BYTE bUpperBaseAddress1;
    BYTE bTypeAndLowerFlag;
    BYTE UpperLimitAndUpperFlag;
    BYTE bUpperBaseAddress2;
} GDTENTRY8;

typedef struct kGDTEntry16Struct
{
    WORD wLowerLimit;
    WORD wLowerBaseAddress;
    BYTE bMiddleBaseAddress1;
    BYTE bTypeAndLowerFlag;
    BYTE bUpperLimitAndUpperFlag;
    BYTE bMiddleBaseAddress2;
    DWORD dwUpperBaseAddress;
    DWORD dwReserved;
} GDTENTRY16;

typedef struct kTSSDataStruct
{
    DWORD dwReserved;
    QWORD qwRsp[ 3 ];
    QWORD qwReserved2;
    QWORD qwIST[ 7 ];
    DWORD dwReserved3;
    WORD wReserved;
    WORD wIOMapBaseAddress;
} TSSSEGMENT;


typedef struct kIDTEntryStruct{
    WORD wLowerBaseAddress;
    WORD wSegmentSelector;
    BYTE bIST;
    BYTE bTypeAndFlags;
    WORD wMiddleBaseAddress;
    DWORD dwUpperBaseAddress;
    DWORD dwReserved;
} IDTENTRY;

#pragma pack( pop )

void kInitializeGDTTableAndTSS( void );
void kSetGDTEntry8( \
    GDTENTRY8* pstEntry, \
    DWORD dwBaseAddress, \
    DWORD dwLimit, \
    BYTE bUppeFlags, \
    BYTE bLowerFlags, \
    BYTE bType \
);

void kSetGDTEntry16( \
    GDTENTRY16* pstEntry, \
    QWORD qwBaseAddress, \
    DWORD dwLimit, \
    BYTE bUpperFlags, \
    BYTE bLowerFlags, \
    BYTE bType \
);

void kInitializeTSSSegment( TSSSEGMENT* pstTSS );

void kSetIDTEntry( \
    IDTENTRY* pstEntry, \
    void* pvHandlerAddress, \
    WORD wSelector, \
    BYTE bIST, \
    BYTE bFlags, \
    BYTE bType \
);

void kDummyHandler( void );

#endif // __DESCRIPTOR_H__