#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

void informacion(char* buffer);
struct arch list(opcion);
int create();
int edit();
int delete();

//estructura de datos para almacenar archivos
typedef struct arch
{
    //la posición de la carpeta
    int numero;
    //informacion sobre el archivo
    struct dirent *archivo_info;
};


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
    printf("\n\n\n");
}

struct arch list(int opcion){
    // opendir() returns a pointer of DIR type.
    // defino un puntero hacia el directorio 
    DIR *dr = opendir("./archivos");
    //defino una estructura que almacena el contenido del directorio y su posición
    struct arch archivo;
    archivo.numero = 0;

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Hubo un error al abrir la carpeta");
        return;
    }
    int contador = 0;

    // leo el nombre de los archivos con la función readdir(dr) dr siendo la carpta
    while ((archivo.archivo_info = readdir(dr)) != NULL){
        if (archivo.archivo_info->d_name[1] != '.' && archivo.archivo_info->d_name[0] != '.'){
            if (opcion == 1){
                //Muestro los archivos en pantalla
                printf("%d      %s\n", archivo.numero , archivo.archivo_info->d_name);
                printf("\n\n");
            }
            //añado los datos a la variable archivo sin mostrarlos en la pantalla para mantene la cuenta
            archivo.numero++;
        }
    }
    //se cierra el directorio
    closedir(dr);
    return archivo;
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

}
int delete(){

}

