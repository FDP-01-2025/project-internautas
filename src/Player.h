#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Constants.h"

using namespace std;

// ===================================================================
// DEFINITION OF THE PLAYER STRUCTURE
// ===================================================================

// The 'Player' structure stores all the information about a player.
struct Player
{
    string name;                      // Name of the player.
    int money;                        // Available money.
    int position;                     // Current position on the board (0-19).
    bool properties[BOARD_PERIMETER]; // Array that indicates the properties it has (true if it has it).
    int getOutOfJailCards;            // Card counter 'Get Out of Jail'.
    int turnsInJail;                  // Remaining shifts that he must spend in jail.
    bool isBankrupt;                  // Indicate if the player has gone bankrupt.
};

// --- Function Prototypes (declarations) ---
// The implementation of these functions is in Player.cpp.

// Create a new instance of Player with initial values.
Player createNewPlayer(string name);

// Displays the current state of a player in the console.
void printPlayerStatus(Player player);

// Returns the total number of properties owned by a player.
int countPlayerProperties(Player player);

#endif // PLAYER_H