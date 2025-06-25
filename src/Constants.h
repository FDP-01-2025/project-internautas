#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using namespace std;

// ARCHIVO DE CONSTANTES GLOBALES
// Aquí se definen todos los valores fijos del juego (MODFICAR SEGUN AVANCEMOS EN EL JUEGO)

// Configuración General del Juego
const int NUM_PLAYERS = 2;          // Número de jugadores en la partida.
const int BOARD_PERIMETER = 20;     // Número total de casillas en el borde del tablero.
const int MAX_PROPERTIES = 11;      // Número de propiedades que activan el fin del juego.
const int STARTING_MONEY = 1500;    // Dinero inicial para cada jugador.
const int GO_BONUS = 150;           // Dinero recibido al pasar por la casilla de Salida.
const int JAIL_POSITION = 5;        // Posición en el array (índice 5) de la casilla de la Cárcel.
const int GO_TO_JAIL_POSITION = 15; // Posición de la casilla "Ir a la Cárcel".
const int BANKRUPTCY_LIMIT = -500;  // Límite de dinero negativo para declarar bancarrota.
const int TAX_AMOUNT = 100;         // Cantidad de impuesto a pagar.
const int JAIL_TURNS_TO_SKIP = 1;   // Turnos a esperar en la cárcel.

// Tipos de Casilla (representados por caracteres)
const char T_START = 'S';      // S: Salida / GO
const char T_PROPERTY = 'P';   // P: Propiedad
const char T_CARD = 'C';       // C: Carta Especial
const char T_TAX = 'I';        // I: Impuesto
const char T_JAIL = 'J';       // J: Cárcel (solo de visita)
const char T_GO_TO_JAIL = 'G'; // G: Ir a la Cárcel
const char T_PARKING = 'E';    // E: Estacionamiento Libre

// Disposición del Tablero
//  Array que define el tipo de cada una de las 20 casillas del perímetro.
const char BOARD_LAYOUT[BOARD_PERIMETER] = {
    T_START, T_PROPERTY, T_CARD, T_PROPERTY, T_TAX, T_GO_TO_JAIL,
    T_PROPERTY, T_PROPERTY, T_CARD, T_PROPERTY,
    T_PARKING, T_PROPERTY, T_TAX, T_PROPERTY, T_PROPERTY, T_JAIL,
    T_CARD, T_PROPERTY, T_PROPERTY, T_PROPERTY};

// Detalles de las Propiedades (usando arrays paralelos)
//  El índice de estos arrays corresponde a la posición en BOARD_LAYOUT.

// Nombres de las propiedades.
const string PROPERTY_NAMES[BOARD_PERIMETER] = {
    "", "Avenida Mediterraneo", "", "Avenida Baltica", "", "",
    "Plaza Oriente", "Avenida Vermont", "", "Avenida Connecticut",
    "", "Plaza San Carlos", "", "Avenida de los Estados", "Avenida Virginia", "",
    "", "Avenida San Jaime", "Avenida Tennessee", "Avenida Nueva York"};

// Precios de compra de cada propiedad.
const int PROPERTY_PRICES[BOARD_PERIMETER] = {
    0, 60, 0, 60, 0, 0,
    100, 100, 0, 120,
    0, 140, 0, 140, 160, 0,
    0, 180, 180, 200};

// Renta a pagar por cada propiedad.
const int PROPERTY_RENTS[BOARD_PERIMETER] = {
    0, 10, 0, 12, 0, 0,
    15, 15, 0, 18,
    0, 20, 0, 20, 22, 0,
    0, 25, 25, 30};

#endif