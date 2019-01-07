#include "PIC.h"


//PIC 초기화
void kInitializePIC( void ){
    
    // 마스터 PIC 컨트롤러 초기화
    // ICW1 (0x20), IC4 bit(0) = 1
    kOutPortByte(PIC_MASTER_PORT1, 0x11);
    // ICW2 (0x21), 인터럽트 벡터 (0x20)
    kOutPortByte(PIC_MASTER_PORT2, PIC_IRQSTARTVECTOR);
    // ICW3 (0x21), 슬레이브 PIC컨트롤러 핀 (비트로 표현)
    // 마스터 PIC의 2번핀 -> 0x04(비트 2) 로 설정
    kOutPortByte(PIC_MASTER_PORT2, 0x04);
    // ICW4 (0x21), uPM bit(0) = 1
    kOutPortByte(PIC_MASTER_PORT2, 0x01);
    
    //슬레이브 PIC 컨트롤러 초기화
    // ICW1 (0xA0), IC4 bit(0) = 1
    kOutPortByte(PIC_SLAVE_PORT1, 0x11);
    // ICW2 (0xA1), 인터럽트 벡터(0x20 + 8);
    kOutPortByte(PIC_SLAVE_PORT2, PIC_IRQSTARTVECTOR + 8);
    // ICW3 (0xA1), 마스터 PIC컨트롤러 핀(정수)
    // 2번핀 -> 0x02
    kOutPortByte(PIC_SLAVE_PORT2, 0x02);
    // ICW4 (0xA1), uPM bit(0) = 1
    kOutPortByte(PIC_SLAVE_PORT2, 0x01);
}

void kMaskPICInterrupt( WORD wIRQBitmask ){

    // 마스터 PIC컨트롤러에 IMR설정
    // OCW1 (0x21), IRQ 1 ~ IRQ 7
    kOutPortByte(PIC_MASTER_PORT2, (BYTE) wIRQBitmask);

    // 슬레이브 PIC컨트롤러에 IMR 설정
    // OWC2 (0xA1), IRQ 8 ~ IRQ 15
    kOutPortByte(PIC_SLAVE_PORT2, (BYTE) (wIRQBitmask>>8));
}

// 인터럽트 처리가 완료되었음을 전성(EOI)
//      마스터 PIC 컨트롤러 -> 마스터 PIC에만 전송
//      슬레이브 PIC 컨트롤러 -> 슬레이브와 마스터 PIC 둘 다 전송
void kSendEOIToPIC( int iIRQNumber ){
    // 마스터 PIC에 EOI전송
    // OWC2 (0x20), EOI비트( 비트 5) = 1
    kOutPortByte(PIC_MASTER_PORT1, 0x20);
    // 슬레이브 PIC컨트롤러일 경우 슬레이브 PIC에 EOI 전송
    if(iIRQNumber >= 8){
        //OCW (0xA0), EOI (5) = 1
        kOutPortByte(PIC_SLAVE_PORT1, 0x20);
    }
}