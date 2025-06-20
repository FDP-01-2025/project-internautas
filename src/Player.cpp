#include <iostream>
#include <cstring>     // para strcpy
#include "Player.h"

using namespace std;

void createPlayers(Player Players[], int Amount)
{
    for (int i = 0; i < Amount; i++)
    {
        cout << "Enter the name of player number " << i + 1 << ": ";
        char inputName[25];
        cin >> inputName;
        strcpy(Players[i].Name, inputName);  // Guardar nombre en el struct

        // Inicializar datos
        Players[i].Cash = 1500;
        Players[i].Position = 0;
        Players[i].inJail = false;
        Players[i].turnsInJail = 0;

        // Inicializar propiedades
        Players[i].totalProperties = 0;
        for (int j = 0; j < MAX_PROPERTIES; j++)
        {
            Players[i].Properties[j] = -1;
        }

        // Inicializar cartas
        Players[i].numCards = 0;
        for (int j = 0; j < MAX_CARDS; j++)
        {
            Players[i].Cards[j] = -1;
        }
    }
}
