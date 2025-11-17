#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pelicula.h"
#include "validaciones.h"

#define NOMBRE_ARCHIVO "cartelera.txt"

int proximoId = 0;


Pelicula *crearPelicula() {
    Pelicula *nuevo = (Pelicula *)malloc(sizeof(Pelicula));
    if (nuevo == NULL) {
        printf("Error, No se pudo asignar memoria para la pelicula.\n");
        return NULL;
    }

    printf("\n--- Agregando Nueva Pelicula ---\n");
    
    nuevo->ID = proximoId;
    proximoId++;
    printf("ID Asignado: %d\n", nuevo->ID);

    
    validarTexto("Ingrese Titulo : ", nuevo->Titulo, 101);
    validarTexto("Ingrese Genero : ", nuevo->Genero, 31);
    validarTexto("Ingrese Clasificacion (ej: PG-13): ", nuevo->Clasificacion, 11);
    validarTexto("Ingrese Director : ", nuevo->Director, 51);

    nuevo->Duracion = validarDuracionPelicula();
    nuevo->Anio = validarAnioPelicula();
    nuevo->Puntuacion = validarPuntuacionPelicula();
   

    nuevo->sgte = NULL;
    return nuevo;
}

void agregarPelicula(Pelicula **inicio) {
    Pelicula *nuevo = crearPelicula();
    if (nuevo == NULL) return;

    if (*inicio == NULL) {
        *inicio = nuevo;
    } else {
        Pelicula *aux = *inicio;
        while (aux->sgte != NULL) {
            aux = aux->sgte;
        }
        aux->sgte = nuevo;
    }
    printf("\nPelicula '%s' agregada exitosamente.\n", nuevo->Titulo);
}

void mostrarCartelera(Pelicula *inicio) {
    if (inicio == NULL) {
        printf("\nLa cartelera esta vacia. No hay peliculas registradas.\n");
        return;
    }

    printf("\n--- CARTELERA DISPONIBLE ---\n");
    Pelicula *aux = inicio;
    while (aux != NULL) {
        
        printf("  ID: %d | Titulo: %s (%d)\n", aux->ID, aux->Titulo, aux->Anio);
        printf("  Genero: %s | Clasificacion: %s | Duracion: %d min\n", aux->Genero, aux->Clasificacion, aux->Duracion);
        printf("  Director: %s | Puntuacion: %.1f\n", aux->Director, aux->Puntuacion);
        printf("--------------------------------------------------\n");
        aux = aux->sgte;
    }
}

void ordenarPorPuntuacion(Pelicula *arr, int n) {
    int i, j;
    Pelicula temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].Puntuacion < arr[j + 1].Puntuacion) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void mostrarPeliculasOrdenadas(Pelicula *inicio) {
    if (inicio == NULL) {
        printf("\nLa cartelera esta vacia.\n");
        return;
    }

    int n = 0;
    Pelicula *aux = inicio;
    while (aux != NULL) {
        n++;
        aux = aux->sgte;
    }

    Pelicula *atemp = (Pelicula *)malloc(n * sizeof(Pelicula));
    if (atemp == NULL) {
        printf("Error. No se pudo asignar memoria.\n");
        return;
    }

    aux = inicio;
    for (int i = 0; i < n; i++) {
        atemp[i] = *aux;
        aux = aux->sgte;
    }

    ordenarPorPuntuacion(atemp, n);

    printf("\n--- PELICULAS ORDENADAS POR PUNTUACION (Mayor a Menor) ---\n");
    for (int i = 0; i < n; i++) {
        printf("Puntuacion: %.1f | Titulo: %s (%d)\n",
               atemp[i].Puntuacion,
               atemp[i].Titulo,
               atemp[i].Anio);
    }
    printf("-----------------------------------------------------------\n");

    free(atemp);
}

void buscarPeliculaPorTitulo(Pelicula *inicio) {
    if (inicio == NULL) {
        printf("\nLa cartelera esta vacia. No se puede buscar.\n");
        return;
    }

    char tituloBuscado[101];
    
    validarTexto("\nIngrese el titulo a buscar: ", tituloBuscado, 101);
   

    Pelicula *aux = inicio;
    int encontrado = 0;
    while (aux != NULL) {
        if (strcmp(aux->Titulo, tituloBuscado) == 0) {
            printf("\n--- PELICULA ENCONTRADA ---\n");
            printf("ID: %d | Titulo: %s (%d)\n", aux->ID, aux->Titulo, aux->Anio);
            printf("  Genero: %s | Clasificacion: %s | Duracion: %d min\n", aux->Genero, aux->Clasificacion, aux->Duracion);
            printf("  Director: %s | Puntuacion: %.1f\n", aux->Director, aux->Puntuacion);
            printf("-------------------------------\n");
            encontrado = 1;
            break;
        }
        aux = aux->sgte;
    }

    if (encontrado == 0) {
        printf("\nLa pelicula no fue encontrada.\n");
    }
}

void guardarCartelera(Pelicula *inicio) {
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "w");
    if (archivo == NULL) {
        printf("Error. No se pudo abrir el archivo\n");
        return;
    }

    if (inicio == NULL) {
        printf("\nLista vacia. No hay nada para guardar. \n");
        fclose(archivo);
        return;
    }

    Pelicula *aux = inicio;
    while (aux != NULL) {
        fprintf(archivo, "%d|%s|%s|%s|%d|%d|%s|%.1f\n",
                aux->ID, aux->Titulo, aux->Genero, aux->Clasificacion,
                aux->Duracion, aux->Anio, aux->Director, aux->Puntuacion);
        aux = aux->sgte;
    }

    fclose(archivo);
    printf("\nCartelera guardada exitosamente en %s.\n", NOMBRE_ARCHIVO);
}

void cargarCartelera(Pelicula **inicio) {
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "r");
    if (archivo == NULL) {
        printf("\nNo se encontro el archivo %s. Se iniciara con una cartelera vacia.\n", NOMBRE_ARCHIVO);
        return;
    }

    liberarMemoria(inicio);
    proximoId = 0;
    printf("\nCargando cartelera desde %s...\n", NOMBRE_ARCHIVO);

    int maxId = -1;
    
    int id, duracion, anio;
    char titulo[101], genero[31], clasificacion[11], director[51];
    float puntuacion;

    while (fscanf(archivo, "%d|%100[^|]|%30[^|]|%10[^|]|%d|%d|%50[^|]|%f\n",
                  &id, titulo, genero, clasificacion,
                  &duracion, &anio, director, &puntuacion) == 8)
    {
        Pelicula *nuevo = (Pelicula *)malloc(sizeof(Pelicula));
        if (nuevo == NULL) {
            printf("Error de memoria al cargar.\n");
            break;
        }

        nuevo->ID = id;
        strcpy(nuevo->Titulo, titulo);
        strcpy(nuevo->Genero, genero);
        strcpy(nuevo->Clasificacion, clasificacion);
        nuevo->Duracion = duracion;
        nuevo->Anio = anio;
        strcpy(nuevo->Director, director);
        nuevo->Puntuacion = puntuacion;
        nuevo->sgte = NULL;

        if (*inicio == NULL) {
            *inicio = nuevo;
        } else {
            Pelicula *aux = *inicio;
            while (aux->sgte != NULL) {
                aux = aux->sgte;
            }
            aux->sgte = nuevo;
        }

        if (id > maxId) {
            maxId = id;
        }
    }

    proximoId = maxId + 1;

    fclose(archivo);
    printf("Carga completada. %d peliculas cargadas.\n", proximoId);
}

void liberarMemoria(Pelicula **inicio) {
    if (*inicio == NULL) {
        return;
    }

    printf("\nLiberando memoria de la cartelera...\n");
    Pelicula *aux;
    while (*inicio != NULL) {
        aux = *inicio;
        *inicio = (*inicio)->sgte;
        free(aux);
    }
    
    *inicio = NULL; 
    
    printf("Memoria liberada.\n");
}