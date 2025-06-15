#include "src/Player.h"
#include "src/Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>


using namespace std;

//Maximos jugadores : 2
const int MAX_PLAYERS = 2;
int main ()
{
    //Pedimos datos de cuantos jugadores seran
    Player Players[MAX_PLAYERS];
    int amountPlayers = MAX_PLAYERS;
    cout << "WELCOME TO MONOPOLY";
    

    //Bucle para validacion de datos evitando errores o mas de 5 o menos de 1 jugador

    //Llamamos nuestra funcion createPlayers
    createPlayers(Players, amountPlayers);

    //Imprimimos los datos de cada jugador
    for (int i= 0; i < amountPlayers; i++)
    {
    cout << "\nJugador " << i + 1 << ": " << Players[i].Name << ", $" << Players[i].Cash;
    }
    
   return 0;
}