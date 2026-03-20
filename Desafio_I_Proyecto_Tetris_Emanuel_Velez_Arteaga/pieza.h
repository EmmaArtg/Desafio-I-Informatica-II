#ifndef PIEZA_H
#define PIEZA_H
#include <cstdint>

// Usamos mayúscula inicial por convención para estructuras
struct PiezaActiva {
    int id;       // Identificador de la pieza (0-6)
    int rotacion; // Estado de rotación actual (0-3)
    int x;        // Posición en X en el tablero
    int y;        // Posición en Y en el tablero
};

extern const uint8_t piezas[7][4][4];
extern const int alturapiezas[7][4];
extern const int anchopiezas[7][4];

#endif