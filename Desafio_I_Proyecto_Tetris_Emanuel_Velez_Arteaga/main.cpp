#include <QCoreApplication>
#include <QRandomGenerator>
#include <iostream>
#include <cstdint>
#include "tablero.h"

using namespace std;

int main() {
    int ancho, alto;

    cout << "Ingrese el ancho (multiplo de 8, minimo 8): ";
    cin >> ancho;
    while (!(ancho >= 8 && ancho % 8 == 0)) {
        cout << "Invalido. Intenta de nuevo: ";
        cin >> ancho;
    }

    cout << "Ingrese el alto (minimo 8): ";
    cin >> alto;
    while (alto < 8) {
        cout << "Invalido. Intenta de nuevo: ";
        cin >> alto;
    }

    int bytesPorFila = ancho / 8;

    // Tablero con memoria dinámica
    uint8_t** tablero = new uint8_t*[alto];
    for (int i = 0; i < alto; i++) {
        tablero[i] = new uint8_t[bytesPorFila];
        for (int j = 0; j < bytesPorFila; j++)
            tablero[i][j] = 0;
    }

    int* pieza = new int[4];

    bool jugando = true;
    while (jugando) {
        pieza[0] = (int)QRandomGenerator::global()->bounded(7u);
        pieza[1] = 0;
        pieza[2] = (ancho / 2) - 2;
        pieza[3] = 0;

        if (!esMovimientoValido(tablero, alto, ancho,
                                pieza[0], pieza[2], pieza[3], pieza[1])) {
            imprimirTablero(tablero, alto, ancho, pieza);
            cout << "\n*** GAME OVER ***\n";
            break;
        }

        bool piezaActiva = true;
        while (piezaActiva) {
            imprimirTablero(tablero, alto, ancho, pieza);

            char accion;
            cin >> accion;

            switch (accion) {
            case 'a': case 'A':
                if (esMovimientoValido(tablero, alto, ancho,
                                       pieza[0], pieza[2] - 1, pieza[3], pieza[1]))
                    pieza[2]--;
                break;

            case 'd': case 'D':
                if (esMovimientoValido(tablero, alto, ancho,
                                       pieza[0], pieza[2] + 1, pieza[3], pieza[1]))
                    pieza[2]++;
                break;

            case 's': case 'S':
                if (esMovimientoValido(tablero, alto, ancho,
                                       pieza[0], pieza[2], pieza[3] + 1, pieza[1])) {
                    pieza[3]++;
                } else {
                    fijarPieza(tablero, ancho, pieza);
                    limpiarFilas(tablero, alto, ancho);
                    piezaActiva = false;
                }
                break;

            case 'w': case 'W': {
                int nuevaRot = (pieza[1] + 1) % 4;
                if (esMovimientoValido(tablero, alto, ancho,
                                       pieza[0], pieza[2], pieza[3], nuevaRot))
                    pieza[1] = nuevaRot;
                break;
            }

            case 'q': case 'Q':
                piezaActiva = false;
                jugando     = false;
                break;

            default:
                break;
            }
        }
    }
    delete[] pieza;
    for (int i = 0; i < alto; i++)
        delete[] tablero[i];
    delete[] tablero;

    return 0;
}