#include "PIC.h"

void kInitializePIC(void)
{
    // <Master PIC 초기화 순서>
    // ICW1 (0x11): 초기화 시작(1) + ICW4 존재(1) + 레벨 트리거 아님(LTIM=0) + 카스케이드 구성(SNGL=0)
    //  - 비트: 7..5=0(예약), 4=1(INIT), 3=0(LTIM=edge), 2=0(ADI=4바이트 간격), 1=0(SNGL=cascade), 0=1(IC4=ICW4 존재)
    kOutPortByte( PIC_MASTER_PORT1, 0x11);

    // ICW2: 마스터 PIC의 인터럽트 벡터 오프셋(IRQ0의 벡터 번호). 0x20(32)로 설정
    //  - CPU 예외가 사용하는 0x00~0x1F(0~31)과 겹치지 않도록 0x20 이상으로 설정해야 함
    kOutPortByte( PIC_MASTER_PORT2, PIC_IRQSTARTVECTOR);

    // ICW3(마스터): 어느 IRQ 라인에 슬레이브가 연결되었는지 비트마스크로 지정
    //  - 슬레이브는 마스터의 IRQ2에 체인 → 0x04(2^2)
    kOutPortByte( PIC_MASTER_PORT2, 0x04);

    // ICW4: 추가 동작 모드 설정
    //  - 0x01: 8086/88 모드(1), 자동 EOI 비활성(0), 버퍼 모드 미사용(0), 특수 중첩 모드 미사용(0)
    kOutPortByte( PIC_MASTER_PORT2, 0x01);

    // <Slave PIC 초기화 순서>
    // ICW1 (0x11): 마스터와 동일하게 초기화(카스케이드, 엣지 트리거, ICW4 존재)
    kOutPortByte( PIC_SLAVE_PORT1, 0x11);

    // ICW2: 슬레이브 PIC의 인터럽트 벡터 오프셋. 마스터 오프셋 + 8 → 0x28(40)
    //  - 슬레이브의 IRQ8~IRQ15가 0x28~0x2F를 사용
    kOutPortByte( PIC_SLAVE_PORT2, PIC_IRQSTARTVECTOR+0x08);

    // ICW3(슬레이브): 자신이 마스터의 어느 IRQ 라인에 붙었는지 번호 지정
    //  - 마스터의 IRQ2에 연결 → 0x02
    kOutPortByte( PIC_SLAVE_PORT2, 0x02);

    // ICW4: 8086/88 모드 사용, 자동 EOI 비활성 등 (마스터와 동일 설정)
    kOutPortByte( PIC_SLAVE_PORT2, 0x01);

    // 참고: 초기화 직후 IRQ 마스크(OCW1)는 기존 값이 유지되므로,
    //       필요한 IRQ 라인을 개별적으로 언마스크하는 코드가 별도로 필요하다.
}

void kMaskPICInterrupt( WORD wIRQBitMask )
{
    // 마스터 PIC 컨트롤러에 IMR 설정
    // OCW1 명령 전송 후 데이터 포트에 마스크 값 전송
    kOutPortByte( PIC_MASTER_PORT2, (BYTE)(wIRQBitMask));

    // 슬레이브 PIC 컨트롤러에 IMR 설정
    // OCW1 명령 전송 후 데이터 포트에 마스크 값 전송
    kOutPortByte( PIC_SLAVE_PORT2, (BYTE)(wIRQBitMask >> 8));
}

void kSendEOIToPIC( int iIRQNumber )
{
    // 마스터 PIC에 EOI(5=1) 전송
    kOutPortByte( PIC_MASTER_PORT1, 0x20);

    // 슬레이브 PIC에 EOI(5=1) 전송
    if( iIRQNumber >= 8 )
        kOutPortByte( PIC_SLAVE_PORT1, 0x20);
}