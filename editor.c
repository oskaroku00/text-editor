#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define NUM_nombres 100
#define NUM_letras 64
// estructura de datos para almacenar archivos
typedef struct arch{
    //la posición de la carpeta
    int numero;
    //informacion sobre el archivo
    char nombres[NUM_nombres][NUM_letras];
};

void informacion(char* buffer);
struct arch list(opcion);
int create();
int edit();
int delete();



int main(){
    int bucle = 0;
    //lista global de los archivos
    struct arch archivo;
    while(bucle == 0){
        char input[1];
        // reed the user input
        informacion(input);
        // printf("%s\n", input);
        // call the respective function
        int i = 1;
        switch (input[0])
        {
        case 'l'/* constant-expression */:
            archivo = list(i);
            break;
        case 'c':
            create();
            break;
        case 'a':
            edit(archivo);
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
    // printf("\n\n\n");
    printf("Que quieres hacer?\n\n");
    printf("Listar los archivos en el directorio: l\n");
    printf("Crear un archivo: c\n");
    printf("Abrir un archivo: a\n");
    printf("Eliminar un archivo: e\n");
    printf("Salir del programa: q\n");
    printf("Que eliges? : ");
    // save the user input in buffer
    scanf("%1s", buffer);
    printf("\n\n");
}

struct arch list(int opcion){
    // opendir() returns a pointer of DIR type.
    // defino un puntero hacia el directorio 
    DIR *dr = opendir("./archivos");
    //defino una estructura que almacena el contenido del directorio y su posición
    struct dirent *archivo;
    struct arch archivos;
    archivos.numero = 0;

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Hubo un error al abrir la carpeta");
        return;
    }
    int contador = 0;

    // leo el nombre de los archivos con la función readdir(dr) dr siendo la carpta
    while ((archivo = readdir(dr)) != NULL){
        if (archivo->d_name[1] != '.' && archivo->d_name[0] != '.'){
            if (opcion == 1){
                //Muestro los archivos en pantalla
                printf("%d:  %s\n", contador, archivo->d_name);
            }
            //añado los datos a la variable archivo sin mostrarlos en la pantalla para mantene la cuenta
            archivos.numero++;
            // copiar los nombres de los archivos
            strcpy(archivos.nombres[contador], archivo->d_name);
            contador++;
        }
    }
    printf("\n\n");
    //se cierra el directorio
    closedir(dr);
    return archivos;
}
int create(){
    //preguntar por el nombre del archivo
    char nombre[64];
    printf("Escribe el nombre del archivo, si quieres poner espacios usa _ ya que no se guardará con ese nombre : ");
    // save the user input in buffer
    scanf("%s", &nombre);
    if (nombre[0] == "\0"){
        printf("El nombre del archivo esta vacio o es invalido");
        return 1;
    }
    //ceo la ruta completa donde guardar los archivos
    char rutaCompleta[256];
    //1º donde se guardarán los caracteres 2º el formato 3º los argumentos
    sprintf(rutaCompleta, "%s/%s", "./archivos", nombre);

    //crear el archivo con la funcion FOPEN
    FILE* archivo = fopen(rutaCompleta, "w");
    //cerrar el archivo
    fclose(archivo);
    //actualizar los directorios
    int i = 0;
    list(i);
    return 0;
}
int edit(){
    int eleccion = -1;
    // conseguir la lista de archivos
    int i = 1;
    struct arch archivos = list(i);
    while (eleccion > archivos.numero -1 || eleccion < 0){
        printf("Elige el archivo que quieres editar: ");
        // guardar la elección
        scanf(" %d", &eleccion);
        printf("\n");
    }
    // abrir el archivo en modo escritura
    //ceo la ruta completa donde guardar los archivos
    char rutaCompleta[256];
    //1º donde se guardarán los caracteres 2º el formato 3º los argumentos
    sprintf(rutaCompleta, "%s/%s", "./archivos", archivos.nombres[eleccion]);

    FILE* archivo = fopen(rutaCompleta, "r");
    char buffer[1024];

    //lee todos los caracteres del documento maximo 1024 caracteres
    fread(buffer, sizeof(buffer), 1, archivo);

    printf(buffer);

    printf("\nNuevo\n");
    char bb[1];


    int linea, contador = 0;

    rewind(archivo);
    while (!feof(bb)){
        fread(bb, sizeof(bb), 1, archivo);
        // printf(bb[0]);
        if(strcmp(bb[0], '\n')){
            printf("%d-");
            linea++;
        }
        else {
            printf("%c", bb[0]);
        }
    }


    printf("\nNuevo\n");



    // feof detecta el caracter final del documento
    while ( !feof( buffer[contador] )){
        if(strcmp(buffer[contador], '\n')){
            printf("%d-");
            linea++;
        }
        else {
            printf("%c", buffer[contador]);
        }
        contador++;
    }

    fclose(archivo);
    printf("\n\n\n");
    return 0;
}
int delete(){

}

