#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <vector>
#include "Board.hpp" 
#include "Square.hpp"

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
void Board::populate(){
    // populate from cache
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
            if(y == 0 || y == 7){// initialize everything else
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
        for(int l = 0; l < 24; l++){
            if(l % 3 == 1 || l == 1){
                if(l % 2 == 0){
                    cout << " " << (l+2)/3 << " |";
                    for(int i = 0; i < 8; i+=2) cout << "   " <<square_arr[i][(l-1)/3].getChar(BLACK)<<"  ..."<<square_arr[i+1][(l-1)/3].getChar(WHITE)<<"..";
                    cout << "|" << endl;
                }
                else{
                    cout << " " << (l+2)/3 << " |";
                    for(int i = 0; i < 8; i+=2) cout << "..." <<square_arr[i][(l-1)/3].getChar(WHITE)<<"..   "<<square_arr[i+1][(l-1)/3].getChar(BLACK)<<"  ";
                    cout << "|" << endl;
                }
            }else{
                if(l % 2 == 0) cout << "   |......      ......      ......      ......      |" << endl;
                else cout << "   |      ......      ......      ......      ......|" << endl;
            }
        }
        cout << "   +________________________________________________+" << endl;
        cout << "       a     b     c     d     e     f    g     h   " << endl;
}
COLOR Board::playGame(){
    COLOR winner;
    string s;
    while(1){
        //system("CLS"); // clear
        drawBoard();
        // wait for user input
        // confirm & preform action
        break;
    }
    if(winner == BLACK) cout << "Black won! ";
    else if(winner == WHITE) cout << "White won! ";
    else cout << "Stalemate. ";
    cout << "Press enter to continue.\n";
    getline(cin, s, '\n');
    return winner;
}