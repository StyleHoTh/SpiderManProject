#pragma once

#ifdef _IS_WINDOWS_
	#include "AllowWindowsPlatformTypes.h" 
#endif

#include <google/protobuf/message_lite.h>

//include other header file
//#include "login.pb.h"

#include <DataContainer.pb.h>


//using namespace fh_proto;
using namespace proto;
using namespace google;

typedef const ::google::protobuf::RepeatedField< ::google::protobuf::int32 > protoarray_int;
typedef const ::google::protobuf::RepeatedPtrField< ::std::string> protoarray_string;


#ifdef _IS_WINDOWS_
	#include "HideWindowsPlatformTypes.h" 
#endif

