//Definimos nuestra libreria
#ifndef PLAYER_H
#define PLAYER_H


/*
FUNCIONES A DESARROLLAR AQUI:

crearJugadores

mostrarEstadoJugador
                                //Carlos todo
jugadorEnBancarrota

eliminarJugador

RECORDAR HACERLO EN INGLES

*/

#include <string>

using namespace std;

//definimos el maximo de propiedades
const int MAX_PROPERTIES = 20;
const int MAX_CARDS = 3;

//Data estructural para el jugador
struct Player 
{
    char Name [25];

    int Cash;
    int Position;
    int Properties[MAX_PROPERTIES];
    int totalProperties;
    int Cards [MAX_CARDS]; //Cuantas cartas de tipo salir de carcel puede almacernar (manejar segun id)
    int numCards;   // conteo de cartas, pues el array de arriba no siempre estara lleno.
    bool inJail;
    int turnsInJail;
};

//declaracion de la funcion (Prototipo)
void createPlayers(Player Players[], int Amount);


#endif