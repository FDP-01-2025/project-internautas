#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
//

using namespace std;

const int SIZE = 6;     // tablero de 6x6
const int TILES = 20;   // solo 20 casillas en el borde

// Tipos de casilla personalizados
const int TYPE_GO = 0;
const int TYPE_PROPERTY = 1;
const int TYPE_CARD = 2;
const int TYPE_TAX = 3;             //id de cada tipo de casilla
const int TYPE_JAIL = 4;
const int TYPE_GOTOJAIL = 5;
const int TYPE_PARKING = 6;

struct Box {
    string Name;
    int Type;
    int Price;
    int Rent;
    int Owner;     // -1 = sin dueño
    int Houses;
    bool Hotel;
};


// Prototipos
void asignBox(int id);
void loadBoard(Box board[SIZE][SIZE]);
void showBoard(Box board[SIZE][SIZE]);

#endif