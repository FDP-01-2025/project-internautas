#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Tablero.h"

using namespace std;

//Maximos jugadores : 4
const int MAX_PLAYERS = 4;
int main ()
{
    //Pedimos datos de cuantos jugadores seran
    Player Players[MAX_PLAYERS];
    int amountPlayers;
    cout << "Enter the number of players: ";
    

    //Bucle para validacion de datos evitando errores o mas de 5 o menos de 1 jugador
    do 
    {
        cin >> amountPlayers;

        if (!cin)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid. Please, do not enter any letter :)" << endl;
        }
        if(amountPlayers > 4 || amountPlayers <= 1)
        {
            cout << "Invalid. There must be only 2 to 4 players." << endl;
        } 

        cout << endl;

    } while (amountPlayers > 4 || amountPlayers <= 1);

    //Llamamos nuestra funcion createPlayers
    createPlayers(Players, amountPlayers);

    //Imprimimos los datos de cada jugador
    for (int i= 0; i < amountPlayers; i++)
    {
    cout << "\nJugador " << i + 1 << ": " << Players[i].Name << ", $" << Players[i].Cash;
    }
    
   return 0;
}