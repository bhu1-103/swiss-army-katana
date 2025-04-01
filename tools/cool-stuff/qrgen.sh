#!/usr/bin/zsh

echo -n "Enter song link: "
read link
echo -n "Rename to: "
read new_name
yt-dlp -x --audio-format aac --audio-quality 7 --embed-metadata $link -o $new_name

scp $new_name.m4a bhu4@192.168.0.107:/home/bhu4/
ssh -T bhu4@192.168.0.107 << EOF
sudo mv ~/$new_name.m4a /var/www/html/download
exit
EOF

qrencode -o link_qr_code.png http://192.168.0.107/download/$new_name.m4a
feh --zoom 600 link_qr_code.png
rm link_qr_code.png
rm $new_name.m4a
