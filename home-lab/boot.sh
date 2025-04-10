qemu-system-x86_64 \
  -enable-kvm \
  -drive file=image.img,format=qcow2 \
  -boot order=d \
  -m 2048 \
  -cpu host \
  -smp 2
