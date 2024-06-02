#!/bin/bash
# Проверяет, больше x чем y или нет
x=10
y=5

if [ $x -gt $y ]; then  # если x > y
  echo "x больше y"
else  # иначе
  echo "x меньше или равен y"
fi