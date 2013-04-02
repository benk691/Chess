#!/bin/bash

##################################################
# Options:
#   Note that if you are note doing your text 
#   editor in the terminal then you should specify
#   the program to fork with & at the end
#   -i: will also open init files, by default init
#       files are not opened
##################################################

# How to use the program
USEAGE="Usage: $0 [-i] [<text editor/IDE> [text editor args]]"
# The text editor
TE="vim"
# Regex expression for opening files
RE="[a-zA-Z0-9]*.py"

if [ $# -ge 1 ]; then
    if [ $1 == "-i" ]; then
        RE="*.py"
        shift
        TE=$@
    else
        TE=$@
    fi
fi

LIB_DIR="lib"
FILE_LIST_STR="$RE bin/${RE} lib/${RE}"

for DIR in $(ls ${LIB_DIR}); do
    if [ -d "${LIB_DIR}/${DIR}" ]; then
        FILE_LIST_STR="${FILE_LIST_STR} ${LIB_DIR}/${DIR}/${RE}"
    fi
done

exec ${TE} ${FILE_LIST_STR}
