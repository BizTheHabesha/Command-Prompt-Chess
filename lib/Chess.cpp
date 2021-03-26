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
string defaultSaveGameLocation = "../saves/initsave.chess";

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
    if(color == BLACK){
        switch(piece){
            case PAWN: return char(PAWN);
            case ROOK: return char(ROOK);
            case BISHOP: return char(BISHOP);
            case KNIGHT: return char(KNIGHT);
            case QUEEN: return char(QUEEN);
            case KING: return char(KING);
            case NONE: 
                if(sq_color == BLACK) return ' ';
                else return '.';
        };
    }else if(color == WHITE){
        switch(piece){
            case PAWN: return (char(PAWN)-32);
            case ROOK: return (char(ROOK)-32);
            case BISHOP: return (char(BISHOP)-32);
            case KNIGHT: return (char(KNIGHT)-32);
            case QUEEN: return (char(QUEEN)-32);
            case KING: return (char(KING)-32); 
            case NONE:
                if(sq_color == BLACK) return ' ';
                else return '.';
        };
    }else if(color == NONE && sq_color == BLACK) return ' ';
    else if(color == NONE && sq_color == WHITE) return '.';
    else{
        try{
            throw runtime_error(string(" broken logic..."));
        }catch(runtime_error& rte){
            cerr << rte.what() << endl;
            abort();
        }
    }
    return '?';
}

Board::Board(){
    populate();
}
bool Board::movePawn(Square* src, Square* dest){
    if(src->getColor() == WHITE){
        if((dest->getX() == src->getX()) /* check that the move is still in the same column */
        && ((dest->getY() == src->getY()+1) || ((dest->getY() == src->getY()+2) && (src->getY() == 1)))) /*AND check if the move is one square up OR if the move is two squares up and the pawn
        starts at it starting position (row B)*/{
            return true;
        }
        else if((dest->getY() == src->getY()+1) /* Check that the move is one square up*/
        && (dest->getPiece() != EMPTY) /*AND check that the destination piece*/
        && (dest->getX() == src->getX()+1 || dest->getX() == src->getX()-1)){
            return true;
        }
    }
    else if(src->getColor() == BLACK){/* Check the piece is black*/
        if((dest->getX() == src->getX()) /* check that the move is in the same column */
        && ((dest->getY() == src->getY()-1) || ((dest->getY() == src->getY()-2) && (src->getY() == 6)))){/* check if the move is one square down OR if the mvoe is two squares down and the pawn
        starts at its starting position (row G) */
            return true;
        }
        else if((dest->getY() == src->getY()+1)
        && (dest->getPiece() != EMPTY)
        && (dest->getX() == src->getX()+1 || dest->getX() == src->getX()-1)){
            return true;
        }
    }
    return false;


}
bool Board::moveRook(Square* src, Square* dest){

}
bool Board::moveKnight(Square* src, Square* dest){
    if((dest->getX() == src->getX()+2 || dest->getX() == src->getX()-2) && (dest->getY() == src->getY()+1 || dest->getY() == src->getY()-1)){
        return true;
    }else return false;
}
bool Board::moveBishop(Square* src, Square* dest){

}
bool Board::moveQueen(Square* src, Square* dest){

}
bool Board::moveKing(Square* src, Square* dest){

}
bool Board::saveGame(){return true;} // W I P
bool Board::movePiece(COLOR this_){
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
    // populate from cache
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++) square_arr[x][y].setColor(NONE);
    }
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
    string s;
    bool success;
    int turns = 1;
    while(1){
        system("CLS"); // clear
        drawBoard();
        if(myTurn) s = "White";
        else s = "Black";
        cout << " [Turn: " << turns << "] " << s <<"'s turn:    [1] Move    [2] Resign    [3] Save and Exit\n  > ";
        getline(cin, s, '\n');
        if(s == "1"){
            if(movePiece(myTurn)){
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
    }
    if(winner == BLACK) cout << "Black won! ";
    else if(winner == WHITE) cout << "White won! ";
    else cout << "Stalemate. ";
    cout << "Press enter to continue.\n";
    getline(cin, s, '\n');
    return winner;
}