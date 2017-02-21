DEVICE_PACKAGE_OVERLAYS := device/qcom/msm8939_64_p805/overlay

TARGET_USES_QCOM_BSP := true
# Add QC Video Enhancements flag
TARGET_ENABLE_QC_AV_ENHANCEMENTS := true

DEVICE_PACKAGE_OVERLAYS := device/qcom/msm8939_64_p805/overlay

#QTIC flag
-include $(QCPATH)/common/config/qtic-config.mk

# splash img
PRODUCT_COPY_FILES += \
    device/qcom/msm8939_64_p805/splash.img:splash.img

# wangqing.yu add for 12 pin
PRODUCT_COPY_FILES += \
    device/qcom/msm8939_64_p805/chmod_dev.sh:system/etc/chmod_dev.sh

# media_profiles and media_codecs xmls for 8916
ifeq ($(TARGET_ENABLE_QC_AV_ENHANCEMENTS), true)
PRODUCT_COPY_FILES += device/qcom/msm8916_32/media/media_profiles_8916.xml:system/etc/media_profiles.xml \
                      device/qcom/msm8916_32/media/media_codecs_8916.xml:system/etc/media_codecs.xml \
                      device/qcom/msm8916_32/media/media_codecs_performance_8916_64.xml:system/etc/media_codecs_performance.xml \
                      device/qcom/msm8916_32/media/media_codecs_performance_8929.xml:system/etc/media_codecs_performance_8929.xml \
                      device/qcom/msm8916_32/media/media_codecs_8939.xml:system/etc/media_codecs_8939.xml \
                      device/qcom/msm8916_32/media/media_codecs_performance_8916_64_8939.xml:system/etc/media_codecs_performance_8939.xml \
                      device/qcom/msm8916_32/media/media_codecs_8929.xml:system/etc/media_codecs_8929.xml
endif

#TARGET_USES_QCA_NFC := false

PRODUCT_PROPERTY_OVERRIDES += \
           dalvik.vm.heapgrowthlimit=128m
$(call inherit-product, device/qcom/common/common64.mk)

PRODUCT_NAME := msm8939_64_p805
PRODUCT_DEVICE := msm8939_64_p805
PRODUCT_BRAND := Android
PRODUCT_MODEL := MSM8939 for arm64

ifeq ($(strip $(TARGET_USES_QTIC)),true)
# font rendering engine feature switch
-include $(QCPATH)/common/config/rendering-engine.mk
ifneq (,$(strip $(wildcard $(PRODUCT_RENDERING_ENGINE_REVLIB))))
#    MULTI_LANG_ENGINE := REVERIE
endif
endif

PRODUCT_BOOT_JARS += qcmediaplayer \
                     WfdCommon \
                     qcom.fmradio \
                     oem-services
PRODUCT_BOOT_JARS += vcard
PRODUCT_BOOT_JARS += tcmiface

# default is nosdcard, S/W button enabled in resource
PRODUCT_CHARACTERISTICS := nosdcard

#Android EGL implementation
PRODUCT_PACKAGES += libGLES_android

PRODUCT_PACKAGES += \
    libqcomvisualizer \
    libqcompostprocbundle \
    libqcomvoiceprocessing

# Audio configuration file
PRODUCT_COPY_FILES += \
    device/qcom/msm8916_32/audio_policy.conf:system/etc/audio_policy.conf \
    device/qcom/msm8916_32/audio_effects.conf:system/vendor/etc/audio_effects.conf \
    device/qcom/msm8916_32/mixer_paths_mtp.xml:system/etc/mixer_paths_mtp.xml \
    device/qcom/msm8916_32/mixer_paths_sbc.xml:system/etc/mixer_paths_sbc.xml \
    device/qcom/msm8916_32/mixer_paths_qrd_skuh.xml:system/etc/mixer_paths_qrd_skuh.xml \
    device/qcom/msm8916_32/mixer_paths_qrd_skui.xml:system/etc/mixer_paths_qrd_skui.xml \
    device/qcom/msm8916_32/mixer_paths_qrd_skuhf.xml:system/etc/mixer_paths_qrd_skuhf.xml \
    device/qcom/msm8916_32/mixer_paths_wcd9306.xml:system/etc/mixer_paths_wcd9306.xml \
    device/qcom/msm8939_64_p805/mixer_paths_skuk.xml:system/etc/mixer_paths_skuk.xml \
    device/qcom/msm8916_32/mixer_paths_skul.xml:system/etc/mixer_paths_skul.xml \
    device/qcom/msm8916_32/mixer_paths.xml:system/etc/mixer_paths.xml \
    device/qcom/msm8916_32/sound_trigger_mixer_paths.xml:system/etc/sound_trigger_mixer_paths.xml \
    device/qcom/msm8916_32/sound_trigger_mixer_paths_wcd9306.xml:system/etc/sound_trigger_mixer_paths_wcd9306.xml \
    device/qcom/msm8916_32/sound_trigger_platform_info.xml:system/etc/sound_trigger_platform_info.xml \
    device/qcom/msm8939_64_p805/aanc_tuning_mixer.txt:system/etc/aanc_tuning_mixer.txt

# MIDI feature
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.software.midi.xml:system/etc/permissions/android.software.midi.xml

#ANT+ stack
PRODUCT_PACKAGES += \
    AntHalService \
    libantradio \
    antradio_app
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    camera2.portability.force_api=1

PRODUCT_PACKAGES += wcnss_service
#add by shaozhaochuang for sensor so
PRODUCT_PACKAGES += libcalmodule_common
# MSM IRQ Balancer configuration file
PRODUCT_COPY_FILES += \
    device/qcom/msm8939_64_p805/msm_irqbalance.conf:system/vendor/etc/msm_irqbalance.conf

# MSM Thermal  Balancer configuration file
#PRODUCT_COPY_FILES += \
#    device/qcom/msm8939_64_p805/thermal-engine.conf:system/etc/thermal-engine.conf

#wlan driver
PRODUCT_COPY_FILES += \
    device/qcom/msm8939_64_p805/WCNSS_qcom_cfg.ini:system/etc/wifi/WCNSS_qcom_cfg.ini \
    device/qcom/msm8939_64_p805/WCNSS_wlan_dictionary.dat:persist/WCNSS_wlan_dictionary.dat \
    device/qcom/msm8939_64_p805/WCNSS_qcom_wlan_nv.bin:persist/WCNSS_qcom_wlan_nv.bin

PRODUCT_PACKAGES += \
    wpa_supplicant_overlay.conf \
    p2p_supplicant_overlay.conf

#ifeq ($(TARGET_USES_QCA_NFC),true)
#NFC_D := false
#
#ifeq ($(NFC_D), true)
#    PRODUCT_PACKAGES += \
#        libqnfc-nci \
#        libqnfc_nci_jni \
#        nfc_nci.msm8916 \
#        QNfc \
#        Tag \
#        com.android.nfc_extras \
#        com.android.nfc.helper \
#        SmartcardService \
#        org.simalliance.openmobileapi \
#        org.simalliance.openmobileapi.xml \
#        libassd
#else
PRODUCT_PACKAGES += \
    libnfc-nci \
    libnfc_nci_jni \
     nfc_nci.pn54x.default \
     com.gsma.services.nfc \
    NfcNci \
    Tag \
    com.android.nfc_extras \
    HitownBattery
#endif

################   NFC  PN547 #############################
##added by yuanwei 2015??¡ìo3??5?¡ì?¡ì?10:59:05
##added by yuanwei
# file that declares the MIFARE NFC constant
# Commands to migrate prefs from com.android.nfc3 to com.android.nfc
# NFC access control + feature files + configuration
PRODUCT_COPY_FILES += \
        packages/apps/Nfc/migrate_nfc.txt:system/etc/updatecmds/migrate_nfc.txt \
        frameworks/native/data/etc/com.nxp.mifare.xml:system/etc/permissions/com.nxp.mifare.xml \
        frameworks/native/data/etc/com.android.nfc_extras.xml:system/etc/permissions/com.android.nfc_extras.xml \
        frameworks/native/data/etc/android.hardware.nfc.xml:system/etc/permissions/android.hardware.nfc.xml \
        frameworks/native/data/etc/android.hardware.nfc.hce.xml:system/etc/permissions/android.hardware.nfc.hce.xml
#endif # TARGET_USES_QCA_NFC


PRODUCT_COPY_FILES += \
					  device/qcom/common/nfc/Firmware/libpn547_fw_08_01_27_prod_plm_64bits.so:system/vendor/firmware/libpn547_fw.so \
					  device/qcom/common/nfc/Firmware/nxp-ALM.rf:system/vendor/firmware/nxp-ALM.rf \
					  device/qcom/common/nfc/Firmware/nxp-PLM.rf:system/vendor/firmware/nxp-PLM.rf \
					  device/qcom/common/nfc/param/route.xml:system/etc/param/route.xml \
					  device/qcom/common/nfc/etc/pn547/libnfc-nxp.conf:system/etc/libnfc-nxp.conf \
					  device/qcom/common/nfc/etc/pn547/libnfc-brcm.conf:system/etc/libnfc-brcm.conf
#############   NFC  PN547 #############################


# Defined the locales
# PRODUCT_LOCALES += th_TH vi_VN tl_PH hi_IN ar_EG ru_RU tr_TR pt_BR bn_IN mr_IN ta_IN te_IN zh_HK \
#         in_ID my_MM km_KH sw_KE uk_UA pl_PL sr_RS sl_SI fa_IR kn_IN ml_IN ur_IN gu_IN or_IN
# add lauguages by zzj start
PRODUCT_LOCALES := en_US en_GB zh_CN zh_HK fr_FR de_DE it_IT ko_KR ja_JP pt_PT pt_BR ru_RU es_ES el_GR 
# add lauguages by zzj end
# Add the overlay path
ifeq ($(strip $(TARGET_USES_QTIC)),true)
PRODUCT_PACKAGE_OVERLAYS := $(QCPATH)/qrdplus/Extension/res-overlay \
        $(PRODUCT_PACKAGE_OVERLAYS)
endif

PRODUCT_SUPPORTS_VERITY := true
PRODUCT_SYSTEM_VERITY_PARTITION := /dev/block/bootdevice/by-name/system
#wsl added for akm cali lib start
#PRODUCT_COPY_FILES += \
#	hardware/akm/pdc_p800.txt:/system/vendor/etc/pdc.txt
#wsl added for akm cali lib end
