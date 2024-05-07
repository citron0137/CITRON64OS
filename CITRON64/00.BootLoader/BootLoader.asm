[ORG 0x00]          ; 코드의 시작 어드레스를 0x00으로 설정
[BITS 16]           ; 16비트 코드로 설정

SECTION .text       ; text섹션 정의

mov ax, 0xB800      
mov ds, ax          ; DS 레지스터에 0xB800 (비디오 메모리 어드레스) 지정

mov byte [ 0x00 ], 'C'
mov byte [ 0x01 ], 0x06 ; 검은색 배경에 노란색 글자 

jmp $               ; 무한 루프 수행

times 510 - ( $ - $$ )    db  0x00    ;510바이트를 00으로 채움 

db 0x55             ; 
db 0xAA             ; 0x55 0xAA로 부트섹터를 표시함

