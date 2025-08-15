#ifndef __INTERRUPT_HANDLER_H__
#define __INTERRUPT_HANDLER_H__

#include "Types.h"

void kCommonExceptionHandler( int iExceptionNumber, QWORD qwErrorCode );
void kCommonInterruptHandler( int iInterruptNumber );
void kKeyboardHandler( int iInterruptNumber );

#endif // __INTERRUPT_HANDLER_H__