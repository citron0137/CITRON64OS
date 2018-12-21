[ORG 0x00]
[BITS 16]

SECTION .text

jmp 0x07C0:START

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; CITRON64 OS에 관련된 환경 설정 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
TOTALSECTORCOUNT: dw 10

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 코드 시작
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
START:
    mov ax, 0x07C0
    mov ds, ax
    mov ax, 0xB800
    mov es, ax

    mov ax, 0x0000
    mov ss, ax
    mov sp, 0xFFFE
    mov bp, 0xFFFE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;화면 지우고, 속성(검정바탕 녹색글씨) 설정
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov si, 0

.SCREENCLEARLOOP:
    mov byte[es:si], 0
    mov byte[es:si+1], 0x0A

    add si, 2

    cmp si, 80*25*2

    jl .SCREENCLEARLOOP

    mov si, 0
    mov di, 0
    ;시작 메세지 출력
    push MESSAGE1
    push 0
    push 0
    call PRINTMESSAGE
    add sp, 6

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; OS를 로딩시작 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;로딩을 시작한다는 메세지 출력
    push IMAGELOADINGMESSAGE
    push 1
    push 0
    call PRINTMESSAGE
    add sp, 6

    ;TODO 디스크에서 OS이미지 로딩
    
    ;디스크를 읽기 전에 먼저 리셋
RESETDISK:
    ;BIOS Reset Function 호출
    mov ax, 0
    mov dl, 0
    int 0x13
    jc HANDLEDISKERROR

    ;디스크에서 섹터 읽음
    mov si, 0x1000
    mov es, si
    mov bx, 0x0000
    mov di, word[TOTALSECTORCOUNT]

READDATA:
    cmp di, 0
    je READEND
    sub di, 0x1

    ;BIOS Read Function 호출
    mov ah, 0x02
    mov al, 0x1
    mov ch, byte[TRACKNUMBER]
    mov cl, byte[SECTORNUMBER]
    mov dh, byte[HEADNUMBER]
    mov dl, 0x00
    int 0x13
    jc HANDLEDISKERROR

    ;복사할 어디레스와 트랙, 헤드, 섹터 어드레스 계산
    add si, 0x0020
    mov es, si

    mov al, byte[SECTORNUMBER]
    add al, 0x01
    mov byte[SECTORNUMBER], al
    cmp al, 19
    jl READDATA

    xor byte[HEADNUMBER], 0x01
    mov byte[SECTORNUMBER], 0x01

    cmp byte[HEADNUMBER], 0x00
    jne READDATA

    add byte[TRACKNUMBER], 0x01
    jmp READDATA

READEND:
    ;OS이미지가 완료되었다는 메세지 출력
    push LOADINGCOMPLETEMESSAGE
    push 1
    push 20
    call PRINTMESSAGE
    add sp,6

    jmp 0x1000:0x0000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   함수 영역
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

HANDLEDISKERROR:    ;디스크 에러 처리
    push DISKERRORMESSAGE
    push 1
    push 20
    CALL PRINTMESSAGE
    jmp $

PRINTMESSAGE:       ;메세제 출력 함수 PRINTMESSAGE(X, Y, STRING)
    push bp
    mov bp, sp

    push es
    push si
    push di
    push ax
    push cx
    push dx

    ; ES 레지스터에 비디오 모드 어드레스 설정
    mov ax, 0xB800
    mov es, ax

    ; x,y좌표로 위치 계산
    mov ax, word[bp+6]
    mov si, 160
    mul si
    mov di, ax

    mov ax, word[bp+4]
    mov si, 2
    mul si
    add di, ax

    mov si, word[bp+8]

.MESSAGELOOP:
    mov cl, byte[si]
    cmp cl, 0
    je .MESSAGEEND

    mov byte[es:di], cl
    add si, 1
    add di, 2
    jmp .MESSAGELOOP

.MESSAGEEND:
    pop dx
    pop cx
    pop ax
    pop di
    pop si
    pop es
    pop bp
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   데이터 영역
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

MESSAGE1: db 'CITRON64 OS Boot Loader Start', 0

DISKERRORMESSAGE: db 'DISK Error', 0
IMAGELOADINGMESSAGE: db 'OS Image Loading...', 0
LOADINGCOMPLETEMESSAGE: db 'Complete', 0

SECTORNUMBER: db 0x02
HEADNUMBER: db 0x00
TRACKNUMBER: db 0x00

times 510 - ($ - $$) db 0x00

db 0x55
db 0xAA