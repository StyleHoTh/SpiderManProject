/*
* Copyright(c) 2018 WindSoul Network Technology, Inc. All rights reserved.
*/

/**
* Desc: google protobuf的工具类
* Author:
* Date: 2018-10-17
* Time: 20:56
*/

#ifndef	__ProtobufHelper_H__
#define	__ProtobufHelper_H__

#include <google/protobuf/message_lite.h>
#include <google/protobuf/io/coded_stream.h>
#include "CoreMinimal.h"

class ProtobufHelper
{
public:

	/*用来替代MessageListe::ParseFromArray()的工具函数。作用是为了解决Android NDK中调用ParseFromArray会崩溃的问题，在windows下不会。
	原因不清楚，估计是UE4下编译NDK与常规android ndk编译有什么特殊之处。
	*/
	static bool Parse(::google::protobuf::MessageLite& Message, const void* Data, int Size)
	{
		::google::protobuf::io::CodedInputStream input(static_cast<const uint8*>(Data), Size);

		Message.Clear();

		if (!Message.MergePartialFromCodedStream(&input))
		{
			return false;
		}
		
		if (!Message.IsInitialized()) 
		{
			//GOOGLE_LOG(ERROR) << InitializationErrorMessage("parse", *message);
			UE_LOG(LogTemp, Error, TEXT("protobuf message isn't initialized."));
			return false;
		}
		return true;
	}
};

#endif
