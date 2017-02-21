ifeq (, $(filter msm8939_64_p800 msm8916_64_a538u msm8939_64_p803 msm8939_64_s700 msm8916_64_a420, $(TARGET_PRODUCT)))

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := samples

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_PACKAGE_NAME := Home

LOCAL_SDK_VERSION := current

include $(BUILD_PACKAGE)

endif
