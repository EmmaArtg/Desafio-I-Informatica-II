#ifndef TABLERO_H
#define TABLERO_H
#include <cstdint>
#include "pieza.h"

void imprimirTablero(uint8_t** tablero, int alto, int ancho, const int* pieza);
bool esMovimientoValido(uint8_t** tablero, int alto, int ancho,
                        int id, int nuevaX, int nuevaY, int nuevaRot);
void fijarPieza(uint8_t** tablero, int ancho, const int* pieza);
int  limpiarFilas(uint8_t** tablero, int alto, int ancho);

#endif
