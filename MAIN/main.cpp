#include <iostream>
#include "../src/Board.h"
#include "../src/Player.h"
using namespace std;

int main() {
    cout << "Iniciando juego...\n";
    Box board[SIZE][SIZE];
    loadBoard(board);
    cout << "Tablero cargado.\n";
    showBoard(board);
    cout << "Tablero mostrado.\n";
    return 0;
}
