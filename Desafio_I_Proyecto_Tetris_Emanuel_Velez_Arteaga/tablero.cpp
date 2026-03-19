#include "tablero.h"
#include <iostream>
using namespace std;

void imprimirtablero(uint8_t** tablero, int alto, int ancho)
{
    int bytesPerRow = ancho / 8;

    for(int i = 0; i < alto; i++)
    {
        for(int j = 0; j < bytesPerRow; j++)
        {
            for(int b = 7; b >= 0; b--)
            {
                if(tablero[i][j] & (1 << b))
                    cout << "#";
                else
                    cout << ".";
            }
        }
        cout << "\n";
    }
}