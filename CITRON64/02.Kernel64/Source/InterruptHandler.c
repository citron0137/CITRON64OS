#include "InterruptHandler.h"
#include "PIC.h"

void kCommonExceptionHandler( int iExceptionNumber, QWORD qwErrorCode )
{
    char vcBuffer[ ] = "Error Code :      ";

    vcBuffer[ 11 ] = '0' + iExceptionNumber / 10;
    vcBuffer[ 12 ] = '0' + iExceptionNumber % 10;

    kPrintDivider( 0 );
    kPrintBlankLine( 1 );
    kPrintBlankLine( 2 );
    kPrintDivider( 3 );
    kPrintString( 10, 1, "Exception" );
    kPrintString( 10, 2, vcBuffer );

    while(1);
}

void kCommonInterruptHandler( int iInterruptNumber )
{
    char vcBuffer[ ] = "[INT:  ,   ]";
    static int g_iCommonInterruptCount = 0;
    g_iCommonInterruptCount = (g_iCommonInterruptCount+1)%100;

    vcBuffer[ 5 ] = '0' + iInterruptNumber / 10;
    vcBuffer[ 6 ] = '0' + iInterruptNumber % 10;
    vcBuffer[ 9 ] = '0' + g_iCommonInterruptCount / 10;
    vcBuffer[ 10 ] = '0' + g_iCommonInterruptCount % 10;

    kPrintOnRightTop( vcBuffer );

    kSendEOIToPIC( iInterruptNumber - PIC_IRQSTARTVECTOR );
}

void kKeyboardHandler( int iInterruptNumber )
{
    char vcBuffer[ ] = "[KEY:  ,  ]";
    static int g_iKeyboardCount = 0;
    g_iKeyboardCount = (g_iKeyboardCount+1)%100;

    vcBuffer[ 5 ] = '0' + g_iKeyboardCount / 10;
    vcBuffer[ 6 ] = '0' + g_iKeyboardCount % 10;
    vcBuffer[ 9 ] = '0' + iInterruptNumber / 10;
    vcBuffer[ 10 ] = '0' + iInterruptNumber % 10;

    kPrintString( 0, 0, vcBuffer );
    kSendEOIToPIC( iInterruptNumber - PIC_IRQSTARTVECTOR );
}