#!/bin/bash
# Autor: Aguilar Martinez Erick Yair
# Fecha: 2023/12/04
# Descripción:
  # Este script compila y ejecuta un programa llamado "main.c".
  # Si la compilación es exitosa, se ejecuta el programa y se redirige la salida a un archivo llamado "output.txt".
  # Si la ejecución es exitosa, se elimina el archivo ejecutable "main".
  # En caso de que ocurra algún error durante la compilación o ejecución, se muestra un mensaje de error correspondiente.
clear

# Compila el archivo main.c con gcc y establece las opciones de compilación
# -std=c99, -Wall, -Wextra y -pedantic. El resultado se guarda en un archivo
# ejecutable llamado "main".

gcc main.c -o main -std=c99 -Wall -Wextra -pedantic -g

# Verifica si la compilación fue exitosa
if [ $? -eq 0 ]; then
  # Verifica si se recibió la bandera -t
  if [ "$1" = "-t" ]; then
    # Ejecuta el programa "main" con el archivo de entrada "test.txt" y redirige
    # Asi no se afecta el input.txt y test.txt es un archivo local para cada desarrollador
    # la salida al archivo "output.txt".
    ./main < test.txt > output.txt
  else
    # Ejecuta el programa "main" con el archivo de entrada "input.txt" y redirige
    # la salida al archivo "output.txt".
    ./main < input.txt > output.txt
  fi

  # Verifica si la ejecución del programa fue exitosa
  if [ $? -eq 0 ]; then
    # Elimina el archivo ejecutable "main"
    rm ./main

    # Imprime un mensaje indicando que el programa se ejecutó correctamente
    echo "Las ADVERTENCIAS de desbordamiento de memoria se pueden ignorar"
    echo "El programa se ejecutó correctamente"
  else
    # Imprime un mensaje de error si no se pudo ejecutar el programa correctamente
    echo "Error: No se pudo ejecutar el programa correctamente."
  fi
else
  # Imprime un mensaje de error si no se pudo compilar el programa correctamente
  echo "Error: No se pudo compilar el programa correctamente."
fi
