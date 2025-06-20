#include <iostream>
#include <string>

using namespace std;

const int SIZE = 6;
const int TILES = 20;

// Tipos de casilla
const int TYPE_GO = 0;
const int TYPE_PROPERTY = 1;
const int TYPE_CARD = 2;        
const int TYPE_TAX = 3;
const int TYPE_JAIL = 4;
const int TYPE_GOTOJAIL = 5;
const int TYPE_PARKING = 6;

// Casilla
struct Box
{
    string Name;
    int Type;
    int Price;
    int Rent;
    int Owner;
    int Houses;
    bool Hotel;
};

// Devuelve una casilla según su ID
Box asignBox(int id)
{
    Box box;

    string names[TILES] = {
        "GO", "Prop 1", "Card", "Prop 2", "Tax",
        "Prop 3", "Card", "Prop 4", "Prop 5", "Jail",
        "Parking", "Prop 6", "Tax", "Prop 7", "Prop 8",
        "Go to Jail", "Prop 9", "Card", "Prop 10", "Prop 11"};

    int types[TILES] = {
        TYPE_GO, TYPE_PROPERTY, TYPE_CARD, TYPE_PROPERTY, TYPE_TAX,
        TYPE_PROPERTY, TYPE_CARD, TYPE_PROPERTY, TYPE_PROPERTY, TYPE_JAIL,
        TYPE_PARKING, TYPE_PROPERTY, TYPE_TAX, TYPE_PROPERTY, TYPE_PROPERTY,
        TYPE_GOTOJAIL, TYPE_PROPERTY, TYPE_CARD, TYPE_PROPERTY, TYPE_PROPERTY};

    //Precio de cada casilla 
    int prices[TILES] = {
        0, 100, 0, 120, 0,
        150, 0, 180, 200, 0,
        0, 220, 0, 240, 260,
        0, 280, 0, 300, 320};

    // Renta de cada casilla
    int rents[TILES] = {
        0, 10, 0, 12, 50,
        14, 0, 16, 18, 0,
        0, 20, 50, 22, 24,
        0, 26, 0, 28, 30};

    box.Name = names[id];
    box.Type = types[id];
    box.Price = prices[id];
    box.Rent = rents[id];
    box.Owner = -1;
    box.Houses = 0;
    box.Hotel = false;

    return box;
}

// Carga el tablero con casillas en el borde
void loadBoard(Box board[SIZE][SIZE])
{
    // Inicializar vacíos
    for (int r = 0; r < SIZE; r++)
    {
        for (int c = 0; c < SIZE; c++)
        {
            board[r][c] = {"", -1, 0, 0, -1, 0, false};
        }
    }

    int id = 0;

    // Fila inferior (abajo → izquierda)
    for (int col = SIZE - 1; col >= 0 && id < TILES; col--)
    {
        board[SIZE - 1][col] = asignBox(id);
        id++;
    }

    // Columna izquierda (abajo → arriba, sin repetir esquina)
    for (int row = SIZE - 2; row >= 0 && id < TILES; row--)
    {
        board[row][0] = asignBox(id);
        id++;
    }

    // Fila superior (izquierda → derecha, sin repetir esquina)
    for (int col = 1; col < SIZE && id < TILES; col++)
    {
        board[0][col] = asignBox(id);
        id++;
    }

    // Columna derecha (arriba → abajo, sin repetir esquina)
    for (int row = 1; row < SIZE - 1 && id < TILES; row++)
    {
        board[row][SIZE - 1] = asignBox(id);
        id++;
    }
}

// Representar una casilla con un símbolo
char symbol(Box b)
{
    switch (b.Type)
    {
    case TYPE_GO:
        return 'S';
    case TYPE_PROPERTY:
        return 'P';
    case TYPE_CARD:
        return 'C';
    case TYPE_TAX:
        return '$';
    case TYPE_JAIL:
        return 'J';
    case TYPE_GOTOJAIL:
        return 'X';
    case TYPE_PARKING:
        return 'E';
    default:
        return ' ';
    }
}

// Mostrar tablero completo
void showBoard(Box board[SIZE][SIZE])
{
    cout << "\n=== TABLERO ===\n";
    for (int r = 0; r < SIZE; r++)
    {
        for (int c = 0; c < SIZE; c++)
        {
            cout << "[" << symbol(board[r][c]) << "]";
        }
        cout << "\n";
    }
    cout << "===============\n";
}

// Función principal PRUEBA PARA VER SI FUNCIONA
