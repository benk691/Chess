#!/bin/bash

uname="kelloggb"
cd include

for i in $(ls)
do
#    echo `mv ${i} ${uname}_${i}`
#    echo `python ../lab.py ${uname}_${i}`
    echo `python ../lab.py ${i}`
done
