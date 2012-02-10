#!/bin/bash

#################### Key 1st Arg ####################
# b # open backup program files                     #
#####################################################
# c # open chess program files                      #
#####################################################
# m # open Makefiles                                #
#####################################################

#################### Key 2nd Arg ####################
# Number # chess version number                     #
#####################################################
# c      # current chess version                    #
#####################################################

USEAGE="Usage: $0 [b|c|m] [chess version number|c]"

if [ -z "$2" ]; then
    echo ${USEAGE}
    exit
fi

CHOICE=$1
BACKUP="b"
CHESS="c"
MAKE="m"

if [ $CHOICE == $BACKUP ]; then
    BACKUP_EXE='backup.sh'
    BACKUP_PROG_DIR='backup_program'
    COMMON_DIR="${BACKUP_PROG_DIR}/common"
    LANGUAGE_DIR="${BACKUP_PROG_DIR}/modules/languages"
    PROCESSOR_DIR="${BACKUP_PROG_DIR}/modules/processors"
    BIN_DIR='bin'

exec gvim ${BACKUP_EXE} ${BACKUP_PROG_DIR}/*.sh ${COMMON_DIR}/*.py ${LANGUAGE_DIR}/*.py ${PROCESSOR_DIR}/*.py ${BIN_DIR}/main.cc ${BIN_DIR}/log.xml ${BACKUP_PROG_DIR}/README &

elif [ $CHOICE == $CHESS ]; then
    if [ $2 == $CHESS ]; then
        BIN_DIR='bin'
        
exec gvim ${BIN_DIR}/*.cc ${BIN_DIR}/*.h &

    else
        VERSION_DIR="bin/bakup/version_/${2}"
        
exec gvim ${VERSION_DIR}/*.cc ${VERSION_DIR}/*.h &
    fi

elif [ $CHOICE == $MAKE ]; then
    BACKUP_PROG_DIR='backup_program'
    COMMON_DIR="${BACKUP_PROG_DIR}/common"
    LANGUAGE_DIR="${BACKUP_PROG_DIR}/modules/languages"
    PROCESSOR_DIR="${BACKUP_PROG_DIR}/modules/processors"
    BIN_DIR='bin'
    BACKUP_DIR='bin/backup'
    BACKUP_MAKEFILE_LIST_STR=""

    for DIR in $(ls ${BACKUP_DIR}); do
        if [ -d "${BACKUP_DIR}/${DIR}" ]; then
            BACKUP_MAKEFILE_LIST_STR="${BACKUP_MAKEFILE_LIST_STR} ${BACKUP_DIR}/${DIR}/Makefile"
        fi
    done
    
    exec gvim Makefile ${BIN_DIR}/Makefile ${BACKUP_MAKEFILE_LIST_STR} ${BACKUP_PROG_DIR}/Makefile ${COMMON_DIR}/Makefile ${LANGUAGE_DIR}/Makefile ${PROCESSOR_DIR}/Makefile &

else
    echo $USEAGE
    exit
fi
