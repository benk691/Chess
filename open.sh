#!/bin/bash

#######################################################
# Options:
#   DEFAULT: No flags will open all files except
#   the init and doc files
#   NOTE: If you are note doing your text 
#   editor in the terminal then you should specify
#   the program to fork with & at the end
#   FLAGS:
#   -i: will also open init files, by default init
#       files are not opened (this should be the first 
#       flag)
#   -m: opens files directly under the Chess directory
#   -b: opens bin files
#   -l: opens log files
#   -d: opens doc files
#######################################################

# How to use the program
USEAGE="Usage: $0 [-i] [-m] [-b] [-l] [-d] [<text editor/IDE> [text editor args]]"
# The text editor
TE="vim"
# Regex expression for opening files
RE="[a-zA-Z0-9]*.py *.tex"
# Number of flags
FLAG_COUNT=0
# Tells whether to open all files
ALL_FILES=1
# List of files to open
FILE_LIST_STR=""
# Bin directory
BIN_DIR="bin"
# Lib directory
LIB_DIR="lib"
# Doc directory
DOC_DIR="docs"

function collectLibFiles {
    FILE_LIST_STR="${FILE_LIST_STR} ${LIB_DIR}/${RE}"
    for DIR in $(ls ${LIB_DIR}); do
        if [ -d "${LIB_DIR}/${DIR}" ]; then
            FILE_LIST_STR="${FILE_LIST_STR} ${LIB_DIR}/${DIR}/${RE}"
        fi
    done
}

if [ $# -ge 1 ]; then
    for ARG in $@; do
        if [ $ARG == "-i" ]; then
            RE="*.py *.tex"
            let FLAG_COUNT=FLAG_COUNT+1
        elif [ $ARG == "-m" ]; then
            FILE_LIST_STR="${FILE_LIST_STR} ${RE}"
            let FLAG_COUNT=FLAG_COUNT+1
            let ALL_FILES=0
        elif [ $ARG == "-b" ]; then
            FILE_LIST_STR="${FILE_LIST_STR} ${BIN_DIR}/${RE}"
            let FLAG_COUNT=FLAG_COUNT+1
            let ALL_FILES=0
        elif [ $ARG == "-l" ]; then
            collectLibFiles
            let FLAG_COUNT=FLAG_COUNT+1
            let ALL_FILES=0
        elif [ $ARG == "-d" ]; then
            FILE_LIST_STR="${FILE_LIST_STR} ${DIR_DIR}/${RE}"
            let FLAG_COUNT=FLAG_COUNT+1
            let ALL_FILES=0
        else:
            break
        fi
    done
fi

if [ $ALL_FILES == 1 ]; then
    FILE_LIST_STR="${RE} ${BIN_DIR}/${RE}"
    collectLibFiles
fi

while [ $FLAG_COUNT -gt 0 ]; do
    shift
    let FLAG_COUNT=FLAG_COUNT-1
done

TE=$@

exec ${TE} ${FILE_LIST_STR}
