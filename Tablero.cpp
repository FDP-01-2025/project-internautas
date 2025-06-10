
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Tablero.h" //Llamamos nuestra libreria

using namespace std;

//Funcion createPLayers desarrolladas
void createPlayers(Player Players[], int Amount)
{
    for (int i = 0; i < Amount; i++)
    {
        //Bucle para asignar nombre al jugador y su datos
        cout << "Enter the name of player number " << i+1 << " :" << endl; 
        cin >> Players[i].Name;

        //Asignacion de datos para el jugador
        Players[i].Cash = 1500;
        Players[i].Position = 0;       
        Players[i].inJail = false;
        Players[i].turnsInJail = 0;

        // Asignacion de propiedades, incializamos en -1 para mejor lectura de datos
        for(int j = 0; j < MAX_PROPERTIES; j++)
        {
            Players[i].Properties[j]= -1;
        }
    }
}
