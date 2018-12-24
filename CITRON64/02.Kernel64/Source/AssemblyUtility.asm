[BITS 64]

SECTION .text

global kInPortByte, kOutPortByte

kInPortByte:
    ;   포트로부터 1바이트 읽기
    push rdx

    mov rdx, rdi
    mov rax, 0
    in al, dx

    pop rdx
    ret

kOutPortByte:
    ;   포트에 1바이트 쓰기
    push rdx
    push rax 

    mov rdx, rdi 
    mov rax, rsi 
    out dx, al

    pop rax 
    pop rdx 
    ret