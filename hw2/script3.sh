#!/bin/bash
# Говорит привет и пока по имени.

function say_hello() {  # функция приветствия
  echo "Hello, $1!"
}

function say_bye() {  # функция прощания
  echo "Bye, $1!"
}

function speak() {  # общий разговор
  say_hello $1
  say_bye $1
}

speak "Andrey"  # разговор с <имя>