[ORG 0x00]          
[BITS 16]

SECTION .text

jmp 0x1000:START            ; 이미지를 복사한 0x10000으로 CS레지스터 변경

SECTORCOUNT:    dw 0x0000   ; 현재 실행중인 섹터 번호 저장
TOTALSECTORCOUNT    equ 1024  ; 총 섹터수를 1024개로 지정

START:
    mov ax, cs
    mov ds, ax              ; 데이터 세그멘트를 0x1000으로 설정
    mov ax, 0xB800
    mov es, ax              ; 비디오 메모리 주소를 es에 설정
; 이까지는 섹터 1번에만 존재함

; 아래부터는 섹터별로 다르게 동작해야함
    %assign i 0
    %rep TOTALSECTORCOUNT
        %assign i  i + 1     ; 1024번 돌면서 i를 1씩 증가

        ; 현재의 섹터 번호 1의 자리수 출력
        mov ax, 2               
        mul word [ SECTORCOUNT ]    
        mov si, ax
        mov byte [ es: ( 160 * 2 ) + si ], '0' + ( i % 10 ) 
        add word [ SECTORCOUNT ], 1
    
        ; 마지막 섹터의 경우 무한 반복
        ; 다음 섹터가 존재하는 경우 다음 섹터로 이동 및 CS 레지스터 변경
        %if i == TOTALSECTORCOUNT
            jmp $
        %else
            jmp ( 0x1000 + 0x20 * i ): 0x0000
        %endif

        ; 섹터당 512가 되게끔 패딩
        times ( 512 - ( $ - $$ ) % 512 ) db 0x00 

    %endrep