#!/bin/bash
modprobe libcomposite

CONFIGFS="/sys/kernel/config/usb_gadget/g1"

# Teardown to prevent "device busy" locks
if [ -d "$CONFIGFS" ]; then
  echo "" >$CONFIGFS/UDC 2>/dev/null
  rm -f $CONFIGFS/configs/c.1/uvc.usb0 2>/dev/null
  rm -rf $CONFIGFS 2>/dev/null
fi

mkdir -p $CONFIGFS
echo 0x1d6b >$CONFIGFS/idVendor
echo 0x0104 >$CONFIGFS/idProduct
echo 0x0200 >$CONFIGFS/bcdUSB

mkdir -p $CONFIGFS/strings/0x409
echo "123456789" >$CONFIGFS/strings/0x409/serialnumber
echo "Raspberry Pi" >$CONFIGFS/strings/0x409/manufacturer
echo "Pi Webcam" >$CONFIGFS/strings/0x409/product

mkdir -p $CONFIGFS/configs/c.1/strings/0x409
echo "Config 1" >$CONFIGFS/configs/c.1/strings/0x409/configuration
echo 500 >$CONFIGFS/configs/c.1/MaxPower

mkdir -p $CONFIGFS/functions/uvc.usb0

# 1. Setup Control Headers (This is where the old script failed)
mkdir -p $CONFIGFS/functions/uvc.usb0/control/header/h
ln -s $CONFIGFS/functions/uvc.usb0/control/header/h $CONFIGFS/functions/uvc.usb0/control/class/fs
ln -s $CONFIGFS/functions/uvc.usb0/control/header/h $CONFIGFS/functions/uvc.usb0/control/class/ss

# 2. Setup Streaming MJPEG Format (1080p)
mkdir -p $CONFIGFS/functions/uvc.usb0/streaming/mjpeg/m/1080p
echo 1920 >$CONFIGFS/functions/uvc.usb0/streaming/mjpeg/m/1080p/wWidth
echo 1080 >$CONFIGFS/functions/uvc.usb0/streaming/mjpeg/m/1080p/wHeight
echo 333333 >$CONFIGFS/functions/uvc.usb0/streaming/mjpeg/m/1080p/dwDefaultFrameInterval
echo $((1920 * 1080 * 2)) >$CONFIGFS/functions/uvc.usb0/streaming/mjpeg/m/1080p/dwMaxVideoFrameBufferSize
echo -e "333333\n666666\n1000000" >$CONFIGFS/functions/uvc.usb0/streaming/mjpeg/m/1080p/dwFrameInterval

# 3. Setup Streaming Headers
mkdir -p $CONFIGFS/functions/uvc.usb0/streaming/header/h
ln -s $CONFIGFS/functions/uvc.usb0/streaming/mjpeg/m $CONFIGFS/functions/uvc.usb0/streaming/header/h/m

ln -s $CONFIGFS/functions/uvc.usb0/streaming/header/h $CONFIGFS/functions/uvc.usb0/streaming/class/fs
ln -s $CONFIGFS/functions/uvc.usb0/streaming/header/h $CONFIGFS/functions/uvc.usb0/streaming/class/hs
ln -s $CONFIGFS/functions/uvc.usb0/streaming/header/h $CONFIGFS/functions/uvc.usb0/streaming/class/ss

# Bind UVC to config and enable
ln -s $CONFIGFS/functions/uvc.usb0 $CONFIGFS/configs/c.1
udevadm settle
ls /sys/class/udc >$CONFIGFS/UDC
