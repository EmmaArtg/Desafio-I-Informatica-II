#include <QCoreApplication>
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include "tablero.h"

using namespace std;

int main() {
    int ancho;
    int  alto;
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
    uint8_t** tablero = new uint8_t*[alto];

    for (int i = 0; i < alto; i++) {
        tablero[i] = new uint8_t[bytesPorFila];
        for (int j = 0; j < bytesPorFila; j++) {
            tablero[i][j] = 0;
        }
    }
    srand((unsigned)time(0));
    bool jugando = true;

    while (jugando) {
        PiezaActiva actual;
        actual.id       = rand() % 7;
        actual.rotacion = 0;
        actual.x        = (ancho / 2) - 2;
        actual.y        = 0;

        if (!esMovimientoValido(tablero, alto, ancho, actual, actual.x, actual.y, actual.rotacion)) {
            imprimirTablero(tablero, alto, ancho, actual);
            cout << "\nGAME OVER\n";
            break;
        }

        bool piezaActiva = true;
        while (piezaActiva) {
            imprimirTablero(tablero, alto, ancho, actual);

            char accion;
            cin >> accion;

            switch (accion) {
            case 'a': case 'A':
                if (esMovimientoValido(tablero, alto, ancho, actual, actual.x - 1, actual.y, actual.rotacion))
                    actual.x--;
                break;
            case 'd': case 'D':
                if (esMovimientoValido(tablero, alto, ancho, actual, actual.x + 1, actual.y, actual.rotacion))
                    actual.x++;
                break;
            case 's': case 'S':
                if (esMovimientoValido(tablero, alto, ancho, actual, actual.x, actual.y + 1, actual.rotacion)) {
                    actual.y++;
                } else {
                    fijarPieza(tablero, ancho, actual);
                    limpiarFilas(tablero, alto, ancho);
                    piezaActiva = false;
                }
                break;
            case 'w': case 'W':
            {
                int nuevaRot = (actual.rotacion + 1) % 4;
                if (esMovimientoValido(tablero, alto, ancho, actual, actual.x, actual.y, nuevaRot))
                    actual.rotacion = nuevaRot;
            }
            break;
            case 'q': case 'Q':
                piezaActiva = false;
                jugando = false;
                break;
            default:
                break;
            }
        }
    }

    for (int i = 0; i < alto; i++) {
        delete[] tablero[i];
    }
    delete[] tablero;
    return 0;
}