#pragma once
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

using namespace std;

enum PIECE{EMPTY = -1, PAWN = 0, ROOK = 1, KNIGHT = 2, BISHOP = 3, QUEEN = 4, KING = 5};
enum COLOR{NONE = -1, WHITE = true, BLACK = false}; // color of the squares and pieces

class Square{
private:
    PIECE piece;
    COLOR color;
    int x;
    int y;
public:
    void setX(int);
    int getX();
    void setY(int);
    int getY();
    void setColor(COLOR);
    COLOR getColor();
    void setPiece(PIECE);
    PIECE getPiece();
};