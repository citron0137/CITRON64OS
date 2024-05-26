#include "Page.h"


void kInitializePageTables( void ){
    // PML4 Table
    PML4TENTRY *pstPML4TEntry = (PML4TENTRY *)0x100000;
    kSetPageEntryData(&(pstPML4TEntry[0]), 0x00, 0x101000, PAGE_FLAGS_DEFAULT, 0);
    for (int i = 1; i < PAGE_MAXENTRYCOUNT; i++)
        kSetPageEntryData(&(pstPML4TEntry[i]), 0, 0, 0, 0);

    // Page Directory Pointer Table
    PDPTENTRY *pstPDPTEntry = (PDPTENTRY *)0x101000;
    for (int i = 0; i < 64; i++)
        kSetPageEntryData(
            &(pstPDPTEntry[i]),
            0,
            0x102000 + (i * PAGE_TABLESIZE),
            PAGE_FLAGS_DEFAULT,
            0);
    for (int i = 64; i < PAGE_MAXENTRYCOUNT; i++)
        kSetPageEntryData(&(pstPDPTEntry[i]), 0, 0, 0, 0);

    // Page Directory Table
    PDENTRY *pstPDEntry = (PDENTRY *)0x102000;
    DWORD dwMappingAddress = 0;
    for (int i = 0; i < PAGE_MAXENTRYCOUNT * 64; i++){
        DWORD lowerBaseAddress = dwMappingAddress;
        DWORD upperBaseAddress = (i * (PAGE_DEFAULTSIZE >> 20)) >> 12;
        kSetPageEntryData(
            &(pstPDEntry[i]), 
            upperBaseAddress, 
            lowerBaseAddress, 
            PAGE_FLAGS_DEFAULT | PAGE_FLAGS_PS, 
            0);
            dwMappingAddress += PAGE_DEFAULTSIZE;
    }

}
void kSetPageEntryData(
    PTENTRY *pstEntry,
    DWORD dwUpperBaseAddress, DWORD dwLowerBaseAddress,
    DWORD dwLowerFlags, DWORD dwUpperFlags)
{
    pstEntry->dwAttributeAndLowerBaseAddress = dwLowerBaseAddress | dwLowerFlags;
    pstEntry->dwUpperBaseAddressAndEXB = (dwUpperBaseAddress & 0xFF ) | dwUpperFlags;
}