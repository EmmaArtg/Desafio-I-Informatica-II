#ifndef PIEZA_H
#define PIEZA_H
#include <cstdint>

struct PiezaActiva {
    int id;
    int rotacion;
    int x;
    int y;
};

extern const uint8_t piezas[7][4][4];
extern const int alturapiezas[7][4];
extern const int anchopiezas[7][4];

#endif