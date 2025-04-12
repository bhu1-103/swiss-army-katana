#!/usr/bin/zsh

page_total=$(pdfinfo book.pdf | grep Pages | awk '{print $2}')
page_width=3
mkdir -p extracted-pages

for page in $(seq 1 $page_total)
do
    padded_page=$(printf "%0${page_width}d" $page)
    pdftotext -f $page -l $page book.pdf extracted-pages/$padded_page.txt
    tail -n +3 extracted-pages/$padded_page.txt | head -n -4 > extracted-pages/$padded_page.cleaned.txt
    mv extracted-pages/$padded_page.cleaned.txt extracted-pages/$padded_page.txt
done
