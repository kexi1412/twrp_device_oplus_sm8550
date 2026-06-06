# TWRP device tree for OPLUS SM8550 series

[中文版本](README_CN.md)

## Supported devices

### OnePlus
- OnePlus 11 (PHB110 CN / CPH2447 IN / CPH2449 GLO)
- OnePlus Ace 2 Pro (PJA110 CN)
- OnePlus Ace 3 (PJE110 CN)
- OnePlus 12R (CPH2585 IN / CPH2609 GLO)
- OnePlus Open (CPH2551 GLO)

### OPPO
- OPPO Find X6 Pro (PGEM10 CN)
- OPPO Find N3 (PHN110 CN)

### realme
- realme GT5 150W (RMX3820 CN)
- realme GT5 240W (RMX3823 CN)

## Build it yourself

```shell
mkdir twrp && cd twrp
repo init --depth=1 -u https://github.com/TWRP-Test/platform_manifest_twrp_aosp.git -b twrp-16.0
repo sync
git clone --depth=1 https://github.com/kexi1412/twrp_device_oplus_sm8550 device/oplus/sm8550
```

```shell
source build/envsetup.sh
lunch twrp_sm8550-eng
make recoveryimage
```

If there are no errors, `recovery.img` will be generated at:

```text
out/target/product/sm8550/recovery.img
```

## Features

Works:

- [X] ADB
- [X] Display
- [X] Decryption
- [X] Fastbootd
- [X] Flashing
- [X] MTP
- [X] Sideload
- [X] Touch
- [X] USB OTG
- [X] Vibrator

## Flashing

```shell
fastboot flash recovery recovery.img
```

or

```shell
fastboot flash recovery_a recovery.img
fastboot flash recovery_b recovery.img
```
