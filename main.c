#include <stdio.h>
#include "productos.h"
#include "clientes.h"
#include "compras.h"

void compras();
void productos();
void clientes();

int main() {
    int opcion;

    while(1){
        printf("\n~~ HerbUri ~~\n\n");
        printf("- Menu -\n");
        printf("1.- Fichero de compras.\n");
        printf("2.- Fichero de productos.\n");
        printf("3.- Fichero de clientes.\n");
        printf("A que fichero desea acceder? (0 = salir): ");
        scanf("%d", &opcion);

        if(opcion == 0) break;

        switch (opcion) {
            case 1:
                compras();
                break;
            case 2:
                productos();
                break;
            case 3:
                clientes();
        }
    }

    return 0;
}

void compras(){
    Compra com;
    RegistrosCom regCom;

    int eleccion;

    fichCompras = fopen(FICH_COMPRAS, "r+b");

    if(fichCompras == NULL){
        fichCompras = fopen(FICH_COMPRAS, "w+b");

        regCom.numRegCom = 0;

        memset(&com, '*', sizeof(com));

        fseek(fichCompras, 0, SEEK_SET);
        fwrite(&com, sizeof(com), 1, fichCompras);
        fseek(fichCompras, 0, SEEK_SET);
        fwrite(&regCom, sizeof(regCom), 1, fichCompras);
    }
    fclose(fichCompras);

    while(1){
        printf("\n- Menu del fichero de compras -\n");
        printf("1.- Anadir una compra realizada.\n");
        printf("2.- Listado de las compras.\n");
        printf("3.- Buscar una compra.\n");
        printf("4.- Modificar una compra.\n");
        printf("Que desea realizar? (0 = salir): ");
        scanf("%d", &eleccion);

        if(eleccion == 0) break;

        switch (eleccion) {
            case 1:
                anadirCompra();
                break;
            case 2:
                listarCompras();
                break;
            case 3:
                buscarCompra();
                break;
            case 4:
                modificarCompra();
        }
    }
}

void productos(){
    int eleccion;

    Producto prod;
    RegistrosProd regProd;

    fichProd = fopen(FICH_PRODUCTOS, "r+b");

    if(fichProd == NULL){
        fichProd = fopen(FICH_PRODUCTOS, "w+b");

        regProd.numRegProd = 0;

        memset(&prod, '*', sizeof(prod));

        fseek(fichProd, 0, SEEK_SET);
        fwrite(&prod, sizeof(prod), 1, fichProd);
        fseek(fichProd, 0, SEEK_SET);
        fwrite(&regProd, sizeof(regProd), 1, fichProd);
    }
    fclose(fichProd);

    while(1){
        printf("\n- Menu del fichero de productos -\n");
        printf("1.- Anadir un nuevo producto.\n");
        printf("2.- Listado de los productos.\n");
        printf("3.- Buscar un producto.\n");
        printf("4.- Modificar un producto.\n");
        printf("5.- Eliminar un producto.\n");
        printf("Que desea realizar? (0 = salir): ");
        scanf("%d", &eleccion);

        if(eleccion == 0) break;

        switch (eleccion) {
            case 1:
                anadirProducto();
                break;
            case 2:
                listarProductos();
                break;
            case 3:
                buscarProducto();
                break;
            case 4:
                modificarProducto();
                break;
            case 5:
                eliminarProducto();
        }
    }
}

void clientes(){
    Cliente cli;
    RegistrosCli regCli;

    int eleccion;

    fichCli = fopen(FICH_CLIENTES, "r+b");

    if(fichCli == NULL){
        fichCli = fopen(FICH_CLIENTES, "w+b");

        regCli.numRegCli = 0;

        memset(&cli, '*', sizeof(cli));

        fseek(fichCli, 0, SEEK_SET);
        fwrite(&cli, sizeof(cli), 1, fichCli);
        fseek(fichCli, 0, SEEK_SET);
        fwrite(&regCli, sizeof(regCli), 1, fichCli);
    }
    fclose(fichCli);

    while(1){
        printf("\n- Menu del fichero de clientes -\n");
        printf("1.- Anadir un nuevo cliente.\n");
        printf("2.- Listado de los clientes.\n");
        printf("3.- Buscar un cliente.\n");
        printf("4.- Modificar un cliente.\n");
        printf("Que desea realizar? (0 = salir): ");
        scanf("%d", &eleccion);

        if(eleccion == 0) break;

        switch (eleccion) {
            case 1:
                anadirCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                buscarCliente();
                break;
            case 4:
                modificarCliente();
        }
    }
}
