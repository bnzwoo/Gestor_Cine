#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pelicula.h"
#include "validaciones.h"

int main() {
    Pelicula *lista = NULL;
    int opcion;

    cargarCartelera(&lista);

    do {
        printf("\n--- GESTION DE CARTELERA DE CINE ---\n");
        printf("1. Agregar Pelicula a la cartelera\n");
        printf("2. Mostrar Cartelera\n");
        printf("3. Mostrar Peliculas Ordenadas por Puntuacion\n");
        printf("4. Buscar Pelicula por Titulo\n");
        printf("5. Guardar Cartelera en Archivo\n");
        printf("6. Cargar Cartelera desde Archivo\n");
        printf("0. Salir\n");
        
        
        opcion = validarOpcionMenu();

        switch (opcion) {
            case 1:

                agregarPelicula(&lista);
                break;

            case 2:

                mostrarCartelera(lista);
                break;

            case 3:

                mostrarPeliculasOrdenadas(lista);
                break;

            case 4:
                
                buscarPeliculaPorTitulo(lista);
                break;

            case 5:
                
                guardarCartelera(lista);
                break;

            case 6:
                printf("\nCargar desde archivo borrara la cartelera actual en memoria.\n");
                char confirm[10];
                validarTexto("Desea continuar? (s/n): ", confirm, 10);
                
                if (strcmp(confirm, "s") == 0 || strcmp(confirm, "S") == 0) {
                    cargarCartelera(&lista);
                } else {
                    printf("Carga cancelada.\n");
                }
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
        }
    } while (opcion != 0);

    liberarMemoria(&lista);
    
    return 0;
}