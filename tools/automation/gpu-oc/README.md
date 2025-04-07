# installation

## sudo pacman -S nvidia nvidia-utils nvidia-settings

## enable coolbits by copying this file to /etc/X11/xorg.conf.d/20-nvidia.conf

## 28 allows us to do everything but overclock the gpu, and 31 allows full control, even on legacy gpus

## but 28 is preferred as pascal architecture isn't that old

## 
