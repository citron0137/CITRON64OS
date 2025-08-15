#ifndef __PIC_H__
#define __PIC_H__

#include "Types.h"

#define PIC_MASTER_PORT1    0X20   // 마스터 PIC의 명령 포트 (OCW/ICW 전송)
#define PIC_MASTER_PORT2    0X21   // 마스터 PIC의 데이터 포트 (ICW2~4, OCW1)
#define PIC_SLAVE_PORT1     0xA0   // 슬레이브 PIC의 명령 포트
#define PIC_SLAVE_PORT2     0xA1   // 슬레이브 PIC의 데이터 포트

#define PIC_IRQSTARTVECTOR  0x20   // 리맵 시작 벡터(IRQ0 → 0x20). 0x20~0x2F 사용

void kInitializePIC( void );
void kMaskPICInterrupt( WORD wIRQBitMask );
void kSendEOIToPIC( int iIRQNumber );

#endif // __PIC_H__