//#include <stdlib.h>
#include <stdio.h>


void informacion(char* buffer);
int conversion_km();
int conversor_centimetros();
int nota_media();



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
            conversion_km();
            break;
        case 'c':
            nota_media();
            break;
        case 'a':
            conversor_centimetros();
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
    printf("\nQue quieres hacer?\n\n");
    printf("De km a millas: l\n");
    printf("Nota media: c\n");
    printf("De centímetros a pulgadas: a\n\n");
    printf("Cerrar el programa: q\n\n");
    // save the user input in buffer
    printf("Esctibe tu opción: ");
    scanf("%1s", buffer);
}

int conversion_km(){
    float km, millas;
    printf("Introduce los km: ");
    scanf("%f", &km);
    millas = km*0.62137;
    printf("%.2f kilómetros son %.2f millas\n", km , millas);
}
int nota_media(){
    float teoria, practica, comportamiento;
    printf("Teoría: ");
    scanf("%f", &teoria);

    printf("Práctica: ");
    scanf("%f", &practica);

    printf("Comportamiento: ");
    scanf("%f", &comportamiento);

    float nota_media = teoria* 0.3 + practica * 0.5 + comportamiento * 0.2;
    printf("Tu nota media es: %.2f\n", nota_media);
}
int conversor_centimetros(){
    float cm, pulgadas;
    printf("Introduce los cm: ");
    scanf("%f", &cm);
    pulgadas = cm*0.3937;
    printf("%.2f centímetro son %.2f pulgadas\n", cm , pulgadas);
}

