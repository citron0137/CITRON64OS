[BITS 64] 

SECTION .text

; import (외부에서 정의된 함수를 쓸 수 있도록)
extern kCommonExceptionHandler, kCommonInterruptHandler, kKeyboardHandler

; Export (예외 처리를 위한 ISR)
global kISRDivideError, kISRDebug, kISRNMI, kISRBreakPoint, kISROverflow
global kISRBoundRangeExceeded, kISRInvalidOpcode, kISRDeviceNotAvailable, kISRDoubleFault
global kISRCoprocessorSegmentOverrun, kISRInvalidTSS, kISRSegmentNotPresent
global kISRStackSegmentFault, kISRGeneralProtection, kISRPageFault, kISR15
global kISRFPUError, kISRAlignmentCheck, kISRMachineCheck, kISRSIMDError, kISRETCException

; Export (인터럽트 처리를 위한 ISR)
global kISRTimer, kISRKeyboard, kISRSlavePIC, kISRSerial2, kISRSerial1, kISRParallel2
global kISRFloppy, kISRParallel1, kISRRTC, kISRReserved, kISRNotUsed1, kISRNotUsed2
global kISRMouse, kISRCoprocessor, kISRHDD1, kISRHDD2, kISRETCInterrupt

; 콘텍스트를 저장하고 셀렉터를 교체하는 매크로
%macro KSAVECONTEXT 0
    ; RBP 레지스터부터 GS 셀렉터까지 모두 스택에 삽입
    push rbp
    mov rbp, rsp
    push rax
    push rbx
    push rcx
    push rdx
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    mov ax, ds
    push rax
    mov ax, es 
    push rax
    push fs
    push gs

    ; 세그먼트 셀렉터 교체
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
%endmacro

; 콘텍스트를 복원하는 매크로
%macro KLOADCONTEXT 0
    ; GS 셀렉터부터 RBP 레지스터까지 모두 스택에서 복원
    pop gs
    pop fs
    pop rax
    mov es, ax
    pop rax
    mov ds, ax
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop rbp
%endmacro

;;;;;;;;;;;;;;;;;;;;;
; 예외 핸들러
;;;;;;;;;;;;;;;;;;;;;

; #0, Divide Error ISR
kISRDivideError:
    KSAVECONTEXT
    mov rdi, 0
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #1, Debug ISR
kISRDebug:
    KSAVECONTEXT
    mov rdi, 1
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #2, NMI ISR
kISRNMI:
    KSAVECONTEXT
    mov rdi, 2
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #3, BreakPoint ISR
kISRBreakPoint:
    KSAVECONTEXT
    mov rdi, 3
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #4, Overflow ISR
kISROverflow:
    KSAVECONTEXT
    mov rdi, 4
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #5, Bound Range Exceeded ISR
kISRBoundRangeExceeded:
    KSAVECONTEXT
    mov rdi, 5
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #6, Invalid Opcode ISR
kISRInvalidOpcode:
    KSAVECONTEXT
    mov rdi, 6
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #7, Device Not Available ISR
kISRDeviceNotAvailable:
    KSAVECONTEXT
    mov rdi, 7
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #8, Double Fault ISR
kISRDoubleFault:
    KSAVECONTEXT
    mov rdi, 8
    mov rsi, qword [ rbp + 8 ]
    call kCommonExceptionHandler
    KLOADCONTEXT
    add rsp, 8
    iretq

; #9, Coprocessor Segment Overrun ISR
kISRCoprocessorSegmentOverrun:
    KSAVECONTEXT
    mov rdi, 9
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #10, Invalid TSS ISR
kISRInvalidTSS:
    KSAVECONTEXT
    mov rdi, 10
    mov rsi, qword [ rbp + 8 ]
    call kCommonExceptionHandler
    KLOADCONTEXT
    add rsp, 8
    iretq

; #11, Segment Not Present ISR
kISRSegmentNotPresent:
    KSAVECONTEXT
    mov rdi, 11
    mov rsi, qword [ rbp + 8 ]
    call kCommonExceptionHandler
    KLOADCONTEXT
    add rsp, 8
    iretq

; #12, Stack Segment Fault ISR
kISRStackSegmentFault:
    KSAVECONTEXT
    mov rdi, 12
    mov rsi, qword [ rbp + 8 ]
    call kCommonExceptionHandler
    KLOADCONTEXT
    add rsp, 8
    iretq

; #13, General Protection ISR
kISRGeneralProtection:
    KSAVECONTEXT
    mov rdi, 13
    mov rsi, qword [ rbp + 8 ]
    call kCommonExceptionHandler
    KLOADCONTEXT
    add rsp, 8
    iretq

; #14, Page Fault ISR
kISRPageFault:
    KSAVECONTEXT
    mov rdi, 14
    mov rsi, qword [ rbp + 8 ]
    call kCommonExceptionHandler
    KLOADCONTEXT
    add rsp, 8
    iretq

; #15, Reserved ISR
kISR15:
    KSAVECONTEXT
    mov rdi, 15
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #16, FPU Error ISR
kISRFPUError:
    KSAVECONTEXT
    mov rdi, 16
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #17, Alignment Check ISR
kISRAlignmentCheck:
    KSAVECONTEXT
    mov rdi, 17
    mov rsi, qword [ rbp + 8 ]
    call kCommonExceptionHandler
    KLOADCONTEXT
    add rsp, 8
    iretq

; #18, Machine Check ISR
kISRMachineCheck:
    KSAVECONTEXT
    mov rdi, 18
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #19, SIMD Floating Point Exception ISR
kISRSIMDError:
    KSAVECONTEXT
    mov rdi, 19
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

; #20~#31, Reserved ISR
kISRETCException:
    KSAVECONTEXT
    mov rdi, 20
    call kCommonExceptionHandler
    KLOADCONTEXT
    iretq

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 인터럽트 헨들러
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# 32, 타이머 ISR
kISRTimer:
    KSAVECONTEXT
    mov rdi, 32
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq
; #33, 키보드 ISR
kISRKeyboard:
    KSAVECONTEXT
    mov rdi, 33
    call kKeyboardHandler
    KLOADCONTEXT
    iretq

; #34, 슬레이브 PIC ISR
kISRSlavePIC:
    KSAVECONTEXT
    mov rdi, 34
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #35, 시리얼 포트 2 ISR
kISRSerial2:
    KSAVECONTEXT
    mov rdi, 35
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #36, 시리얼 포트 1 ISR
kISRSerial1:
    KSAVECONTEXT
    mov rdi, 36
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #37, 패러럴 포트 2 ISR
kISRParallel2:
    KSAVECONTEXT
    mov rdi, 37
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #38, 플로피 디스크 컨트롤러 ISR
kISRFloppy:
    KSAVECONTEXT
    mov rdi, 38
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #39, 패러럴 포트 1 ISR
kISRParallel1:
    KSAVECONTEXT
    mov rdi, 39
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #40, RTC ISR
kISRRTC:
    KSAVECONTEXT
    mov rdi, 40
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #41, 예약된 인터럽트 ISR
kISRReserved:
    KSAVECONTEXT
    mov rdi, 41
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #42, 사용 안 함
kISRNotUsed1:
    KSAVECONTEXT
    mov rdi, 42
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #43, 사용 안 함
kISRNotUsed2:
    KSAVECONTEXT
    mov rdi, 43
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #44, 마우스 ISR
kISRMouse:
    KSAVECONTEXT
    mov rdi, 44
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #45, 코프로세서 ISR
kISRCoprocessor:
    KSAVECONTEXT
    mov rdi, 45
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #46, 하드 디스크 1 ISR
kISRHDD1:
    KSAVECONTEXT
    mov rdi, 46
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #47, 하드 디스크 2 ISR
kISRHDD2:
    KSAVECONTEXT
    mov rdi, 47
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq

; #48 이상의 인터럽트 ISR
kISRETCInterrupt:
    KSAVECONTEXT
    mov rdi, 48
    call kCommonInterruptHandler
    KLOADCONTEXT
    iretq
