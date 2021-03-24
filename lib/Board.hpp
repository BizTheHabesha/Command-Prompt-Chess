#pragma once
#include "Square.hpp"

/*
    Pieces will be encoded by integer. 
    0 - Pawn
    1 - Rook
    2 - Knight
    3 - Bishop
    4 - Queen
    5 - King

    Color will be encoded by boolean.
    True - white
    False - black
*/

class Board{
private:
    enum GAME_STATE{norm = 1, check = 2, checkmate = 0};
    Square square_arr[8][8] = {}; // internal structure
    bool movePawn(Square*, Square*);
    bool moveRook(Square*, Square*);
    bool moveKnight(Square*, Square*);
    bool moveBishop(Square*, Square*);
    bool moveQueen(Square*, Square*);
    bool moveKing(Square*, Square*);
public:
    Board(); // populate by default
    bool drawBoard();
    bool saveGame();
    bool loadGame();
    bool movePiece(Square*, Square*); // use the int to preform the correct method call. check for off board inputs
    void populate();
    COLOR playGame(); //return the color that won.
};