/*
FUNCIONES A DESARROLLAR AQUI:

cargarTablero - Carlos

mostrarTablero - Carlos

propiedadDisponible - Carlos

comprarPropiedad - Carlos

pagarRenta - Carlos

construirCasa - Rodri

construirHotel - Rodri

puedeConstruir - Rodri

contarCasas - Rodri

RECORDAR HACERLO EN INGLES

*/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

#include <iostream>
#include <cstring>

#define SIZE 11
#define TILES 40

const int TYPE_GO         = 0;
const int TYPE_PROPERTY   = 1;
const int TYPE_TAX        = 2;
const int TYPE_JAIL       = 3;
const int TYPE_CHANCE     = 4;
const int TYPE_GO_TO_JAIL = 5;
const int TYPE_UTILITY    = 6;
const int TYPE_RAILROAD   = 7;
const int TYPE_PARKING    = 8;

struct Box {
    char Name[30];
    int  Type;
    int  Price;
    int  Rent;
    int  Owner;
    int  Houses;
    bool Hotel;
};

// Prototipos
void asignBox(Box &box, int id);
void loadBoard(Box board[SIZE][SIZE]);
void showBoard(Box board[SIZE][SIZE]);

#endif