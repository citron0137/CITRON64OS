[ORG 0x00]          ; 코드의 시작 어드레스를 0x00으로 설정
[BITS 16]           ; 16비트 코드로 설정

SECTION .text       ; text섹션 정의

jmp 0x07C0:START    ; 0x07C0(부트로더 영역)으로 CS 레지스터 지정 및 START로 이동

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 환경 설정 값
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
TOTALSECTORCOUNT:   dw 1024     ; 부트로더를 제외한 MINT64 OS 크기 
                                ; 추후 쉬운 변경을 위해 앞쪽에 위치시킴

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Main 코드 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
START:
    ; CS(코드영역), ES (비디오 메모리 어드레스) 지정
    mov ax, 0x07C0
    mov ds, ax      ; 부트로더의 시작 주소를 DS 레지스터에 저장  
    mov ax, 0xB800      
    mov es, ax      ; ES 레지스터에 0xB800 (비디오 메모리 어드레스) 지정

    ; 스택 지정 (0x0000:0000~0x0000:FFFF)
    mov ax, 0x0000
    mov ss, ax
    mov sp, 0xFFFE
    mov bp, 0xFFFE

; 화면 지우기 
    mov si, 0       ; SI 레지스터(문자열 원본 인덱스 레지스터) 초기화    
.SCREENCLEARLOOP:
    mov byte [ es: si ], 0          ; 화면에 아무 문자도 안보이게끔
    mov byte [ es: si + 1 ], 0x06   ; 글자서식을 검정바탕에 노란색으로 지정    
    add si, 2
    cmp si, 80 * 25 * 2 ; 화면 전체 초기화
    jl .SCREENCLEARLOOP

; 화면 상단에 시작 메시지 출력
    push MESSAGE1           ; 출력 메시지
    push 0                  ; Y 좌표
    push 0                  ; X 좌표
    call PRINTMESSAGE
    add sp, 6               ; 스택 정리

; 이미지 로딩 메시지 출력 
    push IMAGELOADINGMESSAGE
    push 1
    push 0
    call PRINTMESSAGE
    add sp, 6
    
    jmp $

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 함수 코드 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


PRINTMESSAGE: 
    push bp
    mov bp, sp
    push es
    push si
    push di
    push ax
    push cx
    push dx

    ; 비디오 메모리 어드레스 지정
    mov ax, 0xB800
    mov es, ax

    ; 라인 주소구하기
    mov ax, word [ bp + 6 ] ; Y 좌표
    mov si, 160             ; 
    mul si                  ; * 160
    mov di, ax              ; di에 저장

    ; X좌표 x2로 들여쓰기 주소 구하기
    mov ax, word [ bp + 4 ] ; X 좌표
    mov si, 2               ;
    mul si                  ; * 2
    add di, ax              ; di에 더하기

    ; 출력할 문자열 주소 
    mov si, word [ bp + 8 ]

    ;출력 반복문
.MESSAGELOOP:
    mov cl, byte [ si ] ; 한 단어 복사
    cmp cl, 0           ; 0(끝) 이면 Break
    je .MESSAGEEND
    
    mov byte [ es: di ], cl ; 한글자를 해당 위치(es:di)에 출력
    
    add si, 1               ; 문자열 포인터는 1Byte씩 증가
    add di, 2               ; 비디오 메모리 포인터는 2Byte씩 증가
    jmp .MESSAGELOOP
.MESSAGEEND:
    
    ; 복귀 코드
    pop dx
    pop cx
    pop ax
    pop di
    pop si
    pop es
    pop bp
    ret 

; PRINTMESSAGE 종료 
    

MESSAGE1: db "CITRON64 OS BootLoader Let's go!", 0 
IMAGELOADINGMESSAGE: db 'Image Loading...', 0

times 510 - ( $ - $$ )    db  0x00    ;510바이트를 00으로 채움 

db 0x55             ; 
db 0xAA             ; 0x55 0xAA로 부트섹터를 표시함

