cmake_minimum_required(VERSION 3.17)
project(proyectoC C)

set(CMAKE_C_STANDARD 99)

add_executable(proyectoC main.c productos.c compras.c clientes.c productos.h clientes.h compras.h)