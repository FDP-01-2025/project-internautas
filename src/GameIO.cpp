#include "GameIO.h"
#include <fstream>
#include <iostream>
#include <cstdio> // Necessary for the remove() function that deletes files.

using namespace std;

// ===================================================================
// IMPLEMENTATION OF INPUT/OUTPUT FUNCTIONS (SAVE/LOAD)
// ===================================================================

// Internal auxiliary function to save the data of a single player in their .txt file.
void savePlayer(Player player)
{
    ofstream file(player.name + ".txt");
    if (file.is_open())
    {
        file << player.name << endl;
        file << player.money << endl;
        file << player.position << endl;
        file << player.getOutOfJailCards << endl;
        // Keep the indices of the properties you own.
        for (int i = 0; i < BOARD_PERIMETER; ++i)
        {
            if (player.properties[i])
            {
                file << i << " ";
            }
        }
        file << endl;
        file.close();
    }
}

// Check if there is a master save file.
bool doesSaveExist()
{
    ifstream file("savegame.txt");
    return file.is_open(); // Returns true if the file could be opened (exists).
}

// Get the names of the players from the master save file.
SavedPlayerNames getSavedPlayerNames()
{
    SavedPlayerNames names;
    ifstream file("savegame.txt");
    if (file.is_open())
    {
        getline(file, names.p1_name);
        getline(file, names.p2_name);
    }
    return names;
}

// Load the data of a player. If their file does not exist, create a new player.
Player loadPlayer(string name)
{
    ifstream file(name + ".txt");
    if (file.is_open())
    {
        Player loadedPlayer;
        file >> loadedPlayer.name;
        file >> loadedPlayer.money;
        file >> loadedPlayer.position;
        file >> loadedPlayer.getOutOfJailCards;

        // Clean the properties before loading the saved ones.
        for (int i = 0; i < BOARD_PERIMETER; ++i)
            loadedPlayer.properties[i] = false;

        // Read the property indices and assign them.
        int propIndex;
        while (file >> propIndex)
        {
            if (propIndex >= 0 && propIndex < BOARD_PERIMETER)
            {
                loadedPlayer.properties[propIndex] = true;
            }
        }
        loadedPlayer.turnsInJail = 0;
        loadedPlayer.isBankrupt = false;
        file.close();
        cout << "Data from " << loadedPlayer.name << " loaded." << endl;
        return loadedPlayer;
    }
    cout << "No data found for " << name << ". Creating new player." << endl;
    return createNewPlayer(name);
}

// Save the complete game.
void saveGame(GameState gs)
{
    cout << "Saving game..." << endl;
    // 1. Save the data of each player in their respective file.
    savePlayer(gs.players[0]);
    savePlayer(gs.players[1]);
    // 2. Create/overwrite the control file with the session names.
    ofstream file("savegame.txt");
    if (file.is_open())
    {
        file << gs.players[0].name << endl;
        file << gs.players[1].name << endl;
        file.close();
    }
    cout << "Game saved successfully." << endl;
}

// Delete the files from the previous game.
void deleteOldSaveFiles()
{
    if (doesSaveExist())
    {
        cout << "Removing data from the previous game..." << endl;
        SavedPlayerNames names = getSavedPlayerNames();
        // Delete the files of each player.
        remove((names.p1_name + ".txt").c_str());
        remove((names.p2_name + ".txt").c_str());
        // Delete the control file.
        remove("savegame.txt");
    }
}