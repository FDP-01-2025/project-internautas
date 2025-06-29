#include "GameActions.h"
#include "Constants.h"
#include <iostream>
#include <cstdlib> // Necessary for rand() y srand()
#include <ctime>   // Necessary for time()
#include <cctype>  // Necessary for tolower()
#include <limits>  // Necessary for numeric_limits

using namespace std;

// ===================================================================
// IMPLEMENTATION OF THE MAIN ACTIONS OF THE GAME
// ===================================================================

// Initialize the random number generator using the current time as the seed.
void initializeRandom()
{
    srand(time(nullptr));
}

// Returns a random number between 1 and 6.
int rollDice()
{
    return (rand() % 6) + 1;
}

// Looks for the owner of a property.
int getPropertyOwnerIndex(GameState gs, int propertyPosition)
{
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        if (gs.players[i].properties[propertyPosition])
        {
            return i;
        }
    }
    return -1;
}

// Manages the logic when a player lands on a property.
GameState handleProperty(GameState gs)
{
    Player currentPlayer = gs.players[gs.currentPlayerIndex];
    int propertyPos = currentPlayer.position;
    int ownerIndex = getPropertyOwnerIndex(gs, propertyPos);

    if (ownerIndex == -1)
    { // If it has no owner
        cout << "The property '" << PROPERTY_NAMES[propertyPos] << "' is available." << endl;
        cout << "Costs $" << PROPERTY_PRICES[propertyPos] << ". Your current cash: $" << currentPlayer.money << endl;
        if (currentPlayer.money >= PROPERTY_PRICES[propertyPos])
        {
            char choice;
            // Input validation loop.
            do
            {
                cout << "Would you like to buy it? (y/n): ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = tolower(choice);
                if (choice != 'y' && choice != 'n')
                {
                    cout << "Error: Invalid option." << endl;
                }
            } while (choice != 'y' && choice != 'n');

            if (choice == 'y')
            { // If bought
                currentPlayer.money -= PROPERTY_PRICES[propertyPos];
                currentPlayer.properties[propertyPos] = true;
                cout << currentPlayer.name << " has bought '" << PROPERTY_NAMES[propertyPos] << "'." << endl;
            }
        }
        else
        {
            cout << "You don't have enough money to buy the property." << endl;
        }
    }
    else if (ownerIndex != gs.currentPlayerIndex)
    { // If it's from another player
        Player owner = gs.players[ownerIndex];
        int rent = PROPERTY_RENTS[propertyPos];
        cout << "This property belongs to " << owner.name << ". You must pay a rent of $" << rent << "." << endl;
        currentPlayer.money -= rent;
        owner.money += rent;
        gs.players[ownerIndex] = owner;
    }
    else
    { // If it is from the player himself/herself
        cout << "You have landed on your own property. !How lucky!" << endl;
    }
    gs.players[gs.currentPlayerIndex] = currentPlayer;
    return gs;
}

// Manages the logic of the special cards.
GameState handleSpecialCard(GameState gs)
{
    Player currentPlayer = gs.players[gs.currentPlayerIndex];
    int effect = rand() % 3; // Random effect
    cout << "You have fallen into a Special Card square.!" << endl;
    if (effect == 0)
    {
        cout << "!You have found a treasure! You win $100." << endl;
        currentPlayer.money += 100;
    }
    else if (effect == 1)
    {
        cout << "Pay a fine for speeding. You lose $50." << endl;
        currentPlayer.money -= 50;
    }
    else
    {
        cout << "!You have obtained a card to 'Get Out of Jail.'!" << endl;
        currentPlayer.getOutOfJailCards++;
    }
    gs.players[gs.currentPlayerIndex] = currentPlayer;
    return gs;
}

// Sends player to jail.
GameState handleGoToJail(GameState gs)
{
    Player currentPlayer = gs.players[gs.currentPlayerIndex];
    cout << "!Straight to jail! You do not go through the exit and you do not charge." << endl;
    currentPlayer.position = JAIL_POSITION;
    currentPlayer.turnsInJail = JAIL_TURNS_TO_SKIP + 1;
    gs.players[gs.currentPlayerIndex] = currentPlayer;
    return gs;
}

// Manages the turn of a player who is in jail.
GameState handleJailTurn(GameState gs)
{
    Player currentPlayer = gs.players[gs.currentPlayerIndex];
    cout << currentPlayer.name << " is in jail." << endl;
    if (currentPlayer.getOutOfJailCards > 0)
    {
        char choice;
        do
        {
            cout << "You have a card to get out of jail. Do you want to use it? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = tolower(choice);
            if (choice != 'y' && choice != 'n')
                cout << "Error: Invalid option." << endl;
        } while (choice != 'y' && choice != 'n');

        if (choice == 'y')
        {
            currentPlayer.getOutOfJailCards--;
            currentPlayer.turnsInJail = 0;
            cout << "You have used the card. You are free!" << endl;
        }
    }
    if (currentPlayer.turnsInJail > 0)
    {
        currentPlayer.turnsInJail--;
        if (currentPlayer.turnsInJail > 0)
        {
            cout << "You stay in jail. You have left " << currentPlayer.turnsInJail << " turns to wait." << endl;
        }
        else
        {
            cout << "You have served your sentence. In the next turn, you will be able to move." << endl;
        }
    }
    gs.players[gs.currentPlayerIndex] = currentPlayer;
    return gs;
}

// Manages the payment of taxes.
GameState handleTax(GameState gs)
{
    Player currentPlayer = gs.players[gs.currentPlayerIndex];
    cout << "Income tax. You must pay $" << TAX_AMOUNT << endl;
    currentPlayer.money -= TAX_AMOUNT;
    gs.players[gs.currentPlayerIndex] = currentPlayer;
    return gs;
}