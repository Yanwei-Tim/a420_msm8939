# Board specific SELinux policy variable definitions
ifeq ($(call is-vendor-board-platform,QCOM),true)
BOARD_SEPOLICY_DIRS := \
       $(BOARD_SEPOLICY_DIRS) \
       device/qcom/sepolicy \
       device/qcom/sepolicy/common \
       device/qcom/sepolicy/test \
       device/qcom/sepolicy/$(TARGET_BOARD_PLATFORM)

#ifeq ($(call is-board-platform-in-list,$(SSC_TARGET_LIST)),true)
	   BOARD_SEPOLICY_UNION += sensors.te
	   BOARD_SEPOLICY_UNION += sensors_test.te
	   BOARD_SEPOLICY_UNION += stkgesd.te
#endif
endif
