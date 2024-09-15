#!/usr/bin/zsh

alias red='echo -e -n "\033[38;2;255;0;0m"'
alias green='echo -e -n "\033[38;2;0;255;0m"'
alias blue='echo -e -n "\033[38;2;0;0;255m"'

red && echo -n "This is red text" && echo -e "\033[0m"
green && echo -n "This is green text" && echo -e "\033[0m"
blue && echo -n "This is blue text" && echo -e "\033[0m"
