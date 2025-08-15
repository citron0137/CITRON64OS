#ifndef __STDIO_H__
#define __STDIO_H__

#include "Types.h"

// 문자열 출력 함수들
void kPrintString( int iX, int iY, const char* pcString );
void kPrintStringWithCheckBox( int iY, const char* pcString );
void kFillCheckBox( int iY, const char* pcString );
void kPrintDivider( int iY );
void kPrintBlankLine( int iY );
void kPrintOnRightTop( const char* pcString );

#endif
