#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "Player.h"

using namespace std;

// ===================================================================
// STATEMENTS OF THE MAIN ACTIONS OF THE GAME
// ===================================================================

// The 'GameState' structure is the central container that holds
// the entire game state, making it easier to pass between functions.
struct GameState
{
    Player players[NUM_PLAYERS]; // Array with the two players.
    int currentPlayerIndex;      // Current player index (0 or 1).
    bool isGameOver;             // Flag that indicates if the game has ended.
};

// --- Function Prototypes ---

// Initialize the random number generator.
void initializeRandom();

// Simulates the roll of a die (returns 1-6).
int rollDice();

// Returns the index of the player who owns a property, or -1 if it has no owner.
int getPropertyOwnerIndex(GameState gs, int propertyPosition);

// Logic for when a player lands on a property.
GameState handleProperty(GameState gs);

// Logic for when a player lands on a special card.
GameState handleSpecialCard(GameState gs);

// Logic to send a player to jail.
GameState handleGoToJail(GameState gs);

// Logic of a player's turn who is in jail.
GameState handleJailTurn(GameState gs);

// Logic for when a player lands on a tax square.
GameState handleTax(GameState gs);

#endif // GAME_ACTIONS_H