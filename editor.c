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

typedef struct ln{
    int numero;
    int inicio[64];
    int final[64];
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
            case 'l':
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
        if (archivo->d_name[0] != '.' && archivo->d_name[1] != '.'){
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
    while (eleccion > archivos.numero || eleccion < 0){
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

    int bucle = 1;
    while(bucle==1){
        FILE* archivo = fopen(rutaCompleta, "r");
        //manda el cursor del archivo al final del docuemento
        fseek(archivo, 0, SEEK_END);
        long longitud_archivo = ftell(archivo);
        fseek(archivo, 0, SEEK_SET);

        //lee todos los caracteres del archivo y crea la cadena donde guardarlos
        char *buffer = malloc(sizeof(char) * longitud_archivo);
        fread(buffer, longitud_archivo, 1, archivo);

        // buffer[longitud_archivo] = '\0'; // Terminar la cadena

        struct ln linea;
        linea.inicio[0] = 0;

        int contador = 0;
        int lineas = 1;

        printf("0:  ");
        while (contador < longitud_archivo) {
            if (buffer[contador] == '\n') {
                printf("\n%d:  ", lineas);

                linea.numero = lineas - 1;
                linea.final[lineas - 1] = contador;
                linea.inicio[lineas] = contador + 1;

                lineas++;
            }
            else if( buffer[contador] == longitud_archivo){
                linea.final[lineas - 1] = contador;
            }
            else {
                printf("%c", buffer[contador]);
            }
            contador++;
        }


        printf("\n\n");


        int usuario;
        do {
            printf("Línea o q para salir del archivo o -1 para volver atrás: ");
            scanf("%i", &usuario);
            printf("\n");
            if (usuario == -1) return 0;
        } while (usuario > lineas || usuario < -1);


        printf("Inserta el texto:   ");

        char saved[1024];
        scanf(" %[^\n]%*c", saved);


        char *final = malloc(sizeof(char) * (longitud_archivo + strlen(saved) + 2)); // +2 para '\0' y un posible '\n'
        if (!final) {
            perror("Error al asignar memoria");
            return 1;
        }
        printf("USU %d\n", usuario);
        printf("LIENAS %d\n", lineas);
        printf("Saved- %s \n", saved);
        printf("Num line %d",linea.numero);printf("\n");
        printf("inicio %d",linea.inicio[usuario]);printf("\n");
        printf("final %d",linea.final[usuario]);printf("\n");
        printf("tamaño %d",strlen(buffer)) ;printf("\n");
        printf("Buffer:\n %s",buffer) ;printf("\n");
        printf("\n");printf("\n");printf("\n");


        printf("correcto\n");
        if (usuario == 0){

            printf("start\n");

            FILE *f = fopen(rutaCompleta, "w");
            if (f) {
                printf("%d\n", linea.final[usuario]);

                strcpy(final, saved);

                // printf("%s",final);
//                 :( magia
//                 arreglar esto
                if (linea.final[0] != 0 && usuario == 0){
                    printf("%d\n", linea.final[0]);
                    printf("%d\n", linea.final[1]);
                    // printf(strlen(buffer) - linea.final[0] + 1);
                    strcat(final, buffer + linea.final[0]);
//                     magia negra que no se como funciona :)))))
                    // for (int i = linea.final[0]; i <= strlen(buffer); i++){
                    //     printf("Saved: %s\n",buffer[i]);
                    //     strcat(final, buffer[i]);
                    // }
                }
                if (linea.final[usuario] == 0){
                    strcat(final, "\n");
                }
                // printf("%s",final);

                fwrite(final, strlen(final), 1, f);
                fclose(f);
                }
        }

        else if (usuario + 1 == lineas) {
            printf("append\n");

            // printf("Final:  %s\n", &final) ;printf("\n");

            strcpy(final, saved);
            strcat(final, "\n");
            FILE *f = fopen(rutaCompleta, "a");
            if (f) {
                fwrite(final, strlen(final), 1, f);
                fclose(f);
            } else {
                perror("Error al abrir el archivo para escribir");
            }
        }

        else{
            printf("Insertar\n");
            FILE *f = fopen(rutaCompleta, "w");
            if (f) {
//             escribir el principio
                fwrite(buffer, linea.final[usuario - 1] + 1, 1, f);
                printf("%s\n", buffer);
//             añadir el texto del usuario
                strcpy(final, saved);
                strcat(final,"\n");
                printf("%s\n", final);
                fwrite(final, strlen(final) + 1,1,f);
//             terminar de escribir lo que queda en el archivo
//                 buffer a partir de la línea despues de la seleccionada
//                 escribir los caracteres restantes
                fwrite(buffer + (linea.final[usuario] + 1), strlen(buffer) - linea.final[usuario] - 1,1,f);
                printf("%s", buffer + (linea.final[usuario] + 1));

            } else {
                perror("Error al abrir el archivo para escribir");
            }
            fclose(f);
        }

        // liberar memoria cerrando los archivos
        free(buffer);
        free(final);
        fclose(archivo);

    }
}
int delete(){
    int eleccion = -1;
    // conseguir la lista de archivos
    int i = 1;
    struct arch archivos = list(i);
    while (eleccion > archivos.numero || eleccion < 0){
        printf("Elige el archivo que quieres eliminar: ");
        // guardar la elección
        scanf(" %d", &eleccion);
        printf("\n");
    }
    // abrir el archivo en modo escritura
    //ceo la ruta completa donde guardar los archivos
    char rutaCompleta[256];
    //1º donde se guardarán los caracteres 2º el formato 3º los argumentos
    sprintf(rutaCompleta, "%s/%s", "./archivos", archivos.nombres[eleccion]);

    //elimina el archivo
    remove(rutaCompleta);
}

