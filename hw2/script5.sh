#!/bin/bash
# Проверяет, существует ли файл

function check_file_exists() {
  if [ -f "$1" ]; then
    echo "Файл существует."
  else
    echo "Файл не существует."
  fi
}

check_file_exists "file.txt"