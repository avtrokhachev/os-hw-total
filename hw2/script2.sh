#!/bin/bash
# Выводит все числа от i до j, i <= j
i=1
j=5
while [ $i -le $j ]; do  # пока i <= j
  echo $i
  ((i++))
done