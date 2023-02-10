#include "productos.h"
#include "compras.h"

void anadirProducto(void){
    int desplazar, flag, i;

    Producto prod;
    RegistrosProd regProd;

    fichProd = fopen(FICH_PRODUCTOS, "r+b");

    printf("\n* Alta de producto\n");

    fseek(fichProd, 0, SEEK_SET);
    fread(&regProd, sizeof(regProd), 1, fichProd);

    flag = 0;

    for (i = 1; i <= regProd.numRegProd; i++) {
        desplazar = i * sizeof(Producto);
        fseek(fichProd, desplazar, SEEK_SET);
        fread(&prod, sizeof(prod), 1, fichProd);

        if (strcmp("*", prod.codigo) == 0) {
            fflush(stdin);
            printf("Introduce el codigo del producto: ");
            gets(prod.codigo);
            printf("Introduce su nombre: ");
            gets(prod.nombre);
            printf("Introduce su tipo: ");
            gets(prod.tipo);
            printf("Introduce su procedencia: ");
            gets(prod.procedencia);
            fflush(stdin);

            if(strlen(prod.codigo) == 5){
                fseek(fichProd, desplazar, SEEK_SET);
                fwrite(&prod, sizeof(prod), 1, fichProd);
            } else printf("El codigo no es valido.\n");

            flag = 1;
        }
    }

    if (!flag) {
        fflush(stdin);
        printf("Introduce el codigo del producto: ");
        gets(prod.codigo);
        printf("Introduce su nombre: ");
        gets(prod.nombre);
        printf("Introduce su tipo: ");
        gets(prod.tipo);
        printf("Introduce su procedencia: ");
        gets(prod.procedencia);
        fflush(stdin);

        if(strlen(prod.codigo) == 5){
            desplazar = (regProd.numRegProd + 1) * sizeof(Producto);
            fseek(fichProd, desplazar, SEEK_SET);
            fwrite(&prod, sizeof(prod), 1, fichProd);

            regProd.numRegProd++;
            fseek(fichProd, 0, SEEK_SET);
            fwrite(&regProd, sizeof(regProd), 1, fichProd);
        } else printf("El codigo no es valido.\n");
    }

    fclose(fichProd);
}

void listarProductos(void) {
    int desplazar, i;

    Producto prod;
    RegistrosProd regProd;

    fichProd = fopen(FICH_PRODUCTOS, "r+b");

    printf("\n* Listado de productos\n");

    fseek(fichProd, 0, 0);
    fread(&regProd, sizeof(regProd), 1, fichProd);

    ordenarProductos();

    for (i = 1; i <= regProd.numRegProd; i++) {
        desplazar = i * sizeof(Producto);
        fseek(fichProd, desplazar, SEEK_SET);
        fread(&prod, sizeof(prod), 1, fichProd);

        if (strcmp("*", prod.codigo) != 0) {
            printf("Codigo: %s", prod.codigo);
            printf("\tNombre: %s", prod.nombre);
            printf("\tTipo: %s", prod.tipo);
            printf("\tProcedencia: %s\n", prod.procedencia);
        }
    }

    fclose(fichProd);
}

void buscarProducto(void) {
    int desplazar, flag, i;

    Producto prod;
    RegistrosProd regProd;

    fichProd = fopen(FICH_PRODUCTOS, "rb");

    printf("\n* Consulta de producto\n");

    fseek(fichProd, 0, SEEK_SET);
    fread(&regProd, sizeof(regProd), 1, fichProd);

    char codigo[5];
    flag = 0;

    fflush(stdin);
    printf("Introduce el codigo del producto a buscar: ");
    gets(codigo);

    for (i = 1; i <= regProd.numRegProd; i++) {
        desplazar = i * sizeof(Producto);
        fseek(fichProd, desplazar, SEEK_SET);
        fread(&prod, sizeof(prod), 1, fichProd);

        if (strcmp(codigo, prod.codigo) == 0) {
            printf("Codigo: %s", prod.codigo);
            printf("\tNombre: %s", prod.nombre);
            printf("\tTipo: %s", prod.tipo);
            printf("\tProcedencia: %s\n", prod.procedencia);

            flag = 1;
        }
    }

    fclose(fichProd);

    if(!flag) printf("No se ha encontrado ningun producto con ese codigo.\n");
}

void modificarProducto(void) {
    int desplazar, flag, i;

    Producto prod;
    RegistrosProd regProd;

    fichProd = fopen(FICH_PRODUCTOS, "r+b");

    printf("\n* Modificaciones de productos\n");

    fseek(fichProd, 0, SEEK_SET);
    fread(&prod, sizeof(prod), 1, fichProd);

    char codigo[5];
    flag = 0;

    fflush(stdin);
    printf("Introduce el codigo del producto a modificar: ");
    gets(codigo);

    for (i = 1; i <= regProd.numRegProd; i++) {
        desplazar = i * sizeof(Producto);
        fseek(fichProd, desplazar, SEEK_SET);
        fread(&prod, sizeof(prod), 1, fichProd);

        if (strcmp(codigo, prod.codigo) == 0) {
            flag = 1;

            puts("Introduce los nuevos datos del producto:\n");
            printf("Introduce el codigo del producto: ");
            gets(prod.codigo);
            printf("Introduce su nombre: ");
            gets(prod.nombre);
            printf("Introduce su tipo: ");
            gets(prod.tipo);
            printf("Introduce su procedencia: ");
            gets(prod.procedencia);
            fflush(stdin);

            if(strlen(prod.codigo) == 5){
                fseek(fichProd, desplazar, SEEK_SET);
                fwrite(&prod, sizeof(prod), 1, fichProd);

                actualizarComprasProd(codigo, prod.codigo);
            } else printf("El codigo no es valido.\n");
        }
    }

    fclose(fichProd);

    if (!flag) printf("No se ha encontrado el registro.");
}

void eliminarProducto(void) {
    int desplazar, flag, i;

    Producto prod;
    RegistrosProd regProd;

    fichProd = fopen(FICH_PRODUCTOS, "r+b");

    printf("\n* Baja de producto\n");

    fseek(fichProd, 0, SEEK_SET);
    fread(&prod, sizeof(prod), 1, fichProd);

    char codigo[5];
    flag = 0;

    fflush(stdin);
    printf("Introduce el codigo del producto a eliminar: ");
    gets(codigo);

    for (i = 1; i <= regProd.numRegProd; i++) {
        desplazar = i * sizeof(Producto);
        fseek(fichProd, desplazar, SEEK_SET);
        fread(&prod, sizeof(prod), 1, fichProd);

        if (strcmp(codigo, prod.codigo) == 0) {
            flag = 1;

            strcpy(prod.codigo, "*");

            fseek(fichProd, desplazar, SEEK_SET);
            fwrite(&prod, sizeof(prod), 1, fichProd);
        }
    }

    fclose(fichProd);
    if (!flag) printf("No se ha encontrado el registro.");
}

void ordenarProductos(void){
    Producto prod;
    RegistrosProd regProd;
    Producto aux;

    int N, D, flag;
    int desplazar, i;

    N = regProd.numRegProd;
    D = N;

    while(D != 1) {
        D = D / 2;

        flag = 1;

        while(flag == 1) {
            flag = 0;

            for (i = 1; i <= N - D; i++) {
                desplazar = i * sizeof(prod);
                fseek(fichProd, desplazar, 0);
                fread(&prod, sizeof(prod), 1, fichProd);

                desplazar = (i + D) * sizeof(prod);
                fseek(fichProd, desplazar, 0);
                fread(&aux, sizeof(aux), 1, fichProd);

                if (strcmp(aux.codigo, prod.codigo) < 0) {
                    desplazar = i * sizeof(prod);
                    fseek(fichProd, desplazar, 0);
                    fwrite(&aux, sizeof(aux), 1, fichProd);

                    desplazar = (i + D) * sizeof(prod);
                    fseek(fichProd, desplazar, 0);
                    fwrite(&prod, sizeof(prod), 1, fichProd);

                    flag = 1;
                }
            }
        }
    }
}

void actualizarComprasProd(char codAnt[5], char codNv[5]) {
    Compra com;
    RegistrosCom regCom;

    int desplazar, i;
    fichCompras = fopen(FICH_COMPRAS, "r+b");

    fseek(fichCompras, 0, SEEK_SET);
    fread(&regCom, sizeof(regCom), 1, fichCompras);

    for (i = 1; i <= regCom.numRegCom; i++) {
        desplazar = i * sizeof(Compra);
        fseek(fichCompras, desplazar, SEEK_SET);
        fread(&com, sizeof(com), 1, fichCompras);

        if (strcmp(codAnt, com.id_producto) == 0) {
            strcpy(com.id_producto, codNv);

            fseek(fichCompras, desplazar, SEEK_SET);
            fwrite(&com, sizeof(com), 1, fichCompras);
        }
    }

    fclose(fichCompras);
}