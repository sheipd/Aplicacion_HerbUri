#ifndef PROYECTOC_PRODUCTOS_H
#define PROYECTOC_PRODUCTOS_H
#define FICH_PRODUCTOS "productos.dat"

#include <stdio.h>
#include <string.h>

typedef struct{
    char codigo[6]; //el código estará compuesto por 5 números enteros
    char nombre[21];
    char tipo[21];
    char procedencia[21];
} Producto;

typedef struct{
    int numRegProd;
} RegistrosProd;

FILE *fichProd;

void anadirProducto(void);
void listarProductos(void);
void buscarProducto(void);
void modificarProducto(void);
void eliminarProducto(void);
void ordenarProductos(void);
void actualizarComprasProd(char[], char[]);

#endif //PROYECTOC_PRODUCTOS_H
