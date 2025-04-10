#!/usr/bin/zsh

mkdir home-lab
cd home-lab
#wget https://cdimage.kali.org/kali-2025.1a/kali-linux-2025.1a-installer-amd64.iso #deprecated because kali is not ideal for quick a-install

wget https://repo-default.voidlinux.org/live/current/void-live-x86_64-20250202-xfce.iso
qemu-img create -f qcow2 image.img 10G

qemu-system-x86_64 \
  -enable-kvm \
  -cdrom void-live-x86_64-20250202-xfce.iso \
  -drive file=image.img,format=qcow2 \
  -boot order=d \
  -m 2048 \
  -cpu host \
  -smp 2
