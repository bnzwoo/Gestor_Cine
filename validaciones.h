#ifndef VALIDACIONES_H
#define VALIDACIONES_H

void leerString(char *buffer, int tam);
void validarTexto(const char *mensaje, char *buffer, int tam);
int validarOpcionMenu();
int validarAnioPelicula();
int validarDuracionPelicula();
float validarPuntuacionPelicula();

#endif