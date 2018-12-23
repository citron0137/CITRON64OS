[ORG 0x00]
[BITS 16]

SECTION .text

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   코드영역
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

START:
    mov ax, 0x1000
    mov ds, ax
    mov es, ax

    ;   A20게이트 활성화
    ;   1. BIOS 서비스 사용
    mov ax, 0x2401
    int 0x15
    jc .A20GATEERROR
    jmp .A20GATESUCCESS

.A20GATEERROR:
    in al, 0x92 ;컨트롤 포트(0x92)에서 바이트를 읽어옴
    or al, 0x02
    and al, 0xFE
    out 0x92, al

.A20GATESUCCESS:
    cli
    lgdt[GDTR]

    ;보호모드로 진입 전 세팅
    ;Disable Paging, Disable cache, Internal FPU
    ;Disable Align check, Enable ProtectedMode
    mov eax, 0x4000003B
    mov cr0, eax

    jmp dword 0x18: (PROTECTEMODE - $$ + 0x10000 )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   보호모드 진입
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[BITS 32]
PROTECTEMODE:
    mov ax, 0x20
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ss, ax
    mov esp, 0xFFFE
    mov ebp, 0xFFFE

    push(SWITCHSUCCESSMESSAGE - $$ + 0x10000)
    push 2
    push 0
    call PRINTMESSAGE
    add esp, 12

    jmp dword 0x18: 0x10200

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   함수 코드 영영
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PRINTMESSAGE:
    push ebp
    mov ebp, esp
    push esi
    push edi
    push eax
    push ecx
    push edx

    mov eax, dword[ebp+12]
    mov esi, 160
    mul esi
    mov edi, eax

    mov eax, dword[ebp+8]
    mov esi, 2
    mul esi
    add edi, eax

    mov esi, dword[ebp+16]

.MESSAGELOOP:
    mov cl, byte[esi]
    cmp cl, 0
    je .MESSAGEEND

    mov byte[edi+0xB8000], cl

    add esi, 1
    add edi, 2
    jmp .MESSAGELOOP

.MESSAGEEND:
    pop edx
    pop ecx
    pop eax
    pop edi
    pop esi
    pop ebp
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   데이터 영역
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
align 8, db 0

dw 0x0000

GDTR:
    dw GDTEND - GDT - 1
    dd (GDT - $$ + 0x10000)

GDT:
    NULLDescriptor:
        dw 0x0000   ;Limit[15:0]
        dw 0x0000   ;Base[15:0]
        db 0x00     ;Base[23:16]
        db 0x00     ;P(1), DPL(2), S(1), Typed(4)
        db 0x00     ;G(1), D/B(1), L(1), Available(1), Limit[19:16]
        db 0x00     ;Base[31:24]

    IA_32eCODEDESCRIPTOR:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x9A
        db 0xAF
        db 0x00

    IA_32eDATADESCRIPTOR:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x92
        db 0xAF
        db 0x00

    CODEDESCRIPTOR:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x9A
        db 0xCF
        db 0x00

    DATADESCRIPTOR:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x92
        db 0xCF
        db 0x00
GDTEND:

SWITCHSUCCESSMESSAGE: db 'Switch To Protected Mode [Success]', 0

times 512 - ( $ - $$ ) db 0x00