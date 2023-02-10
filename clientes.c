#include "clientes.h"
#include "compras.h"

void anadirCliente(void){
    Cliente cli;
    RegistrosCli regCli;

    fichCli = fopen(FICH_CLIENTES, "r+b");

    printf("\n* Alta de cliente\n");

    fseek(fichCli, 0, SEEK_SET);
    fread(&regCli, sizeof(regCli), 1, fichCli);

    int desplazar, flag = 0, i;
    char tel[9];

    for (i = 1; i <= regCli.numRegCli; i++) {
        desplazar = i * sizeof(Cliente);
        fseek(fichCli, desplazar, SEEK_SET);
        fread(&cli, sizeof(cli), 1, fichCli);

        if (strcmp("*", cli.telefono) == 0) {
            fflush(stdin);
            printf("Introduce el telefono del cliente: ");
            gets(cli.telefono);
            fflush(stdin);
            printf("Introduce su nombre: ");
            gets(cli.nombre);
            fflush(stdin);

            if(strlen(cli.telefono) == 9) {
                fseek(fichCli, desplazar, SEEK_SET);
                fwrite(&cli, sizeof(cli), 1, fichCli);
            }

            flag = 1;
        }
    }
    if (!flag) {
        fflush(stdin);
        printf("Introduce el telefono del cliente: ");
        gets(cli.telefono);
        printf("Introduce su nombre: ");
        gets(cli.nombre);
        fflush(stdin);

        if(strlen(cli.telefono) == 9){
            desplazar = (regCli.numRegCli + 1) * sizeof(Cliente);
            fseek(fichCli, desplazar, SEEK_SET);
            fwrite(&cli, sizeof(cli), 1, fichCli);

            regCli.numRegCli++;
            fseek(fichCli, 0, SEEK_SET);
            fwrite(&regCli, sizeof(regCli), 1, fichCli);
        }
    }

    fclose(fichCli);
}

void listarClientes(void) {
    Cliente cli;
    RegistrosCli regCli;

    int desplazar, i;

    fichCli = fopen(FICH_CLIENTES, "rb");

    printf("\n* Listado de clientes\n");

    fseek(fichCli, 0, SEEK_SET);
    fread(&regCli, sizeof(regCli), 1, fichCli);

    //ordenarClientes();

    for (i = 1; i <= regCli.numRegCli; i++) {
        desplazar = i * sizeof(Cliente);
        fseek(fichCli, desplazar, SEEK_SET);
        fread(&cli, sizeof(cli), 1, fichCli);

        if (strcmp("*", cli.telefono) != 0) {
            printf("Telefono: %s", cli.telefono);
            printf("\tNombre: %s\n", cli.nombre);
        }
    }

    fclose(fichCli);
}

void buscarCliente(void) {
    Cliente cli;
    RegistrosCli regCli;

    fichCli = fopen(FICH_CLIENTES, "rb");

    printf("\n* Consulta de cliente\n");

    fseek(fichCli, 0, SEEK_SET);
    fread(&regCli, sizeof(regCli), 1, fichCli);

    char tel[9];
    int desplazar, flag = 0, i;

    fflush(stdin);
    printf("Introduce el telefono del cliente a buscar: ");
    gets(tel);

    for (i = 1; i <= regCli.numRegCli; i++) {
        desplazar = i * sizeof(Cliente);
        fseek(fichCli, desplazar, SEEK_SET);
        fread(&cli, sizeof(cli), 1, fichCli);

        if (strcmp(tel, cli.telefono) == 0) {
            printf("Telefono: %s", cli.telefono);
            printf("\tNombre: %s\n\n", cli.nombre);

            flag = 1;
        }
    }

    fclose(fichCli);

    if(!flag) printf("No se ha encontrado ningun cliente con ese telefono.\n");
}

void modificarCliente(void) {
    Cliente cli;
    RegistrosCli regCli;

    fichCli = fopen(FICH_CLIENTES, "r+b");

    printf("\n* Modificaciones de clientes\n");

    fseek(fichCli, 0, SEEK_SET);
    fread(&cli, sizeof(cli), 1, fichCli);

    int desplazar, flag = 0, i;
    char tel[9];

    fflush(stdin);
    printf("Introduce el telefono del cliente a modificar: ");
    gets(tel);

    for (i = 1; i <= regCli.numRegCli; i++) {
        desplazar = i * sizeof(Cliente);
        fseek(fichCli, desplazar, SEEK_SET);
        fread(&cli, sizeof(cli), 1, fichCli);

        if (strcmp(tel, cli.telefono) == 0) {
            flag = 1;

            puts("Introduce los nuevos datos del cliente:\n");
            printf("Introduce el telefono del cliente: ");
            gets(cli.telefono);
            printf("Introduce su nombre: ");
            gets(cli.nombre);
            fflush(stdin);

            if(strlen(cli.telefono) == 9){
                fseek(fichCli, desplazar, SEEK_SET);
                fwrite(&cli, sizeof(cli), 1, fichCli);

                actualizarComprasCli(tel, cli.telefono);
            }
        }
    }

    fclose(fichCli);

    if (!flag) printf("No se ha encontrado el registro.");
}

void ordenarClientes(void){
    Cliente cli;
    RegistrosCli regCli;
    Cliente aux;

    int N, D, flag;
    int desplazar, i;

    fichCli = fopen(FICH_CLIENTES, "r+b");

    fseek(fichCli, 0, 0);
    fread(&regCli, sizeof(regCli), 1, fichCli);

    N = regCli.numRegCli;
    D = N;

    do {
        D = D / 2;

        do {
            flag = 0;

            for (i = 1; i <= N - D; i++) {
                desplazar = i * sizeof(cli);
                fseek(fichCli, desplazar, 0);
                fread(&cli, sizeof(cli), 1, fichCli);

                desplazar = (i + D) * sizeof(aux);
                fseek(fichCli, desplazar, 0);
                fread(&aux, sizeof(aux), 1, fichCli);

                if (strcmp(aux.telefono, cli.telefono) < 0) {
                    desplazar = i * sizeof(aux);
                    fseek(fichCli, desplazar, 0);
                    fwrite(&aux, sizeof(aux), 1, fichCli);

                    desplazar = (i + D) * sizeof(cli);
                    fseek(fichCli, desplazar, 0);
                    fwrite(&cli, sizeof(cli), 1, fichCli);
                }
            }

        } while(flag == 1);
    } while(D != 1);

    fclose(fichCli);
}

void actualizarComprasCli(char codAnt[9], char codNv[9]){
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

        if (strcmp(codAnt, com.id_cliente) == 0) {
            strcpy(com.id_cliente, codNv);

            fseek(fichCompras, desplazar, SEEK_SET);
            fwrite(&com, sizeof(com), 1, fichCompras);
        }
    }

    fclose(fichCompras);
}