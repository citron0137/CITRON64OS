[ORG 0x00]          ; 코드의 시작 어드레스를 0x00으로 설정
[BITS 16]           ; 16비트 코드로 설정

SECTION .text       ; text섹션 정의

jmp 0x07C0:START    ; 0x07C0(부트로더 영역)으로 CS 레지스터 지정 및 START로 이동

START:
    mov ax, 0x07C0
    mov ds, ax      ; 부트로더의 시작 주소를 DS 레지스터에 저장  
    mov ax, 0xB800      
    mov es, ax      ; ES 레지스터에 0xB800 (비디오 메모리 어드레스) 지정
    mov si, 0       ; SI 레지스터(문자열 원본 인덱스 레지스터) 초기화    

.SCREENCLEARLOOP:
    mov byte [ es: si ], 0          ; 화면에 아무 문자도 안보이게끔
    mov byte [ es: si + 1 ], 0x06   ; 글자서식을 검정바탕에 노란색으로 지정
    
    add si, 2
    cmp si, 80 * 25 *2
    jl .SCREENCLEARLOOP


; ScreenClearLoop End

    mov si, 0
    mov di, 0
.MESSAGELOOP:
    mov cl, byte [ MESSAGE1 + si ]  ; cl에 메시지의 si번째 문자 복사

    cmp cl, 0                       ; 문자열 끝인지 비교
    je .MESSAGEEND

    mov byte [ es: di ], cl         ; 비디오 메모리에 문자 출력

    add si, 1                       ; 문자는 1Byte씩 카운팅
    add di, 2                       ; 비디오 메모리는 2Byte 씩 넘어가기
    jmp .MESSAGELOOP

.MESSAGEEND:

    jmp $

MESSAGE1: db "CITRON64 OS BootLoader Let's go!", 0 

times 510 - ( $ - $$ )    db  0x00    ;510바이트를 00으로 채움 

db 0x55             ; 
db 0xAA             ; 0x55 0xAA로 부트섹터를 표시함

