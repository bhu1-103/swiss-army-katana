#!/usr/bin/zsh

domain=$1
url=$2

wget --mirror --convert-links --adjust-extension --page-requisites --no-parent --wait=2 --random-wait --domain=$domain,static.wikia.nocookie.net $url
