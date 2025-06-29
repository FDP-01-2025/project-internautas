#include <iostream>
#include <string>
#include <limits>  // Necessary for input validation
#include <cstdlib> // Necessary for system()
#include "../src/Constants.h"
#include "../src/Player.h"
#include "../src/GameIO.h"
#include "../src/Board.h"
#include "../src/GameActions.h"

// It tells windows.h not to include unnecessary APIs that cause the conflict.
#define WIN32_LEAN_AND_MEAN

// It is included only in Windows for console functions.
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// --- Prototypes of auxiliary functions of the main ---
GameState checkGameOver(GameState gs);
void showWinner(GameState gs);
int getValidInput(int min, int max);

// --- Main Function ---
int main()
{
// --- Initial Console Setup ---
#ifdef _WIN32
    // Prepare the console to display Unicode symbols (UTF-8)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    initializeRandom();
    GameState gameState;

    cout << "========================================" << endl;
    cout << "      WELCOME TO MINIMONOPOLY 🏁" << endl; // Emoji added
    cout << "========================================" << endl;

    // Startup logic: Check if there is a saved game.
    if (doesSaveExist())
    {
        SavedPlayerNames names = getSavedPlayerNames();
        cout << "\nA saved game has been found:" << endl;
        cout << " -> " << names.p1_name << " vs " << names.p2_name << endl;

        cout << "\nWhat would you like to do?" << endl;
        cout << "1. Load game 💾" << endl;                                     // Emoji added
        cout << "2. Start a new game (the previous one will be deleted) 🚮" << endl; // Emoji added
        int choice = getValidInput(1, 2);

        if (choice == 1)
        { // Load game
            cout << "\nLoading saved game..." << endl;
             Sleep(1500);
            gameState.players[0] = loadPlayer(names.p1_name);
            gameState.players[1] = loadPlayer(names.p2_name);
        }
        else
        { // Start from zero
            deleteOldSaveFiles();
            cout << "\nStarting new game..." << endl;
             Sleep(1500);
            string name1, name2;
            cout << "Name of Player 1: ";
            cin >> name1;
            cout << "Name of Player 2: ";
            cin >> name2;
            gameState.players[0] = createNewPlayer(name1);
            gameState.players[1] = createNewPlayer(name2);
        }
    }
    else
    { // There is no saved game
        cout << "\nNo saved game was found." << endl;
        cout << "Starting a new game..." << endl;
         Sleep(2000);
        string name1, name2;
        cout << "Name of Player 1: ";
        cin >> name1;
        cout << "Name of Player 2: ";
        cin >> name2;
        gameState.players[0] = createNewPlayer(name1);
        gameState.players[1] = createNewPlayer(name2);
    }

    // Initialization of the game state
    gameState.currentPlayerIndex = 0;
    gameState.isGameOver = false;

    // --- Main Loop of the Game ---
    while (!gameState.isGameOver)
    {
        Player currentPlayer = gameState.players[gameState.currentPlayerIndex];
        Player otherPlayer = gameState.players[(gameState.currentPlayerIndex + 1) % NUM_PLAYERS];

        cout << "\n==================== " << currentPlayer.name << "'s TURN ====================" << endl;
        printBoard(currentPlayer, otherPlayer);

        // Shift action menu
        bool endTurn = false;
        while (!endTurn)
        {
            cout << "\n--- MENU ---" << endl;
            cout << "1. Roll the dice 🎲" << endl;                 // Emoji added
            cout << "2. View my money and properties 💰" << endl; // Emoji added
            cout << "3. Save and exit" << endl;
            cout << "4. Exit without saving" << endl;
            int choice = getValidInput(1, 4);

            if (choice == 1)
            {
                cout<<"Rolling dices...\n";
                 Sleep(1000);
                endTurn = true;
            }
            else if (choice == 2)
            {
                 Sleep(600);
                printPlayerStatus(currentPlayer);
                cout << "Properties:" << endl;
                int propCount = countPlayerProperties(currentPlayer);
                if (propCount > 0)
                {
                    for (int i = 0; i < BOARD_PERIMETER; ++i)
                    {
                        if (currentPlayer.properties[i])
                        {
                            cout << " - " << PROPERTY_NAMES[i] << endl;
                        }
                    }
                }
                else
                {
                    cout << " - (None)" << endl;
                }
            }
            else if (choice == 3)
            {
                cout<<"Saving game...\n";
                 Sleep(2000);
                saveGame(gameState);
                return 0;
            }
            else if (choice == 4)
            {
                cout << "Exiting without saving. ¡Goodbye!" << endl;
                 Sleep(500);
                return 0;
            }
        }

        // Action logic of the turn
        if (currentPlayer.turnsInJail > 0)
        {
            gameState = handleJailTurn(gameState);
        }
        else
        {
            gameState.players[gameState.currentPlayerIndex] = movePlayer(currentPlayer, rollDice());
            currentPlayer = gameState.players[gameState.currentPlayerIndex];
            char tileType = BOARD_LAYOUT[currentPlayer.position];

            if (tileType == T_PROPERTY)
            {
                gameState = handleProperty(gameState);
            }
            else if (tileType == T_CARD)
            {
                gameState = handleSpecialCard(gameState);
            }
            else if (tileType == T_TAX)
            {
                gameState = handleTax(gameState);
            }
            else if (tileType == T_GO_TO_JAIL)
            {
                gameState = handleGoToJail(gameState);
            }
            else if (tileType == T_JAIL)
            {
                cout << "You are visiting in jail." << endl;
            }
            else if (tileType == T_PARKING)
            {
                cout << "Free station. Nothing happens." << endl;
            }
            else if (tileType == T_START)
            { /* The action is already being handled in movePlayer. */
            }
        }

        gameState = checkGameOver(gameState);

        if (!gameState.isGameOver)
        {
            gameState.currentPlayerIndex = (gameState.currentPlayerIndex + 1) % NUM_PLAYERS;
        }
    }

    showWinner(gameState);
    return 0;
}

// --- Implementation of Auxiliary Functions ---

int getValidInput(int min, int max)
{
    int choice;
    do
    {
        cout << "Choose an option: ";
        cin >> choice;
        if (cin.fail())
        {
            cout << "Error: Please insert only numbers." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }
        else if (choice < min || choice > max)
        {
            cout << "Error: Option out of range. Try again." << endl;
        }
    } while (choice < min || choice > max);
    return choice;
}

GameState checkGameOver(GameState gs)
{
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        if (gs.players[i].money < BANKRUPTCY_LIMIT)
        {
            gs.players[i].isBankrupt = true;
            gs.isGameOver = true;
            cout << "!" << gs.players[i].name << " has gone bankrupt! 📉" << endl; // Emoji added
            return gs;
        }
    }
    int propertiesOwned = 0;
    for (int i = 0; i < BOARD_PERIMETER; ++i)
    {
        if (BOARD_LAYOUT[i] == T_PROPERTY && getPropertyOwnerIndex(gs, i) != -1)
        {
            propertiesOwned++;
        }
    }
    if (propertiesOwned >= MAX_PROPERTIES)
    {
        gs.isGameOver = true;
        cout << "!All the properties have been bought!" << endl;
    }
    return gs;
}

void showWinner(GameState gs)
{
    Player winner;
    if (gs.players[0].isBankrupt)
    {
        winner = gs.players[1];
    }
    else if (gs.players[1].isBankrupt)
    {
        winner = gs.players[0];
    }
    else
    {
        int propsP1 = countPlayerProperties(gs.players[0]);
        int propsP2 = countPlayerProperties(gs.players[1]);
        if (propsP1 > propsP2)
        {
            winner = gs.players[0];
        }
        else if (propsP2 > propsP1)
        {
            winner = gs.players[1];
        }
        else
        {
            if (gs.players[0].money > gs.players[1].money)
            {
                winner = gs.players[0];
            }
            else
            {
                winner = gs.players[1];
            }
        }
    }
    cout << "\n==================== GAME OVER ====================" << endl;
    cout << "!!! The winner is " << winner.name << " 🏆 !!!" << endl; // Emoji added
    cout << "=======================================================" << endl;
}