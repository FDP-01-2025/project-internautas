#ifndef BOARD_H
#define BOARD_H

#include "Player.h"

// ===================================================================
// STATEMENTS OF FUNCTIONS OF THE BOARD
// ===================================================================

// Draw the board in the console, showing the position of the players.
void printBoard(Player p1, Player p2);

// Calculates the player's new position, grants the bonus if they pass through Exit, and returns their updated status.
Player movePlayer(Player player, int roll);

#endif // BOARD_H