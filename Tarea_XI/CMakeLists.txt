cmake_minimum_required(VERSION 4.1)
project(Tarea_XI)

set(CMAKE_CXX_STANDARD 20)

# Añadir el ejecutable principal
add_executable(Tarea_XI main.cpp)

# COMANDO AUTOMÁTICO: Copia estudiantes.csv a la carpeta donde se ejecuta el programa
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/estudiantes.csv
        ${CMAKE_CURRENT_BINARY_DIR}/estudiantes.csv
        COPYONLY
)