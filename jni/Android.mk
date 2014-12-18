LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := mglxuewei

LOCAL_SRC_FILES := \
    Scene/Xuewei/3dxuewei.cpp \
    Scene/Xuewei/xueweiLoader.cpp \
    Scene/Xuewei/3dXueweiLogic.cpp \
    native_main.cpp \
    register_natives.cpp \

LOCAL_LDFLAGS += -Wl,-soname,xuewei.so.1

LOCAL_C_INCLUDES += $(LOCAL_PATH) $(LOCAL_PATH)/../../M-GLEngine/jni/Engine $(LOCAL_PATH)/Scene $(LOCAL_PATH)/include
LOCAL_CFLAGS := -DOPEL_ES -DANDROID_NDK -DGL20
LOCAL_ARM_MODE := arm
LOCAL_LDLIBS += -L$(LOCAL_PATH)/lib -llog -lGLESv1_CM -lGLESv2 -lmglengine -lpng -lzlib -lfreetype 

include $(BUILD_SHARED_LIBRARY)


