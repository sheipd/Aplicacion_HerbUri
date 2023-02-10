#include "compras.h"
#include "productos.h"
#include "clientes.h"

void anadirCompra(void){
    Compra com;
    RegistrosCom regCom;

    fichCompras = fopen(FICH_COMPRAS, "r+b");

    fseek(fichCompras, 0, SEEK_SET);
    fread(&regCom, sizeof(regCom), 1, fichCompras);

    int desplazar, flag = 0, i;

    printf("\n* Alta de compra\n");

    for (i = 1; i <= regCom.numRegCom; i++) {
        desplazar = i * sizeof(Compra);
        fseek(fichCompras, desplazar, SEEK_SET);
        fread(&com, sizeof(com), 1, fichCompras);

        if (strcmp("*", com.id_cliente) == 0) {
            fflush(stdin);
            printf("Introduce el telefono del cliente: ");
            gets(com.id_cliente);
            printf("Introduce el codigo del producto: ");
            gets(com.id_producto);
            printf("Introduce la fecha de la venta: ");
            gets(com.fecha);
            fflush(stdin);

            if(comprobarCliente(com.id_cliente) == 0 && comprobarProducto(com.id_producto) == 0){
                fseek(fichCompras, desplazar, SEEK_SET);
                fwrite(&com, sizeof(com), 1, fichCompras);
            } else printf("El telefono del cliente o el codigo del producto no esta registrado en la base de datos.\n");

            flag = 1;
        }
    }

    if (!flag) {
        fflush(stdin);
        printf("Introduce el telefono del cliente: ");
        gets(com.id_cliente);
        printf("Introduce el codigo del producto: ");
        gets(com.id_producto);
        printf("Introduce la fecha: ");
        gets(com.fecha);
        fflush(stdin);

        if(comprobarCliente(com.id_cliente) == 0 && comprobarProducto(com.id_producto) == 0){
            desplazar = (regCom.numRegCom + 1) * sizeof(Compra);
            fseek(fichCompras, desplazar, SEEK_SET);
            fwrite(&com, sizeof(com), 1, fichCompras);

            regCom.numRegCom++;
            fseek(fichCompras, 0, SEEK_SET);
            fwrite(&regCom, sizeof(regCom), 1, fichCompras);
        } else printf("El telefono del cliente o el codigo del producto no esta registrado en la base de datos.\n");

    }

    fclose(fichCompras);
}

void listarCompras(void) {
    Cliente cli;
    RegistrosCli regCli;
    Compra com;
    RegistrosCom regCom;

    int desplazar, flag, i;

    fichCompras = fopen(FICH_COMPRAS, "rb");

    fseek(fichCompras, 0, SEEK_SET);
    fread(&regCli, sizeof(regCli), 1, fichCompras);

    printf("\n* Listado de compras\n");

    for (i = 1; i <= regCom.numRegCom; i++) {
        desplazar = i * sizeof(Compra);
        fseek(fichCompras, desplazar, SEEK_SET);
        fread(&com, sizeof(com), 1, fichCompras);

        if (strcmp("*", com.id_cliente) != 0) {
            printf("Telefono del cliente: %s", com.id_cliente);
            printf("\tCodigo del producto: %s", com.id_producto);
            printf("\tFecha: %s\n", com.fecha);
        }
    }

    fclose(fichCompras);
}

void buscarCompra(void) {
    Cliente cli;
    RegistrosCli regCli;
    Compra com;
    RegistrosCom regCom;

    fichCompras = fopen(FICH_COMPRAS, "rb");

    fseek(fichCompras, 0, SEEK_SET);
    fread(&regCli, sizeof(regCli), 1, fichCompras);

    char tel[9], cod[5];
    int desplazar, flag = 0, i;

    printf("\n* Consulta de compra\n");

    fflush(stdin);
    printf("Introduce el telefono del cliente: ");
    gets(tel);
    printf("Introduce el codigo del producto: ");
    gets(cod);

    for (i = 1; i <= regCom.numRegCom; i++) {
        desplazar = i * sizeof(Compra);
        fseek(fichCompras, desplazar, SEEK_SET);
        fread(&com, sizeof(com), 1, fichCompras);

        if (strcmp(tel, com.id_cliente) == 0 && strcmp(cod, com.id_producto) == 0) {
            printf("\nTelefono del cliente: %s", com.id_cliente);
            printf("\tCodigo del producto: %s", com.id_producto);
            printf("\tFecha: %s\n\n", com.fecha);

            flag = 1;
        }
    }

    if(!flag) printf("No se ha encontrado ningun registro con esos datos.\n");

    fclose(fichCompras);
}

void modificarCompra(void) {
    Compra com;
    RegistrosCom regCom;

    fichCompras = fopen(FICH_COMPRAS, "r+b");

    fseek(fichCompras, 0, SEEK_SET);
    fread(&regCom, sizeof(regCom), 1, fichCompras);

    char telf[9];
    char cod[5];
    int desplazar, flag = 0, i;

    printf("\n* Modificaciones de compras\n");

    fflush(stdin);
    printf("Introduce el telefono del cliente: ");
    gets(telf);
    printf("Introduce el codigo del producto: ");
    gets(cod);

    for (i = 1; i <= regCom.numRegCom; i++) {
        desplazar = i * sizeof(Compra);
        fseek(fichCompras, desplazar, SEEK_SET);
        fread(&com, sizeof(com), 1, fichCompras);

        if (strcmp(telf, com.id_cliente) == 0 && strcmp(cod, com.id_producto) == 0) {
            flag = 1;

            printf("Introduce los nuevos datos de la compra:\n");
            printf("Introduce el telefono del cliente: ");
            gets(com.id_cliente);
            printf("Introduce el codigo del producto: ");
            gets(com.id_producto);
            fflush(stdin);

            if(comprobarCliente(com.id_cliente) == 0 && comprobarProducto(com.id_producto) == 0){
                fseek(fichCompras, desplazar, SEEK_SET);
                fwrite(&com, sizeof(com), 1, fichCompras);
            } else {
                printf("El telefono del cliente o el codigo del producto no esta registrado en la base de datos.\n");
            }
        }
    }

    if (!flag) printf("No se ha encontrado el registro.");

    fclose(fichCompras);
}

int comprobarCliente(char codigo[9]) {
    Cliente cli;
    RegistrosCli regCli;

    fichCli = fopen(FICH_CLIENTES, "rb");

    fseek(fichCli, 0, SEEK_SET);
    fread(&regCli, sizeof(regCli), 1, fichCli);

    int flag = 0;
    int desplazar, i;

    for (i = 1; i <= regCli.numRegCli; i++) {
        desplazar = i * sizeof(Cliente);
        fseek(fichCli, desplazar, SEEK_SET);
        fread(&cli, sizeof(cli), 1, fichCli);

        if (strcmp(codigo, cli.telefono) == 0) {
            flag = 1;
            break;
        }
    }

    fclose(fichCli);

    if(flag) return 0;
    else return 1;
}

int comprobarProducto(char codigo[6]){
    Producto prod;
    RegistrosProd regProd;

    fichProd = fopen(FICH_PRODUCTOS, "rb");

    int flag = 0;
    int desplazar, i;

    fseek(fichProd, 0, SEEK_SET);
    fread(&regProd, sizeof(regProd), 1, fichProd);

    for (i = 1; i <= regProd.numRegProd; i++) {
        desplazar = i * sizeof(Producto);
        fseek(fichProd, desplazar, SEEK_SET);
        fread(&prod, sizeof(prod), 1, fichProd);

        if (strcmp(codigo, prod.codigo) == 0) {
            flag = 1;
            break;
        }
    }

    fclose(fichProd);

    if(flag) return 0;
    else return 1;
}
