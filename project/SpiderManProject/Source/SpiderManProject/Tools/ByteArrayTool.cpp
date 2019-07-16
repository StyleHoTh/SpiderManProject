/*
* Copyright(c) 2018 WindSoul Network Technology, Inc. All rights reserved.
*/

/**
 * Desc: 字节流操作工具类
 * Author:
 * Date: 2018-04-24
 * Time: 17:41
 */


#include "ByteArrayTool.h"

void ByteArrayTool::IntToByte( char* buf, int index, int value )
{
    buf[index] = ( char )( value & 0xff );
    buf[index + 1] = ( char )( ( value & 0xff00 ) >> 8 );
    buf[index + 2] = ( char )( ( value & 0xff0000 ) >> 16 );
    buf[index + 3] = ( char )( ( value & 0xff000000 ) >> 24 );
}

void ByteArrayTool::FloatToByte( char* buf, int index, float value )
{
    char* ivalue = ( char* )&value;
    buf[index] = ivalue[0];
    buf[index + 1] = ivalue[1];
    buf[index + 2] = ivalue[2];
    buf[index + 3] = ivalue[3];
}

void ByteArrayTool::LongToByte( char* buf, int index, long value )
{
    int int1 = ( int )( value & 0x7FFFFFFF );
    int int2 = ( int )( ( value - int1 ) >> 31 );

    IntToByte( buf, index, int2 );
    IntToByte( buf, index + 4, int1 );
}

long ByteArrayTool::IntToLong( long int1, long int2 )
{
    long a = int1 << 31;
    a = a | int2;
    return a;
}

int ByteArrayTool::ReadInt( const char* buf, int index )
{
    int d1 = buf[index + 3];
    d1 = d1 >= 0 ? d1 : 256 + d1;
    d1 = d1 << 24;

    int d2 = buf[index + 2];
    d2 = d2 >= 0 ? d2 : 256 + d2;
    d2 = d2 << 16;

    int d3 = buf[index + 1];
    d3 = d3 >= 0 ? d3 : 256 + d3;
    d3 = d3 << 8;

    int d4 = buf[index + 0];
    d4 = d4 >= 0 ? d4 : 256 + d4;

    return d1 + d2 + d3 + d4;
}

float ByteArrayTool::ReadFloat( const char* buf, int index )
{
    float val = 0;
    char* b_f = ( char* )&val;
    b_f[0] = buf[index];
    b_f[1] = buf[index + 1];
    b_f[2] = buf[index + 2];
    b_f[3] = buf[index + 3];

    return val;
}

long ByteArrayTool::ReadLong( const char* buf, int index )
{
    long int1 = ReadInt( buf, index );
    long int2 = ReadInt( buf, index + 4 );

    return IntToLong( int1, int2 );
}

void ByteArrayTool::ReadString( const char* buf, int index, int len, char* val )
{
    for( int i = index, j = 0; i < index + len; i++, j++ )
    {
        val[j] = buf[i];
    }
}

void ByteArrayTool::TCharToCharArray(const TCHAR* Src, int SrcLen, char* Dest, int DestLen)
{
	if (SrcLen != DestLen)
	{
		return;
	}

	for (int i = 0; i < SrcLen; i++)
	{
		Dest[i] = Src[i];
	}
}
