[BITS 32]

; C언어에서 사용할 수 있도록 노출
global kReadCPUID
global kSwitchAndExecute64bitKernel

SECTION .text

; CPUID 반환
;   PARAM: dwEAX, pdwEBX, pdwECX, pdwEDX
kReadCPUID:
    push ebp
    mov ebp, esp
    push eax
    push ebx
    push ecx
    push edx
    push esi

    ; CPUID 실행
    mov eax, dword[ ebp + 8 ]
    cpuid

    ; 반환값 저장
    mov esi, dword [ ebp + 12 ]
    mov dword[ esi ], eax
    
    mov esi, dword [ ebp + 16 ]
    mov dword[ esi ], ebx
    
    mov esi, dword [ ebp + 20 ]
    mov dword[ esi ], ecx
    
    mov esi, dword [ ebp + 24 ]
    mov dword[ esi ], edx

    pop esi
    pop edx
    pop ecx 
    pop ebx
    pop eax
    pop ebp
    ret
    
    
; IA-32e 모드로 전환 및 64bit 커널로 jmp
;   PARAM: Void
kSwitchAndExecute64bitKernel:
    
    ; CR4 PAE = 1
    mov eax, cr4
    or eax, 0x20
    mov cr4, eax

    ; Enable PML4 table address cache 
    mov eax, 0x100000
    mov cr3, eax

    ; IA32_EFER.LME를 1로 설정하여 IA-32e 모드 활성화
    mov ecx, 0xC0000080 ; 0xC0000080 = MSR레지스터 주소 
    rdmsr
    or eax, 0x0100; LME bit = 1
    wrmsr

    ; NW[29] = 0, CD[30] = 0, PG[32] = 1 -> 캐시와 페이징 활성화
    mov eax, cr0
    or eax, 0xE0000000
    xor eax, 0x60000000
    mov cr0, eax

    ; 64bit 커널로 jmp
    jmp 0x08: 0x200000

    jmp $



