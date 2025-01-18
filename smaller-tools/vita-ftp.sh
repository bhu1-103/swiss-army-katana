#!/usr/bin/zsh

ftp -n 192.168.0.$1 1337 <<EOF
quote USER anonymous
quote PASS 
cd ux0:/vpks
put $2
quit
EOF
