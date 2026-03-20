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

    for (int i = 0; i < alto; i++) {
        delete[] tablero[i];
    }
    delete[] tablero;
    return 0;
}