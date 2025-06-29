#include "Board.h"
#include "Constants.h"
#include <iostream>

using namespace std;

// ===================================================================
// IMPLEMENTATION OF BOARD FUNCTIONS
// ===================================================================

// --- Auxiliary Structure ---
// This structure is created to return two values (row and column) 
// from the getCoords function without using pointers or references.
struct Coordinates
{
    int row;
    int col;
};

// --- Auxiliary Structure ---
// Convert the player's linear position (0-19) to grid coordinates.
// Returns a 'Coordinates' structure by value.
Coordinates getCoords(int pos)
{
    Coordinates coords; // An object is created to store the coordinates.
    if (pos >= 0 && pos <= 5)
    {
        coords.row = 0;
        coords.col = pos;
    }
    else if (pos >= 6 && pos <= 9)
    {
        coords.row = pos - 5;
        coords.col = 5;
    }
    else if (pos >= 10 && pos <= 15)
    {
        coords.row = 5;
        coords.col = 15 - pos;
    }
    else if (pos >= 16 && pos <= 19)
    {
        coords.row = 19 - pos;
        coords.col = 0;
    }
    return coords; // The complete structure is returned.
}

// Implementation of the improved function to print the board.
void printBoard(Player p1, Player p2)
{
    // 1. A 6x6 grid is created to visually represent the board.
    string grid[6][6];
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            grid[i][j] = "     "; // The interior is filled with spaces.
        }
    }

    // 2. The array of SYMBOLS is mapped to the grid coordinates.
    // Note: This is the simple implementation that uses emojis directly.
    // It does not try to correct the alignment, so it may appear "crooked" in the console.
    for (int i = 0; i <= 5; ++i)
        grid[0][i] = "[ " + BOARD_SYMBOLS[i] + " ]";
    for (int i = 0; i < 4; ++i)
        grid[1 + i][5] = "[ " + BOARD_SYMBOLS[6 + i] + " ]";
    for (int i = 0; i <= 5; ++i)
        grid[5][5 - i] = "[ " + BOARD_SYMBOLS[10 + i] + " ]";
    for (int i = 0; i < 4; ++i)
        grid[4 - i][0] = "[ " + BOARD_SYMBOLS[16 + i] + " ]";

    // 3. The position (row, column) of each player is obtained using the new function.
    Coordinates p1_coords = getCoords(p1.position);
    Coordinates p2_coords = getCoords(p2.position);

    // 4. The players' indicators ('1' and '2') are placed on the grid.
    // Values are accessed through the structure (ex: p1_coords.row).
    grid[p1_coords.row][p1_coords.col][1] = '1';
    grid[p2_coords.row][p2_coords.col][3] = '2';

    // 5. The final grid and the legend are printed.
    cout << "\n================== GAME BOARD ==================" << endl;
    for (int i = 0; i < 6; ++i)
    {
        string line = "";
        for (int j = 0; j < 6; ++j)
        {
            line += grid[i][j];
        }
        cout << line << endl
             << endl; // Double vertical space for better readability.
    }
    cout << "======================================================" << endl;
    cout << "Legend:  1-" << p1.name << "   2-" << p2.name << endl;
}

// The movePlayer function, now updated to be consistent.
Player movePlayer(Player player, int roll)
{
    int oldPosition = player.position;
    // The modulo operator (%) ensures that the position stays within the range of 0-19.
    player.position = (oldPosition + roll) % BOARD_PERIMETER;

    // If the new position is less than the previous one, it means that you have completed a lap.
    if (player.position < oldPosition)
    {
        cout << player.name << " has gone through the Exit and charges $" << GO_BONUS << "!" << endl;
        player.money += GO_BONUS;
    }

    // --- IMPORTANT CHANGE ---
    // Now the movement message uses BOARD_SYMBOLS to display the emoji,
    // instead of the BOARD_LAYOUT letter, to be consistent with the board.
    cout << player.name << " has landed a " << roll << " and moves to square " << player.position
         << " " << BOARD_SYMBOLS[player.position] << endl;

    // The full name of the property is displayed.
    if (PROPERTY_NAMES[player.position] != "")
    {
        cout << "Has landed in: " << PROPERTY_NAMES[player.position] << endl;
    }

    return player;
}