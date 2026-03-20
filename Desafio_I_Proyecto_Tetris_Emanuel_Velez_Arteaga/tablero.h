#ifndef TABLERO_H
#define TABLERO_H
#include <cstdint>
#include "pieza.h"

void imprimirTablero(uint8_t** tablero, int alto, int ancho, PiezaActiva actual);
bool esMovimientoValido(uint8_t** tablero, int alto, int ancho, PiezaActiva pieza, int nuevaX, int nuevaY, int nuevaRot);
void fijarPieza(uint8_t** tablero, int ancho, PiezaActiva actual);
int limpiarFilas(uint8_t** tablero, int alto, int ancho);

#endif