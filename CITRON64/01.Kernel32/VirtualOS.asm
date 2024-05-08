[ORG 0x00]          
[BITS 16]

SECTION .text

jmp 0x1000:START            ; 이미지를 복사한 0x10000으로 CS레지스터 변경

SECTORCOUNT:    dw 0x0000   ; 현재 실행중인 섹터 번호 저장

START:
    mov ax, cs
    mov ds, ax              ; 데이터 세그멘트도 CS와 동일하게 설정

    mov ax, 0xB800
    mov es, ax              ; 비디오 메모리 주소를 es에 설정

    mov ax, 2               
    mul word [ SECTORCOUNT ]    ;
    mov si, ax
    mov byte [ es: ( 160 * 2 ) + si ], '0'
    add word [ SECTORCOUNT ], 1

    jmp $

    times 512 - ( $ - $$ ) db 0x00