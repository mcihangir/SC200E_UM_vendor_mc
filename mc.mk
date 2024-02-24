# Usage: include this file to QSSI.12/device/qcom/qssi/qssi.mk
# include device/mcdevice/mcdevice.mk

include $(call all-subdir-makefiles)
LOCAL_PATH := $(call my-dir)

#PRODUCT_NAME := mcdevice
#PRODUCT_DEVICE := mcdevice
#PRODUCT_BRAND := Android
#PRODUCT_MODEL := AOSP on qcm2290
#PRODUCT_MANUFACTURER := MC
#PRODUCT_RESTRICT_VENDOR_FILES := true
PRODUCT_MODEL := qcom/qssi customized model for mcdevice
######################################################################
PRODUCT_MODEL := MC Device
DEVICE_PACKAGE_OVERLAYS += device/mcdevice/overlays
BOARD_SEPOLICY_DIRS += device/mcdevice/sepolicy
#BOARD_SEPOLICY_UNION, defines files that should be combined with existing files from AOSP of the same name.
#BOARD_SEPOLICY_UNION += file_contexts \
#						service_context \
#						mcdevice.te 
# System properties for mcdevice
#TARGET_SYSTEM_PROP += device/mcdevice/system.prop

######################################################################
# mcdevice init scripts
######################################################################
# Bu örnek, init_mcdevice.rc dosyasını hedef cihaza kopyalar ve başlatma sırasında çalıştırır
# Özel rc dosyanızı hedef cihaza kopyalamak için PRODUCT_COPY_FILES kullanın
# copy init.mcdevice.system.rc to /system/etc/init folder in the target file system
PRODUCT_COPY_FILES += \
    device/mcdevice/mcdevice.rc:/system/etc/init/mcdevice.rc 
# init_mcdevice.rc dosyasını başlatma sırasında çalıştırmak için INIT etiketini kullanın
INIT += /system/etc/init/mcdevice.rc

######################################################################
# Add the following Packages
######################################################################
PRODUCT_PACKAGES += mchello \
					com.example.ndkdemo



