#!/bin/bash

usage="Usage: -f input_file"

options=f:

input_file=""

while getopts $options opt; do
    case $opt in
        f)
            input_file=$OPTARG
            ;;
        *)
            echo "Error: unknown parameter" $opt
            echo $usage
            exit -1
            ;;
    esac
done

if [ -z $input_file ]; then
    echo "Error: -f option must be specified"
    echo $usage
    exit -1
fi

input_file_name=$input_file

if [ ! -f $input_file ]; then
    input_file=Tests/"$input_file"
    if [ ! -f $input_file ]; then
        echo "Error: Incorrect input file"
        echo $usage
        exit -1
    fi
fi

name_without_extension="$(echo $input_file_name | sed 's:\(.*/\)*\(.*\)[.].*:\2:')"
output_file=Out/"$name_without_extension".out

input_file_time="$(stat -c %Y $input_file)"
if [ -f "$output_file" ]; then
    output_file_time="$(stat -c %Y $output_file)"
else
    output_file_time=0
fi

if [ "$input_file_time" -gt "$output_file_time" ]; then
    if ! Assembler/ass -i $input_file -o $output_file >/dev/null
    then
        exit $exit_code
    fi
fi

Emulator/emu -i $output_file
