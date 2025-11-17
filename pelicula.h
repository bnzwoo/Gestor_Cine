#ifndef PELICULA_H
#define PELICULA_H

typedef struct Pelicula {
    int ID;
    char Titulo[101];
    char Genero[31];
    char Clasificacion[11];
    int Duracion;
    int Anio;
    char Director[51];
    float Puntuacion;
    struct Pelicula *sgte;
} Pelicula;


void agregarPelicula(Pelicula **inicio);

void mostrarCartelera(Pelicula *inicio);

void mostrarPeliculasOrdenadas(Pelicula *inicio);

void buscarPeliculaPorTitulo(Pelicula *inicio);

void guardarCartelera(Pelicula *inicio);

void cargarCartelera(Pelicula **inicio);

void liberarMemoria(Pelicula **inicio);

void ordenarPorPuntuacion(Pelicula *arr, int n);

#endif