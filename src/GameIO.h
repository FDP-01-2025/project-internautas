#ifndef GAMEIO_H
#define GAMEIO_H

#include "Player.h"
#include "GameActions.h" // It is included so you can know the GameState structure.

// ===================================================================
// INPUT/OUTPUT FUNCTION DECLARATIONS (SAVE/LOAD)
// ===================================================================

// Auxiliary structure to return the two names of the saved game.
struct SavedPlayerNames
{
    string p1_name;
    string p2_name;
};

// --- Function Prototypes ---

// Returns 'true' if the control file exists "savegame.txt".
bool doesSaveExist();

// Read and return the names of the players from "savegame.txt".
SavedPlayerNames getSavedPlayerNames();

// Load the data of a single player from their file .txt.
Player loadPlayer(string name);

// Save the complete state of the current game.
void saveGame(GameState gs);

// Delete all files from the previous saved game.
void deleteOldSaveFiles();

#endif // GAMEIO_H