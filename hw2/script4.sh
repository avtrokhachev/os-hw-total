#!/bin/bash
# Выводит содержимое файла

function read_file() {
  while read line; do
    echo $line
  done < $1
}

read_file "file.txt"