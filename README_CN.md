# OPLUS SM8550 系列 TWRP 设备树

[English version](README.md)

## 支持设备

### OnePlus
- OnePlus 11（PHB110 国行 / CPH2447 印度 / CPH2449 全球）
- OnePlus Ace 2 Pro（PJA110 国行）
- OnePlus Ace 3（PJE110 国行）
- OnePlus 12R（CPH2585 印度 / CPH2609 全球）
- OnePlus Open（CPH2551 全球）

### OPPO
- OPPO Find X6 Pro（PGEM10 国行）
- OPPO Find N3（PHN110 国行）

### realme
- realme GT5 150W（RMX3820 国行）
- realme GT5 240W（RMX3823 国行）

## 自行构建

```shell
mkdir twrp && cd twrp
repo init --depth=1 -u https://github.com/TWRP-Test/platform_manifest_twrp_aosp.git -b twrp-16.0
repo sync
git clone --depth=1 https://github.com/kexi1412/twrp_device_oplus_sm8550 device/oplus/sm8550
```

```shell
source build/envsetup.sh
lunch twrp_sm8550
make recoveryimage
```

如果没有报错，`recovery.img` 会生成在：

```text
out/target/product/sm8550/recovery.img
```

## 功能状态

可用：

- [X] ADB
- [X] 显示
- [X] 解密
- [X] Fastbootd
- [X] 刷写
- [X] MTP
- [X] Sideload
- [X] 触摸
- [X] USB OTG
- [X] 震动

## 刷入方法

```shell
fastboot flash recovery recovery.img
```

或者

```shell
fastboot flash recovery_a recovery.img
fastboot flash recovery_b recovery.img
```
