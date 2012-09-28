#!/bin/bash

if [ -z $1 ]; then
    echo "Usage: backup.sh version"
    exit 0
fi

version=$1
backup_dir="backup"
ver_dir="version_${version}"
backup_path="${backup_dir}/${ver_dir}"

cd bin

if [ ! -d "${backup_path}" ]; then
    mkdir "${backup_path}"
    echo "Directory $ver_dir made"
fi

for item in $( ls ); do
    if [[ "$item" != "$ver_dir" && "$item" != "$backup_dir" ]]; then
        if [ ! -e "${backup_path}/$item" ]; then
            cp ${item} ${backup_path}/${item}
        fi
    fi
done

exit 0
