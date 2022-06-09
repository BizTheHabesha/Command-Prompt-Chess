#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <vector>
#include "Board.hpp" 
#include "Square.hpp"
#include "functions.hpp"

using namespace std;

int linkFile(string location){
    ifstream save;
    string temp;
    save.open(location);
    if(!save.is_open()) cout << "Invalid location.\n";
    getline(save, temp, '\n');
    save.close();
    if(temp != "Command-Prompt-Chess-Save-File") cout << "Invalid save game file.\n";
    return 0;
}
int editConfig(int setting){
    fstream config;
    config.open("../config/config.chess");
    try{
        if(!config.is_open()) throw runtime_error(string("fstream: failed to open \"../config/config.chess\"\nYour game may be incorrectly initialized!"));
    }catch(runtime_error& fto){
        cerr << "Error: -" << fto.what() << endl;
        return -1;
    }catch(exception& e){
        cerr << "Error: -Undefined Throw: -" << e.what() << "\nPlease submit a screenshot to github.\n";
        return -2;
    }catch(...){
        cerr << "Error: -Unexcpeted Throw: -catch_all: -aborting...\n";
        abort();
    }
    // edit the config
    config.close();
    return 0;
}
// link both the save and config files.

void Square::setX(int this_){
    x = this_;
}
void Square::setY(int this_){
    y = this_;
}
void Square::setColor(COLOR this_){
    color = this_;
}
void Square::setPiece(PIECE this_){
    piece = this_;
}
int Square::getX(){
    return x;
}
int Square::getY(){
    return y;
}
COLOR Square::getColor(){
    return color;
}
PIECE Square::getPiece(){
    return piece;
}
char Square::getChar(COLOR sq_color){
    char temp;
    if(piece == EMPTY){
        if(sq_color == BLACK) return ' ';
        else return '.';
    }
    else if(color == WHITE) return char(piece)-32;
    else return char(piece);
}

Board::Board(){
    populate();
}
bool Board::movePawn(Square* src, Square* dest){
    if(src->getColor() == WHITE){/*Check the piece is white*/
        if((dest->getX() == src->getX()) /* check that the move is still in the same column */
        && ((dest->getY() == src->getY()+1) || ((dest->getY() == src->getY()+2) && (src->getY() == 1)))/*AND check if the move IS one square up OR if the move IS two squares up AND the pawn
        IS at its starting position (row B)*/
        && (dest->getPiece() == EMPTY)){/*AND check the destination IS empty (pawns cannot take while moving forward*/
            return true;
        }
        else if((dest->getY() == src->getY()+1) /* Check that the move IS one square up*/
        && (dest->getX() == src->getX()+1 || dest->getX() == src->getX()-1)/* AND check if the destination is one square to the right OR the left*/
        && (dest->getPiece() != EMPTY))/*AND check that the destination piece IS NOT empty (pawns can only move diagonally if they are taking a piece.*/{
            return true;
        }
    }
    /* The same principles apply below, but inverted for black pieces*/
    else if(src->getColor() == BLACK){
        if((dest->getX() == src->getX())
        && ((dest->getY() == src->getY()-1) || ((dest->getY() == src->getY()-2) && (src->getY() == 6)))
        && (dest->getPiece() == EMPTY)){
            return true;
        }
        else if((dest->getY() == src->getY()-1)
        && (dest->getPiece() != EMPTY)
        && (dest->getX() == src->getX()+1 || dest->getX() == src->getX()-1)){
            return true;
        }
    }
    else return false;
}
bool Board::moveRook(Square* src, Square* dest){
    /* Check every square in a vertical line*/
    int xdist = src->getX()-dest->getX();/* get the distance*/
    int ydist = src->getY()-dest->getY();

    if(xdist != 0 && ydist == 0 && xdist > 0){
        for(int x = src->getX()-1; x < dest->getX(); x--){
            if(square_arr[x][src->getY()].getPiece() != EMPTY) return false;
        }
    }
    else if(xdist != 0 && ydist == 0){
        for(int x = src->getX()+1; x < dest->getX(); x++){
            if(square_arr[x][src->getY()].getPiece() != EMPTY) return false;
        }
    }
    else if(ydist != 0 && xdist == 0 && ydist > 0){
        for(int y = src->getY()-1; y < dest->getY(); y--){
            if(square_arr[src->getX()][y].getPiece() != EMPTY) return false;
        }
    }else if(ydist != 0 && xdist == 0){
        for(int y = src->getY()+1; y < dest->getY(); y++){
            if(square_arr[src->getX()][y].getPiece() != EMPTY) return false;
        }
    }
    else return false;
    return true;
}
bool Board::moveKnight(Square* src, Square* dest){
    if((dest->getX() == src->getX()+2 || dest->getX() == src->getX()-2) && (dest->getY() == src->getY()+1 || dest->getY() == src->getY()-1)){
        return true;
    }
    else if((dest->getX() == src->getX()+1 || dest->getX() == src->getX()-1) && (dest->getY() == src->getY()+2 || dest->getY() == src->getY()-2)){
        return true;
    }
    else return false;
}
bool Board::moveBishop(Square* src, Square* dest){
    /* loop through squares between src and dest in a similar manner to the rook*/
}
bool Board::moveQueen(Square* src, Square* dest){
    /* combine rook and bishop checks */
}
bool Board::moveKing(Square* src, Square* dest){
    /* only moves one square */
}
bool Board::saveGame(){return true;} // W I P
bool Board::movePiece(COLOR this_, GAME_STATE curr_){
    // if user is check
    string s, msg;
    int xsrc, ysrc, xdest, ydest;
    bool success;
    while(1){
        system("CLS");
        drawBoard();
        cout << msg << endl;
        msg.clear();
        cout << " What piece would you like to move? [Ex: B7]\n Type 'C' to cancel\n  > ";
        getline(cin, s, '\n');
        if(s == "C") return false;
        if(s[0] > 72 || s[0] < 65) msg+=" That isn't a valid column.";
        else xsrc = s[0]-65;
        if(s[1] > 57 || s[1] < 49) msg+=" That isn't a valid row.";
        else ysrc = s[1]-49;
        if(!msg.empty()) continue;
        if(square_arr[xsrc][ysrc].getPiece() == EMPTY){
            msg+=" There is no piece there.";
            continue;
        }
        else if(square_arr[xsrc][ysrc].getColor() != this_){
            msg+=" That isn't your color.";
            continue;
        }
        
        cout << "Where would you like to move it? [Ex: B7]\n Type 'C' to cancel\n  > ";
        getline(cin, s, '\n');
        if(s == "C") return false;
        if(s[0] > 72 || s[0] < 65) msg+=" That isn't a valid row.";
        else xdest = s[0]-65;
        if(s[1] > 57 || s[1] < 49) msg+=" That isn't a valid column.";
        else ydest = s[1]-49;
        if(!msg.empty()) continue;
        if(square_arr[xdest][ydest].getColor() == this_ && square_arr[xdest][ydest].getPiece() != EMPTY){
            msg+=" You already have a piece there.";
            continue;
        }

        Square* src = &square_arr[xsrc][ysrc];
        Square* dest = &square_arr[xdest][ydest];

        PIECE srcpiece = src->getPiece();
        if(srcpiece == PAWN) success = movePawn(src, dest);
        else if(srcpiece == ROOK) success = moveRook(src, dest);
        else if(srcpiece == BISHOP) success = moveBishop(src, dest);
        else if(srcpiece == KNIGHT) success = moveKnight(src, dest);
        else if(srcpiece == QUEEN) success = moveQueen(src, dest);
        else if(srcpiece == KING) success = moveKing(src, dest);
        else{
            msg+=" An error occured while moving a piece.";
            continue;
        }
        if(success){
            dest->setPiece(src->getPiece());
            dest->setColor(src->getColor());
            src->setColor(NONE);
            src->setPiece(EMPTY);
            break;
        }
        else{
            msg+=" ";
            msg+=(src->getChar(this_));
            msg+=" cannot move there.";
        }
    }
    return true;
}
void Board::populate(){
    Square temp;
    temp.setPiece(EMPTY);
    temp.setColor(NONE);
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            if(y == 6 || y == 1){
                temp.setPiece(PAWN); //initialize pawns
                if(y == 6) temp.setColor(BLACK);
                else temp.setColor(WHITE);
            }
            else if(y == 0 || y == 7){// initialize everything else
                if(y==0) temp.setColor(WHITE);
                else if(y == 7)temp.setColor(BLACK);
                if(x == 0 || x == 7) temp.setPiece(ROOK);
                else if(x == 1 || x == 6) temp.setPiece(KNIGHT);
                else if(x == 2 || x == 5) temp.setPiece(BISHOP);
                else if(x == 3) temp.setPiece(QUEEN);
                else if(x == 4) temp.setPiece(KING);
            }

            temp.setX(x);
            temp.setY(y);
            square_arr[x][y] = temp;
            temp.setColor(NONE);
            temp.setPiece(EMPTY);
        }
    }
}
void Board::drawBoard(){
        // draw from array.
        cout << "   +________________________________________________+" << endl;
        // the chess board is made up of 24 lines of text, plus the caps and the letters on the bottom.
        for(int l = 0; l < 24; l++){
            // every third row begging from the second row is where a piece could be rendered. 
            if(l % 3 == 1 || l == 1){
                // even rows start on a black square, odd start on white.
                if(l % 2 == 0){
                    // convineitly, the lines containing pieces are also the lines containing numbers. 
                    cout << " " << (l+2)/3 << " |";
                    // iterate 4 times, each time 'i' is incremented by 2. The render looks the same after the first two squares.
                    for(int i = 0; i < 8; i+=2) cout << "   " <<square_arr[i][(l-1)/3].getChar(BLACK)<<"  ..."<<square_arr[i+1][(l-1)/3].getChar(WHITE)<<"..";
                    // cap the sides of the board
                    cout << "|" << endl;
                }
                // odd lines
                else{
        
                    cout << " " << (l+2)/3 << " |";
                    for(int i = 0; i < 8; i+=2) cout << "..." <<square_arr[i][(l-1)/3].getChar(WHITE)<<"..   "<<square_arr[i+1][(l-1)/3].getChar(BLACK)<<"  ";
                    cout << "|" << endl;
                }
            // for non chess lines, which are just the squares. again, we check for even and and odd.
            }else{
                if(l % 2 == 0) cout << "   |......      ......      ......      ......      |" << endl;
                else cout << "   |      ......      ......      ......      ......|" << endl;
            }
        }
        // cap the bottom.
        cout << "   +________________________________________________+" << endl;
        // letters for the user to make use of.
        cout << "       A     B     C     D     E     F    G     H   " << endl;
}
COLOR Board::playGame(){
    COLOR myTurn = WHITE;
    COLOR winner;
    GAME_STATE curr = NORM;
    string s;
    bool success;
    int turns = 1;
    while(1){
        system("CLS"); // clear
        drawBoard();
        s = (!myTurn) ? "White" : "Black";
        if(curr == CHECK) cout << s << " has you in check.\n";
        s = (myTurn) ? "White" : "Black";
        cout << " [Turn: " << turns << "] " << s <<"'s turn:    [1] Move    [2] Resign    [3] Save and Exit\n  > ";
        getline(cin, s, '\n');
        if(s == "1"){
            if(movePiece(myTurn, curr)){
                myTurn = COLOR(!myTurn);
                turns++;
            }
        }
        else if(s == "2"){
            system("CLS");
            cout << " This means your opponent wins, are you sure?\n [1] Yes, resign the match\n [2] No, take me back!\n > ";
            getline(cin, s, '\n');
            if(s == "2") continue;
            winner = COLOR(!myTurn);
            break;
        }
        else if(s == "3"){
            saveGame();
            cout << "Saved! Press enter to continue.\n";
            getline(cin, s, '\n');
            return myTurn;
        }
        // check for 'check' and 'checkmate' game states. maybe add to movePiece()?
    }
    if(winner == BLACK) cout << "Black won! ";
    else if(winner == WHITE) cout << "White won! ";
    else cout << "Stalemate. ";
    cout << "Press enter to continue.\n";
    getline(cin, s, '\n');
    return winner;
}