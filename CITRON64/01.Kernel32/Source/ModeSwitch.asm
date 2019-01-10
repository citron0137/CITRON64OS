[BITS 32]

global kReadCPUID, kSwitchAndExecute64bitKernel

SECTION .text

kReadCPUID:
    push ebp
    mov ebp, esp
    push eax
    push ebx 
    push ecx 
    push edx 
    push esi 

    mov eax, dword[ebp+8]
    cpuid 

    mov esi, dword[ebp+12]
    mov dword[esi], eax

    mov esi, dword[ebp+16]
    mov dword[esi], ebx

    mov esi, dword[ebp+20]
    mov dword[esi], ecx 

    mov esi, dword[ebp+24]
    mov dword[esi], edx 

    pop esi 
    pop edx 
    pop ecx 
    pop ebx 
    pop eax 
    pop ebp 
    ret

kSwitchAndExecute64bitKernel:
    
    mov eax, cr4
    or eax, 0x620    ; PAE비트 1로 설정 
    mov cr4, eax 

    mov eax, 0x100000 
    mov cr3, eax    ;CR3 컨트롤 레지스터에 PML4테이블 위치 저장

    mov ecx, 0xC0000080
    rdmsr
    or eax, 0x0101  ;IA32_EFER MSR에서 LME비트 1로 설정
    wrmsr

    mov eax, cr0
    or eax, 0xE000000E      ; NW, CD, PG 1로 설정 
    xor eax, 0x60000004     ; NW, CD 0으로 설정
    mov cr0, eax

    jmp 0x08:0x200000
