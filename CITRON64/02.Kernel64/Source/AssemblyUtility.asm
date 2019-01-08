[BITS 64]

SECTION .text

global kInPortByte, kOutPortByte, kLoadGDTR, kLoadTR, kLoadIDTR
global kEnableInterrupt, kDisableInterrupt, kReadRFLAGS

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

; GDTR레지스터에 GDT 테이블을 설정
;   PARAM: GDT 테이블의 정보를 저장하는 자료구조의 어드레스
kLoadGDTR:
    lgdt [rdi]
    ret

kLoadTR:
    ltr di
    ret

kLoadIDTR:
    lidt [rdi]
    ret

kEnableInterrupt:
    sti 
    ret 

kDisableInterrupt:
    cli
    ret 

kReadRFLAGS:
    pushfq
    pop rax 
    ret 