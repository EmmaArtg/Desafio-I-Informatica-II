#include <QCoreApplication>
#include <iostream>
#include <cstdint>
using namespace std;
int main()
{
    int ancho,alto;
    cout << "Ingrese un valor para el ancho tablero (Multiplo de 8, minimo 8): ";
    cin >> ancho;
    cout << "Ingrese un valor para el alto del tablero(Minimo 8): ";
    cin >> alto;

    while(!(ancho >= 8 && ancho % 8 == 0)){
        cout << "Ancho invalido verifica los datos de nuevo";
        cin >> ancho;
    }
    while( alto < 8){
        cout << "Alto invalido verifica los datos ingresados";
        cin >> alto;
    }
    int bytesPerRow = ancho/8;

    uint8_t** tablero = new uint8_t*[alto];
    for(int i=0; i < alto; i++){
        tablero[i] = new uint8_t[bytesPerRow];
        for (int j = 0; j < bytesPerRow; ++j){
            tablero[i][j] =0;
        }
    }

    for(int i =0; i < alto;i++){
        delete[] tablero[i];
    }
    delete[]tablero;

    return 0;
}
