#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

void informacion(char* buffer);
int list();
int create();
int edit();
int delete();


int main(){
    int bucle = 0;
    while(bucle == 0){
        char input[1];
        // reed the user input
        informacion(input);
        // printf("%s\n", input);
        // call the respective function
        switch (input[0])
        {
        case 'l'/* constant-expression */:
            list();
            break;
        case 'c':
            create();
            break;
        case 'a':
            edit();
            break;
        case 'e':
            delete();
            break;
        case 'q':
            bucle = 1;
            break;
        default:
            break;
        }
    }
    return 0;
}

void informacion(char* buffer){
    printf("\n\n\n");
    printf("Que quieres hacer?\n\n");
    printf("Listar los archivos en el directorio: l\n");
    printf("Crear un archivo: c\n");
    printf("Abrir un archivo: a\n");
    printf("Eliminar un archivo: e\n");
    printf("Salir del programa: q\n");
    printf("Que eliges? : ");
    // save the user input in buffer
    scanf("%1s", buffer);
    printf("\n\n\n");
}

int list(){
    // opendir() returns a pointer of DIR type.
    // defino un puntero hacia un directorio
    DIR *dr = opendir(".");
    //defino una estructura que almacena el contenido del directorio
    struct dirent *de;


    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Hubo un error al abrir la carpeta");
        return 1;
    }
    int contador = 0;
    // for readdir()
    while ((de = readdir(dr)) != NULL){
        if (de->d_name[1] != '.' && de->d_name[0] != '.'){
            printf("%d   %s\n", contador, de->d_name);
            contador++;
        }
    }
    //se cierra el directorio
    closedir(dr);
    return 0;
}
int create(){
    //preguntar por el nombre del archivo
    char nombre[64];
    printf("Escribe el nombre del archivo : ");
    // save the user input in buffer
    scanf("%s", &nombre);
    if (nombre[0] == NULL){
        printf("El nombre del archivo esta vacio o es invalido");
        return 1;
    }
    //crear el archivo con la funcion FOPEN
    FILE* archivo = fopen(nombre, "w");
    //cerrar el archivo
    fclose(archivo);
    //listar los directorios
    list();
    rerurn 0;
}
int edit(){

}
int delete(){

}

