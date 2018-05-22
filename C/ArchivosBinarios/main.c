#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nombre[20];
    char direccion[30];
    int telefono;
}Contacto;

void menu (char* nombreArchivo);
Contacto crearContacto();
void guardarContacto(Contacto contacto, char* nombreArchivo);
void mostrarAgenda(char* nombreArchivo);
void pausar();

int main(){
    char nombreArchivo[12]= "agenda.bin";
	menu (nombreArchivo);
    return 0;
}

void menu(char* nombreArchivo){
    int opcion;

    do{
        system("cls");
        printf("1. Crear contacto\n");
        printf("2. Consultar agenda\n");
        printf("3. Salir\n\n");
        printf("Ingresar una opcion: ");
        scanf(" %d", &opcion);

        if (opcion>0 && opcion<4){
            system("cls");
            switch(opcion){
                case 1:
                    guardarContacto(crearContacto(), nombreArchivo);
                    break;
                case 2:
                    mostrarAgenda(nombreArchivo);
                    break;
                case 3:
                    printf("Fin del programa\n");
                    pausar();
                    break;
            }
        }
        else{
            printf("\nOpcion no contemplada\n");
            pausar();
        }
    }while (opcion!=3);
}

Contacto crearContacto(){
    Contacto contacto;

    printf("Nombre: ");
    scanf(" %[^\n]", contacto.nombre);
    printf("Direccion: ");
    scanf(" %[^\n]", contacto.direccion);
    printf("Telefono: ");
    scanf(" %d", &contacto.telefono);

    return contacto;
}

void guardarContacto(Contacto contacto, char* nombreArchivo){
    FILE* file= fopen(nombreArchivo, "ab");

    if (file==NULL){
        printf("Error al intentar acceder al archivo\n");
        pausar();
    }
    else{
        fwrite(&contacto, sizeof(Contacto), 1, file);
        printf("\nContacto guardado!\n");
        pausar();
        fclose(file);
    }
}

void mostrarAgenda(char* nombreArchivo){
    FILE* file= fopen(nombreArchivo, "rb");

    if (file==NULL){
        printf("Error al intentar acceder al archivo\n");
        pausar();
    }
    else{
        Contacto contacto;
        printf("%-20s %-30s %-10s\n\n", "Nombre", "Direccion", "Telefono");
        while (fread(&contacto, sizeof(Contacto), 1, file)){
            printf("%-20s %-30s %-10d\n", contacto.nombre, contacto.direccion,
                    contacto.telefono);
        }
        fclose(file);
        printf("\n\n");
        pausar();
    }
}

void pausar(){
    printf("Presione ENTER para continuar");

    while (getchar() != '\n');
    getchar();

    printf("");
}
