
LOCAL_PATH := $(call my-dir) 

include $(CLEAR_VARS)  
  
LOCAL_MODULE := libexcelformat-ndk
LOCAL_MODULE_TAGS := optional  
  
LOCAL_CPP_EXTENSION := .cc  
  
#LOCAL_SRC_FILES += \
#$(CC_LITE_SRC_FILES)                                         

MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/protoc_files/*.cc)
LOCAL_SRC_FILES += $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)
  
LOCAL_CFLAGS := -march=armv7-a -mfloat-abi=softfp -DGOOGLE_PROTOBUF_NO_RTTI     #-DGOOGLE_PROTOBUF_NO_RTTI  
LOCAL_CFLAGS += -std=gnu++11

LOCAL_C_INCLUDES += ../../protobuf/include

LOCAL_STATIC_LIBRARIES += ../../protobuf/lib/libprotobuf-lite-ndk.a
  
include $(BUILD_STATIC_LIBRARY)  