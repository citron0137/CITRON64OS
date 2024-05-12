[ORG 0x00]
[BITS 16]

SECTION .text

;;;;;;;;;;;;;;;;;
; 코드 영역
;;;;;;;;;;;;;;;;;

; 메인
START:
    mov ax, 0x1000
    mov es, ax          ; es를 현재 메모리 주소 기준으로 계산

    jmp $   ; 무한 반복 (임시 코드)

; TODO
;    cli                 ; 인터럽트가 발생하지 않도록 설정
;    lgdt [ GDTR ]       ; GDT 로드

; 함수

;;;;;;;;;;;;;;;;;
; 데이터 영역
;;;;;;;;;;;;;;;;;

align 8, db 0           ;데이터를 8byte에 맞춰 정렬

dw 0x0000               ; GDTR을 8byte에 맞추기 위해 2byte 패딩 
;GDTR
GDTR: 
    dw GDTEND - GDT - 1         ; GDT의 전체 크기 2byte
    dd ( GDT - $$ + 0x10000 )   ; GDT의 시작 주소 4byte

GDT:
    NULL_DESCRIPTOR:
        dw 0x0000
        dw 0x0000
        db 0x00
        db 0x00
        db 0x00
        db 0x00
    
    ; addr
     
    CODE_DESCRIPTOR:
        ; limit(20) : 0xFFFFF
        ; base(32)  : 0x00000000
        ; P=1 (유효한 디스크립터), DPL=0(권한 Hightest), s=1(세그먼트 디스크립터, not 시스템)
        ; 타입=0xA => [0]=1 (코드 세그먼트), [1]=0 접근승인X, [2]=1 (실행&읽기), [3]=0 (접근됨 X)
        ; G=1(세그멘트 디스크립터 가중치 0x4K), D/B=1 (세그멘트 사이즈: 32bit), L=0(추후 IA32-e에서 사용), avl=0(운영체제가 씀)
        dw 0xFFFF   ; limit[15:0]
        dw 0x0000   ; base[15:0]
        db 0x00     ; base[23:16]
        db 0x9A     ; P=1, DPL=0,s=1, 타입=0xA 
        db 0xCF     ; G=1, D/B=1, L=0, limit[19:16]
        db 0x00     ; base[31:24]
    
    DATA_DESCRIPTOR:
        ; limit(20) : 0xFFFFF
        ; base(32)  : 0x00000000
        ; P=1 (유효한 디스크립터), DPL=0(권한 Hightest), s=1(세그먼트 디스크립터, not 시스템)
        ; 타입=0x2 => [0]=0 (코드 세그먼트), [1]=0 접근승인X, [2]=1 (읽기&쓰기), [3]=0 (접근됨 X)
        ; G=1(세그멘트 디스크립터 가중치 0x4K), D/B=1 (세그멘트 사이즈: 32bit), L=0(추후 IA32-e에서 사용), avl=0(운영체제가 씀)
        dw 0xFFFF   ; limit[15:0]
        dw 0x0000   ; base[15:0]
        db 0x00     ; base[23:16]
        db 0x92     ; P=1, DPL=0,s=1, 타입=0x2 
        db 0xCF     ; G=1, D/B=1, L=0, limit[19:16]
        db 0x00     ; base[31:24]
GDTEND:


times 512 - ( $ - $$ ) db 0x00 ; 512 채우기










