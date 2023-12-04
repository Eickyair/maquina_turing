#!/bin/bash
# Autor: Aguilar Martinez Erick Yair
# Fecha: 2023/12/04
# Descripción:
  # Este script compila y ejecuta un programa llamado "main.c".
  # Si la compilación es exitosa, se ejecuta el programa y se redirige la salida a un archivo llamado "output.txt".
  # Si la ejecución es exitosa, se elimina el archivo ejecutable "main".
  # En caso de que ocurra algún error durante la compilación o ejecución, se muestra un mensaje de error correspondiente.
clear
gcc main.c -o main -std=c99 -Wall -Wextra -pedantic -g
if [ $? -eq 0 ]; then
  ./main < input.txt > output.txt
  if [ $? -eq 0 ]; then
    rm ./main
    echo "El programa se ejecutó correctamente."
  else
    echo "Error: No se pudo ejecutar el programa correctamente."
  fi
else
  echo "Error: No se pudo compilar el programa correctamente."
fi
