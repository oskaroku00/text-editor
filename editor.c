#include <stdlib.h>
#include <stdio.h>


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
    printf("Que quieres hacer?\n\n");
    printf("Listar los archivos en el directorio: l\n");
    printf("Crear un archivo: c\n");
    printf("Abrir un archivo: a\n");
    printf("Eliminar un archivo: e\n");
    printf("Salir del programa: q\n");
    printf("Que eliges? : ");
    // save the user input in buffer
    scanf("%1s", buffer);
}

int list(){

}
int create(){

}
int edit(){

}
int delete(){

}

