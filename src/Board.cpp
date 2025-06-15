#include "board.h"
#include <iostream>
#include <string>

using namespace std;


//1) Asignar datos a UNA casilla del id 0‑39
void asignBox(Box &box, int id)
{
    // Datos del Monopoly clásico (MODIFICAR SEGUN SEA NECESARIO)
    static const char *names[TILES] = {
        "GO", "Mediterranean Ave", "Community Chest", "Baltic Ave", "Income Tax",
        "Reading RR", "Oriental Ave", "Chance", "Vermont Ave", "Connecticut Ave",
        "Jail / Just Visiting", "St. Charles Pl.", "Electric Company", "States Ave", "Virginia Ave",
        "Pennsylvania RR", "St. James Pl.", "Community Chest", "Tennessee Ave", "New York Ave",
        "Free Parking", "Kentucky Ave", "Chance", "Indiana Ave", "Illinois Ave",
        "B&O RR", "Atlantic Ave", "Ventnor Ave", "Water Works", "Marvin Gardens",
        "Go To Jail", "Pacific Ave", "North Carolina Ave", "Community Chest", "Pennsylvania Ave",
        "Short Line RR", "Chance", "Park Place", "Luxury Tax", "Boardwalk"
    };

    static const int types[TILES] = {
        TYPE_GO, TYPE_PROPERTY, TYPE_CHANCE, TYPE_PROPERTY, TYPE_TAX,
        TYPE_RAILROAD, TYPE_PROPERTY, TYPE_CHANCE, TYPE_PROPERTY, TYPE_PROPERTY,
        TYPE_JAIL, TYPE_PROPERTY, TYPE_UTILITY, TYPE_PROPERTY, TYPE_PROPERTY,
        TYPE_RAILROAD, TYPE_PROPERTY, TYPE_CHANCE, TYPE_PROPERTY, TYPE_PROPERTY,
        TYPE_PARKING, TYPE_PROPERTY, TYPE_CHANCE, TYPE_PROPERTY, TYPE_PROPERTY,
        TYPE_RAILROAD, TYPE_PROPERTY, TYPE_PROPERTY, TYPE_UTILITY, TYPE_PROPERTY,
        TYPE_GO_TO_JAIL, TYPE_PROPERTY, TYPE_PROPERTY, TYPE_CHANCE, TYPE_PROPERTY,
        TYPE_RAILROAD, TYPE_CHANCE, TYPE_PROPERTY, TYPE_TAX, TYPE_PROPERTY
    };

    static const int prices[TILES] = {
        0, 60, 0, 60, 0,
        200, 100, 0, 100, 120,
        0, 140, 150, 140, 160,
        200, 180, 0, 180, 200,
        0, 220, 0, 220, 240,
        200, 260, 260, 150, 280,
        0, 300, 300, 0, 320,
        200, 0, 350, 0, 400
    };

    static const int rents[TILES] = {
        0, 2, 0, 4, 200,      // Income Tax: 200
        25, 6, 0, 6, 8,
        0, 10, 0, 10, 12,
        25, 14, 0, 14, 16,
        0, 18, 0, 18, 20,
        25, 22, 22, 0, 24,
        0, 26, 26, 0, 28,
        25, 0, 35, 100, 50   // Luxury Tax: 100
    };

    // ► Copiar al Box
    strcpy(box.Name, names[id]);
    box.Type   = types[id];
    box.Price  = prices[id];
    box.Rent   = rents[id];
    box.Owner  = -1;      // sin dueño al inicio
    box.Houses = 0;
    box.Hotel  = false;
}

//2) Cargar TODAS las casillas en el tablero
void loadBoard(Box board[SIZE][SIZE])
{
    // A) Inicializar tablero vacío
    for (int r = 0; r < SIZE; ++r)
        for (int c = 0; c < SIZE; ++c) {
            board[r][c].Type   = -1;     // -1 = interior / vacío
            board[r][c].Owner  = -1;
            board[r][c].Name[0]= '\0';
            board[r][c].Price  = 0;
            board[r][c].Rent   = 0;
            board[r][c].Houses = 0;
            board[r][c].Hotel  = false;
        }

    // B) Rellenar el borde siguiendo el sentido horario,
    //    empezando en la casilla 0 (GO) en la esquina (10,10)
    int id = 0;

    // ↓ fila inferior (derecha → izquierda)
    for (int col = SIZE - 1; col >= 0; --col)
        asignBox(board[SIZE - 1][col], id++);

    // ← columna izquierda (abajo → arriba, sin repetir esquina)
    for (int row = SIZE - 2; row >= 0; --row)
        asignBox(board[row][0], id++);

    // ↑ fila superior (izquierda → derecha, sin repetir esquina)
    for (int col = 1; col < SIZE; ++col)
        asignBox(board[0][col], id++);

    // → columna derecha (arriba → abajo, sin repetir esquinas)
    for (int row = 1; row < SIZE - 1; ++row)
        asignBox(board[row][SIZE - 1], id++);
}

//Helper: convertir tipo a símbolo para mostrar ―
char symbol(const Box &b)
{
    switch (b.Type) {
        case TYPE_GO:         return 'G';
        case TYPE_PROPERTY:   return 'P';
        case TYPE_TAX:        return '$';
        case TYPE_JAIL:       return 'J';
        case TYPE_CHANCE:     return '?';
        case TYPE_GO_TO_JAIL: return 'X';
        case TYPE_UTILITY:    return 'U';
        case TYPE_RAILROAD:   return 'R';
        case TYPE_PARKING:    return 'F';
        default:              return ' ';   // interior
    }
}

//3) Imprimir tablero en consola
void showBoard(Box board[SIZE][SIZE])
{
    cout << '\n';
    for (int r = 0; r < SIZE; ++r) {
        for (int c = 0; c < SIZE; ++c) {
            cout << '[' << symbol(board[r][c]) << ']';
        }
        cout << '\n';
    }
}

