#include <iostream>
#include "../src/Board.h"
using namespace std;

int main() {
    cout << "Iniciando juego...\n";
    Box board[SIZE][SIZE];
    loadBoard(board);
    cout << "Tablero cargado.\n";
    showBoard(board);
    cout << "Tablero mostrado.\n";

    cin.get();
    return 0;
}
