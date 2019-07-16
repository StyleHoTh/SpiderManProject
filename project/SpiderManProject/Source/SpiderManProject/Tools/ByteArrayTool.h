/*
* Copyright(c) 2018 WindSoul Network Technology, Inc. All rights reserved.
*/

/**
* Desc: 字节流操作工具类
* Author:
* Date: 2018-04-24
* Time: 17:41
*/

#ifndef	__BYTEARRAYTOOL_H__
#define	__BYTEARRAYTOOL_H__

#include "CoreMinimal.h"

class ByteArrayTool
{
public:
	static void IntToByte(char* buf, int index, int value);
	static void FloatToByte(char* buf, int index, float value);
	static void LongToByte(char* buf, int index, long value);
	static long IntToLong(long int1, long int2);
	static int ReadInt(const char* buf, int index);
	static float ReadFloat(const char* buf, int index);
	static long ReadLong(const char* buf, int index);
	static void ReadString(const char* buf, int index, int len, char* val);

	//TChar转Char数组
	static void TCharToCharArray(const TCHAR* Src, int SrcLen, char* Dest, int DestLen);
};

#endif
