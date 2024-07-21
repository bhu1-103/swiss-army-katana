#!/usr/bin/zsh
qemu-system-x86_64 -enable-kvm -cdrom VoidPup64-22.02-240717.iso -boot menu=on -drive file=image.img -m 2G -cpu host
