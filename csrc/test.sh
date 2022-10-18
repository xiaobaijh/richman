#! /bin/bash

read -p "Enter input file:" file
read -p "Enter dest terminal num(type tty inst):" dest


while read line
do
    echo $line > $dest
done < $file
