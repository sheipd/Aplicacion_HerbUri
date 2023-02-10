#ifndef PROYECTOC_CLIENTES_H
#define PROYECTOC_CLIENTES_H
#define FICH_CLIENTES "clientes.dat"

#include <stdio.h>
#include <string.h>

typedef struct {
    char telefono[10];
    char nombre[51];
} Cliente;

typedef struct{
    int numRegCli;
} RegistrosCli;

FILE *fichCli;

void anadirCliente(void);
void listarClientes(void);
void buscarCliente(void);
void modificarCliente(void);
void ordenarClientes(void);
void actualizarComprasCli(char[], char[]);

#endif //PROYECTOC_CLIENTES_H
