#include "Types.h"

void kPrintString( int iX, int iY, const char* pcString );
void kPrintStringWithCheckBox( int iY, const char* pcString );
void kFillCheckBox( int iY, const char* pcString );

void Main( void ){
    kFillCheckBox( 10, "Pass" );
    while(1);
}

void kPrintString( int iX, int iY, const char* pcString ){
    CHARACTER* pstScreen = ( CHARACTER* ) 0xB8000; 
    pstScreen += ( iY * 80 ) + iX;
    for( int i = 0; pcString[i] != 0; i++ )
    {
        pstScreen[ i ].bCharactor = pcString[ i ];
    }
}
void kPrintStringWithCheckBox( int iY, const char* pcString ){
    kPrintString( 0, iY, "............................................[    ]"); 
    kPrintString( 0, iY, pcString );
}

void kFillCheckBox( int iY, const char* pcString ){
    kPrintString( 45, iY, pcString );
}
