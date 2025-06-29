#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using namespace std;

// ===================================================================
// GLOBAL CONSTANTS FILE
// Here all the fixed values of the game are defined for easy access and modification.
// ===================================================================

// --- 1. General Game Settings ---
// Here the economic rules and flow of the game are adjusted.
// ===================================================================
const int NUM_PLAYERS = 2;          // Number of players.
const int BOARD_PERIMETER = 20;     // Don't change: EThe board is designed for 20 squares.
const int MAX_PROPERTIES = 11;      // Don't change: The total number of properties in the board.
const int STARTING_MONEY = 1000;    // Starter money for each player.
const int GO_BONUS = 150;           // Bonus for passing the exit.
const int JAIL_POSITION = 5;        // Position in the array (index 5) of the Jail cell.
const int GO_TO_JAIL_POSITION = 15; // Position of the 'Go to Jail' square.
const int BANKRUPTCY_LIMIT = -200;  // Debt limit to declare bankruptcy.
const int TAX_AMOUNT = 150;         // Cost of the tax.
const int JAIL_TURNS_TO_SKIP = 1;   // Turns that a player must wait in jail.

// --- 2. Logical and Visual Configuration of the Dashboard ---
// Defines what is in each box.
// ===================================================================
// Internal logic (do not change). Simple characters are used for the game's logic.
const char T_START = 'S', T_PROPERTY = 'P', T_CARD = 'C', T_TAX = 'I', T_JAIL = 'J', T_GO_TO_JAIL = 'G', T_PARKING = 'E';

const char BOARD_LAYOUT[BOARD_PERIMETER] = {
    T_START, T_PROPERTY, T_CARD, T_PROPERTY, T_TAX, T_GO_TO_JAIL, T_PROPERTY, T_PROPERTY, T_CARD, T_PROPERTY,
    T_PARKING, T_PROPERTY, T_TAX, T_PROPERTY, T_PROPERTY, T_JAIL, T_CARD, T_PROPERTY, T_PROPERTY, T_PROPERTY};

// NEW: Visualization with symbols. This array is to show the board more appealing to the eye.
const string BOARD_SYMBOLS[BOARD_PERIMETER] = {
    "🏁", "🏠", "❔", "🏠", "💲", "🚓", "🏠", "🏠", "❔", "🏠",
    "🅿️", "🏠", "💲", "🏠", "🏠", "👮", "❔", "🏠", "🏠", "🏠"};

// --- 3. Properties Settings ---
// Parallel arrays: The index of each array corresponds to the same slot on the board.
// ===================================================================
// Names of the properties (Theme of Nicaragua).
const string PROPERTY_NAMES[BOARD_PERIMETER] = {
    "Exit", "Sandino Avenue", "Surprise Card", "Real Street", "Value Added Tax", "Go to jail",
    "Inter Plaza", "El Gueguense Roundabout", "Surprise Card", "Bolivar Avenue", "Free Parking",
    "Masaya Road", "Income Tax", "Camino de Oriente", "Galerias Santo Domingo",
    "Jail (visiting)", "Surprise card", "Puerto Salvador Allende", "Ruben Dario Theater", "Metrocentro"};

// Purchase prices of each property.
const int PROPERTY_PRICES[BOARD_PERIMETER] = {
    0, 60, 0, 60, 0, 0, 100, 100, 0, 120, 0, 140, 0, 140, 160, 0, 0, 180, 180, 200};

// Rent to be paid for each property.
const int PROPERTY_RENTS[BOARD_PERIMETER] = {
    0, 10, 0, 12, 0, 0, 15, 15, 0, 18, 0, 20, 0, 20, 22, 0, 0, 25, 25, 30};

// --- 4. NEW: Property Sets Configuration (Matrix) ---
// Defines the groups of properties and the bonus for completing them.
// ===================================================================
const int RENT_MULTIPLIER = 4; // The rent is multiplied by this value if you have the complete set.
const int NUM_PROPERTY_SETS = 4;
const int MAX_PROPS_PER_SET = 3;

// Matrix that defines the sets. Each row is a set. The numbers are the positions on the board.
// -1 is used to fill sets with less than 3 properties.
const int PROPERTY_SETS[NUM_PROPERTY_SETS][MAX_PROPS_PER_SET] = {
    {1, 3, -1},   // Set 1: Properties of $60
    {6, 7, 9},    // Set 2: Properties of $100-$120
    {11, 13, 14}, // Set 3: Properties of $140-$160
    {17, 18, 19}  // Set 4: Properties of $180-$200
};

#endif