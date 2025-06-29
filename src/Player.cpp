#include "Player.h"
#include <iostream>

using namespace std;

// ===================================================================
// IMPLEMENTATION OF PLAYER FUNCTIONS
// ===================================================================

// Implementation of the function to create a new player.
Player createNewPlayer(string name)
{
    Player newPlayer;
    newPlayer.name = name;
    newPlayer.money = STARTING_MONEY;
    newPlayer.position = 0;
    // Initialize the properties array, ensuring that the player does not own any at the start.
    for (int i = 0; i < BOARD_PERIMETER; ++i)
    {
        newPlayer.properties[i] = false;
    }
    newPlayer.getOutOfJailCards = 0;
    newPlayer.turnsInJail = 0;
    newPlayer.isBankrupt = false;
    return newPlayer; // Returns the structure of the newly created player.
}

// Implementation of the function to display the player's status.
void printPlayerStatus(Player player)
{
    cout << "-> Name: " << player.name << endl;
    cout << "-> Cash: $" << player.money << endl;
    cout << "-> Cards 'Getting Out of Jail': " << player.getOutOfJailCards << endl;
}

// Implementation of the function to count a player's properties.
int countPlayerProperties(Player player)
{
    int count = 0;
    // Iterate through the array of properties and add 1 for each 'true' you find.
    for (int i = 0; i < BOARD_PERIMETER; ++i)
    {
        if (player.properties[i])
        {
            count++;
        }
    }
    return count;
}