[ORG 0x00]
[BITS 16]

SECTION .text

jmp 0x1000:START

SECTORCOUNT: dw 0x0000
TOTALSECTORCOUNT equ 1000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   코드 영역
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
START:
    mov ax, cs
    mov ds, ax
    mov ax, 0xB800
    mov es, ax

    %assign count 0
    %rep TOTALSECTORCOUNT
        %assign count count+1
        
        mov ax, 2
        mul word[SECTORCOUNT]
        mov si, ax
        
        mov byte[es:si + ( 160 * 2 ) ], '0'+(count % 10)
        add word[SECTORCOUNT], 1

        %if count == TOTALSECTORCOUNT
            jmp $
        %else
            jmp (0x1000 + count * 0x20): 0x0000
        %endif

        times (512 - ( $ - $$ ) % 512) db 0x00

    %endrep