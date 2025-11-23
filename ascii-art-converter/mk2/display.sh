#/usr/bin/zsh
for txt_file in "frames-t"/*.txt; do
	clear
	cat "$txt_file"
	sleep 0.04
done
