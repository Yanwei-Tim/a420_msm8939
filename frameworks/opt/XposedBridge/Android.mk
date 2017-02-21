
LOCAL_PATH:= $(call my-dir)

#MAKE_JAR
include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_MODULE := LovdreamUtil

LOCAL_CERTIFICATE := platform

include $(BUILD_JAVA_LIBRARY)
