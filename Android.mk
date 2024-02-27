#
# This make file will be processed by the build system as the name is Android.mk
#
# If the name is different than Android.mk, it should be included device or product make files to be processed
# device/qcom/.../<product>.mk or device/qcom/.../AndroidProducts.mk.
# include vendor/mc/vendor.mc.mk

LOCAL_PATH := $(call my-dir)
include $(call all-subdir-makefiles)
#include $(call all-makefiles-under, $(LOCAL_PATH))

include $(CLEAR_VARS)
# Specify the target name of the file
LOCAL_MODULE := vendor.mc.rc
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_TAGS := optional
# Specify precompiled file
LOCAL_SRC_FILES := vendor.mc.rc
# Specify the target directory of the file
LOCAL_MODULE_PATH := $(PRODUCT_OUT)/vendor/etc/init/
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

