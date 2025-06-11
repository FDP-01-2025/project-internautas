//Definimos nuestra libreria
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

//definimos el maximo de propiedades
const int MAX_PROPERTIES = 28;

//Data estructural para el jugador
struct Player 
{
    string Name;

    int Cash;
    int Position;
    int Properties[MAX_PROPERTIES];
    int totalProperties;
    bool inJail;
    int turnsInJail;
};

//declaracion de la funcion (Prototipo)
void createPlayers(Player Players[], int Amount);


#endif