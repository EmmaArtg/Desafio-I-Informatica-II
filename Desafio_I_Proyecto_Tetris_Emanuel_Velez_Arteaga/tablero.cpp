#include "tablero.h"
#include <iostream>
using namespace std;

void imprimirTablero(uint8_t** tablero, int alto, int ancho, const int* pieza) {
    int bytesPorFila = ancho / 8;
    uint8_t* filaVisual = new uint8_t[bytesPorFila];

    const uint8_t* formaActual = piezas[pieza[0]][pieza[1]];

    for (int i = 0; i < alto; i++) {
        cout << "|";

        for (int j = 0; j < bytesPorFila; j++)
            filaVisual[j] = tablero[i][j];

        int filaLocal = i - pieza[3];
        if (filaLocal >= 0 && filaLocal < 4) {
            uint8_t filaPieza = formaActual[filaLocal];
            if (filaPieza != 0) {
                int indiceByte = pieza[2] / 8;
                int bitOffset  = pieza[2] % 8;
                if (indiceByte < bytesPorFila)
                    filaVisual[indiceByte] |= (filaPieza >> bitOffset);
                if (bitOffset > 0 && (indiceByte + 1) < bytesPorFila)
                    filaVisual[indiceByte + 1] |= (filaPieza << (8 - bitOffset));
            }
        }

        for (int j = 0; j < bytesPorFila; j++)
            for (int b = 7; b >= 0; b--)
                cout << ((filaVisual[j] & (1 << b)) ? '#' : '.');

        cout << "|\n";
    }

    delete[] filaVisual;
    cout << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";
}

bool esMovimientoValido(uint8_t** tablero, int alto, int ancho,
                        int id, int nuevaX, int nuevaY, int nuevaRot) {
    int bytesPorFila = ancho / 8;
    const uint8_t* forma = piezas[id][nuevaRot];
    int altPieza = alturapiezas[id][nuevaRot];
    int ancPieza = anchopiezas[id][nuevaRot];

    if (nuevaX < 0 || nuevaX + ancPieza > ancho) return false;

    for (int fila = 0; fila < altPieza; fila++) {
        int filaTablero = nuevaY + fila;
        if (filaTablero >= alto) return false;
        if (filaTablero < 0)    continue;

        uint8_t filaPieza = forma[fila];
        if (filaPieza == 0) continue;

        int indiceByte = nuevaX / 8;
        int bitOffset  = nuevaX % 8;
        uint8_t maskIzq = filaPieza >> bitOffset;
        uint8_t maskDer = (bitOffset > 0) ? (filaPieza << (8 - bitOffset)) : 0;

        if (indiceByte < bytesPorFila && (tablero[filaTablero][indiceByte] & maskIzq))
            return false;
        if (bitOffset > 0 && (indiceByte + 1) < bytesPorFila
            && (tablero[filaTablero][indiceByte + 1] & maskDer))
            return false;
    }
    return true;
}

void fijarPieza(uint8_t** tablero, int ancho, const int* pieza) {
    int bytesPorFila = ancho / 8;
    const uint8_t* forma = piezas[pieza[0]][pieza[1]];
    int altPieza = alturapiezas[pieza[0]][pieza[1]];

    for (int fila = 0; fila < altPieza; fila++) {
        int filaTablero = pieza[3] + fila;
        uint8_t filaPieza = forma[fila];
        if (filaPieza == 0) continue;

        int indiceByte = pieza[2] / 8;
        int bitOffset  = pieza[2] % 8;

        if (indiceByte < bytesPorFila)
            tablero[filaTablero][indiceByte] |= (filaPieza >> bitOffset);
        if (bitOffset > 0 && (indiceByte + 1) < bytesPorFila)
            tablero[filaTablero][indiceByte + 1] |= (filaPieza << (8 - bitOffset));
    }
}

int limpiarFilas(uint8_t** tablero, int alto, int ancho) {
    int bytesPorFila = ancho / 8;
    int filasLimpiadas = 0;

    for (int i = alto - 1; i >= 0; i--) {
        bool filaLlena = true;
        for (int j = 0; j < bytesPorFila; j++) {
            if (tablero[i][j] != 0xFF) { filaLlena = false; break; }
        }
        if (filaLlena) {
            for (int k = i; k > 0; k--) {
                uint8_t* temp = tablero[k];
                tablero[k]    = tablero[k - 1];
                tablero[k - 1] = temp;
            }
            for (int j = 0; j < bytesPorFila; j++) tablero[0][j] = 0;
            filasLimpiadas++;
            i++;
        }
    }
    return filasLimpiadas;
}