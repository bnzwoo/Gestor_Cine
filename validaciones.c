#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "validaciones.h"

void leerString(char *buffer, int tam) {
    fgets(buffer, tam, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}


void validarTexto(const char *mensaje, char *buffer, int tam) {
    while (1) {
        printf("%s", mensaje);
        leerString(buffer, tam);
        
        if (strlen(buffer) > 0 && strspn(buffer, " \t\n") != strlen(buffer)) {
            break;
        }
        printf("Error: La entrada no puede estar vacia. Intente de nuevo.\n");
    }
}


int validarOpcionMenu() {
    char buffer[100];
    int valor;
    char *endptr;

    while (1) {
        printf("Ingrese una opcion: "); /* Mensaje fijo */
        leerString(buffer, sizeof(buffer));
        valor = (int)strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\0') {
            printf("Error: Ingrese un numero valido.\n");
        } 
        else if (valor < 0 || valor > 6) { /* Rango fijo */
            printf("Error: El valor debe estar entre 0 y 6.\n");
        } else {
            return valor;
        }
    }
}


int validarAnioPelicula() {
    char buffer[100];
    int valor;
    char *endptr;

    while (1) {
        printf("Ingrese Anio (1990-2025): "); 
        leerString(buffer, sizeof(buffer));
        valor = (int)strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\0') {
            printf("Error: Ingrese un numero valido.\n");
        } 
        else if (valor < 1990 || valor > 2025) { 
            printf("Error: El anio debe estar entre 1990 y 2025.\n");
        } else {
            return valor;
        }
    }
}


int validarDuracionPelicula() {
    char buffer[100];
    int valor;
    char *endptr;

    while (1) {
        printf("Ingrese Duracion (en minutos): "); 
        leerString(buffer, sizeof(buffer));
        valor = (int)strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\0') {
            printf("Error: Ingrese un numero valido.\n");
        } 
        else if (valor <= 0) { 
            printf("Error: La duracion debe ser mayor a 0.\n");
        } else {
            return valor;
        }
    }
}


float validarPuntuacionPelicula() {
    char buffer[100];
    float valor;
    char *endptr;

    while (1) {
        printf("Ingrese Puntuacion (0.0 - 10.0): "); 
        leerString(buffer, sizeof(buffer));
        valor = strtof(buffer, &endptr);

        if (endptr == buffer || *endptr != '\0') {
            printf("Error: Ingrese un numero decimal valido.\n");
        } 
        else if (valor < 0.0 || valor > 10.0) {
            printf("Error: La puntuacion debe estar entre 0.0 y 10.0.\n");
        } else {
            return valor;
        }
    }
}