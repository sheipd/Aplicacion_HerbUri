#ifndef PROYECTOC_COMPRAS_H
#define PROYECTOC_COMPRAS_H
#define FICH_COMPRAS "compras.dat"

#include <stdio.h>
#include <string.h>

typedef struct {
    char id_cliente[10];
    char id_producto[6];
    char fecha[9];
} Compra;

typedef struct{
    int numRegCom;
} RegistrosCom;

FILE *fichCompras;

void anadirCompra(void);
void listarCompras(void);
void buscarCompra(void);
void modificarCompra(void);
int comprobarCliente(char[]);
int comprobarProducto(char[]);

#endif //PROYECTOC_COMPRAS_H
