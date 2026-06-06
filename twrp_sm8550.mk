#
# Copyright (C) 2026 The Android Open Source Project
#
# SPDX-License-Identifier: Apache-2.0
#

DEVICE_PATH := device/oplus/sm8550

# Inherit from device.mk configuration
$(call inherit-product, $(DEVICE_PATH)/device.mk)

## Device identifier
PRODUCT_DEVICE  := sm8550
PRODUCT_NAME    := twrp_sm8550
PRODUCT_BRAND   := oplus
PRODUCT_MODEL   := OPLUS SM8550
PRODUCT_MANUFACTURER := OPLUS

# Theme
TW_STATUS_ICONS_ALIGN   := center
TW_Y_OFFSET             := 111
TW_H_OFFSET             := -111
