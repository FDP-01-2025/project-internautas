#include <iostream>
#include <string>
#include <limits> // Necesario para la validación de entrada
#include "../src/Constants.h"
#include "../src/Player.h"
#include "../src/GameIO.h"
#include "../src/Board.h"
#include "../src/GameActions.h"

using namespace std;

// ===================================================================
// ARCHIVO PRINCIPAL DEL JUEGO (PUNTO DE ENTRADA)
// ===================================================================

// --- Prototipos de funciones auxiliares del main ---
GameState checkGameOver(GameState gs);
void showWinner(GameState gs);

// Función de utilidad para obtener una entrada numérica válida del usuario.
// Garantiza que la entrada es un número y está en el rango [min, max].
int getValidInput(int min, int max)
{
    int choice;
    do
    {
        cout << "Elige una opcion: ";
        cin >> choice;

        if (cin.fail())
        { // Si la entrada no es un número
            cout << "Error: Por favor, ingresa solo numeros." << endl;
            cin.clear();                                         // Limpia el flag de error de cin.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada incorrecta del buffer.
            choice = -1;                                         // Asigna un valor inválido para que el bucle continúe.
        }
        else if (choice < min || choice > max)
        { // Si el número está fuera de rango
            cout << "Error: Opcion fuera de rango. Intenta de nuevo." << endl;
        }
    } while (choice < min || choice > max);
    return choice;
}

// --- Función Principal ---
int main()
{
    initializeRandom();
    GameState gameState;

    cout << "========================================" << endl;
    cout << "      BIENVENIDO A MINIMOPOLY" << endl;
    cout << "========================================" << endl;

    // Lógica de inicio: Comprueba si hay una partida guardada.
    if (doesSaveExist())
    {
        SavedPlayerNames names = getSavedPlayerNames();
        cout << "\nSe ha encontrado una partida guardada:" << endl;
        cout << " -> " << names.p1_name << " vs " << names.p2_name << endl;

        cout << "\nQue deseas hacer?" << endl;
        cout << "1. Cargar partida" << endl;
        cout << "2. Empezar una nueva partida (se borrara la anterior)" << endl;
        int choice = getValidInput(1, 2);

        if (choice == 1)
        { // Cargar partida
            cout << "\nCargando partida guardada..." << endl;
            gameState.players[0] = loadPlayer(names.p1_name);
            gameState.players[1] = loadPlayer(names.p2_name);
        }
        else
        { // Empezar de cero
            deleteOldSaveFiles();
            cout << "\nIniciando nueva partida..." << endl;
            string name1, name2;
            cout << "Nombre del Jugador 1: ";
            cin >> name1;
            cout << "Nombre del Jugador 2: ";
            cin >> name2;
            gameState.players[0] = createNewPlayer(name1);
            gameState.players[1] = createNewPlayer(name2);
        }
    }
    else
    { // No hay partida guardada
        cout << "\nNo se encontraron partidas guardadas." << endl;
        cout << "Iniciando nueva partida..." << endl;
        string name1, name2;
        cout << "Nombre del Jugador 1: ";
        cin >> name1;
        cout << "Nombre del Jugador 2: ";
        cin >> name2;
        gameState.players[0] = createNewPlayer(name1);
        gameState.players[1] = createNewPlayer(name2);
    }

    // Inicialización del estado del juego
    gameState.currentPlayerIndex = 0;
    gameState.isGameOver = false;

    // --- Bucle Principal del Juego ---
    while (!gameState.isGameOver)
    {
        Player currentPlayer = gameState.players[gameState.currentPlayerIndex];
        cout << "\n==================== TURNO DE " << currentPlayer.name << " ====================" << endl;
        printBoard(gameState.players[0], gameState.players[1]);

        // Menú de acciones del turno
        bool endTurn = false;
        while (!endTurn)
        {
            cout << "\n--- MENU ---" << endl;
            cout << "1. Lanzar dado" << endl;
            cout << "2. Ver mi dinero y propiedades" << endl;
            cout << "3. Guardar y Salir" << endl;
            cout << "4. Salir sin guardar" << endl;
            int choice = getValidInput(1, 4);

            if (choice == 1)
            {
                endTurn = true; // Termina el bucle del menú para proceder con el turno.
            }
            else if (choice == 2)
            {
                printPlayerStatus(currentPlayer);
                cout << "Propiedades:" << endl;
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
                    cout << " - (Ninguna)" << endl;
                }
            }
            else if (choice == 3)
            {
                saveGame(gameState);
                return 0; // Termina el programa.
            }
            else if (choice == 4)
            {
                cout << "Saliendo sin guardar. ¡Adios!" << endl;
                return 0; // Termina el programa.
            }
        }

        // Lógica de acción del turno
        if (currentPlayer.turnsInJail > 0)
        {
            gameState = handleJailTurn(gameState);
        }
        else
        {
            currentPlayer = movePlayer(currentPlayer, rollDice());
            gameState.players[gameState.currentPlayerIndex] = currentPlayer;
            char tileType = BOARD_LAYOUT[currentPlayer.position];
            // Llama a la función correspondiente según la casilla.
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
                cout << "Estas de visita en la carcel." << endl;
            }
            else if (tileType == T_PARKING)
            {
                cout << "Estacionamiento libre. No pasa nada." << endl;
            }
            else if (tileType == T_START)
            {
                cout << "Has caido en la Salida." << endl;
            }
        }

        // Comprueba si el juego ha terminado después del turno.
        gameState = checkGameOver(gameState);
        // Si no ha terminado, pasa al siguiente jugador.
        if (!gameState.isGameOver)
        {
            gameState.currentPlayerIndex = (gameState.currentPlayerIndex + 1) % NUM_PLAYERS;
        }
    }

    // Muestra al ganador y termina el juego.
    showWinner(gameState);
    return 0;
}

// --- Implementación de Funciones Auxiliares ---

// Comprueba las condiciones de fin de juego (bancarrota o todas las propiedades compradas).
GameState checkGameOver(GameState gs)
{
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        if (gs.players[i].money < BANKRUPTCY_LIMIT)
        {
            gs.players[i].isBankrupt = true;
            gs.isGameOver = true;
            cout << "!" << gs.players[i].name << " ha entrado en bancarrota!" << endl;
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
        cout << "!Todas las propiedades han sido compradas!" << endl;
    }
    return gs;
}

// Determina y anuncia al ganador según las reglas.
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
        { // En caso de empate en propiedades, gana el que tenga más dinero.
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
    cout << "\n==================== FIN DEL JUEGO ====================" << endl;
    cout << "!!! El ganador es " << winner.name << " !!!" << endl;
    cout << "=======================================================" << endl;
}

/*g++ MAIN/main.cpp src/Player.cpp src/Board.cpp src/GameIO.cpp src/GameActions.cpp -o minimopoly -Isrc*/