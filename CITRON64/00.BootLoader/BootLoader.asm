[ORG 0x00]          ; 코드의 시작 어드레스를 0x00으로 설정
[BITS 16]           ; 16비트 코드로 설정

SECTION .text       ; text섹션 정의

jmp $               ; 무한 루프 수행

times 510 - ( $ - $$ )    db  0x00    ;510바이트를 00으로 채움 

db 0x55             ; 
db 0xAA             ; 0x55 0xAA로 부트섹터를 표시함

