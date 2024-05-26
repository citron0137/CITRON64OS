[BITS 64]

SECTION .text

; 외부에서 정의된 함수를 사용할 수 있도록 선언
extern Main

START:
    mov ax, 0x10    ; 세그먼트 디스크립터 지정
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ss, ax
    mov rsp, 0x6FFFF8
    mov rbp, 0x6FFFF8

    call Main

    jmp $
