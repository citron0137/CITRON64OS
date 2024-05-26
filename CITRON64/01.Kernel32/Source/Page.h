#ifndef __PAGE_H__
#define __PAGE_H__

#include "Types.h"

#define PAGE_FLAGS_P            0x00000001  // Present
#define PAGE_FLAGS_RW           0x00000002  // Read/Write
#define PAGE_FLAGS_US           0x00000004  // User/Superviser

#define PAGE_FLAGS_PWT          0x00000008  // Page Level Write-through 
#define PAGE_FLAGS_PCD          0x00000010  // Page Level Cache disabled 

#define PAGE_FLAGS_A            0x00000020  // Accessed 
#define PAGE_FLAGS_D            0x00000040  // Dirty 

#define PAGE_FLAGS_PS           0x00000080  // PageSize
#define PAGE_FLAGS_G            0x00000100  // Global 
#define PAGE_FLAGS_PAT          0x00001000  // Page Attribute table index 
#define PAGE_FLAGS_EXB          0x80000000  // Executive Disabled  

#define PAGE_FLAGS_DEFAULT      ( PAGE_FLAGS_P | PAGE_FLAGS_RW ) 
#define PAGE_TABLESIZE          0x1000
#define PAGE_MAXENTRYCOUNT      512
#define PAGE_DEFAULTSIZE        0x200000 


// 자료형
#pragma pack( push, 1 )
typedef struct kPageTableEntryStruct{
    DWORD dwAttributeAndLowerBaseAddress;
    // PML4T와 PDPTE의 경우 
    // P, RW, US, PWT, PCD, A, D, PS, G, Avail(3bit), pat, reserved(8bit), BaseAddress (20bit)
    // PDE의 경우 
    // P, RW, US, PWT, PCD, A, D,  1, G, Avail(3bit), pat,    avail(8bit), Base Address (20bit)

    DWORD dwUpperBaseAddressAndEXB;
    // UpperBaseAddress(8bit), reserved(12bit), avail(11bit), EXB(1bit)
} PML4TENTRY, PDPTENTRY, PDENTRY, PTENTRY;
#pragma pack( pop )

// 함수
void kInitializePageTables( void );
void kSetPageEntryData( PTENTRY* pstEntry, 
                        DWORD dwUpperBaseAddress, DWORD dwLowerBaseAddress,
                        DWORD dwLowerFlags, DWORD dwUpperFlags );

#endif /* __PAGE_H__ */