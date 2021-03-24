#pragma once
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
char Square::getRep(){
    
}

Board::Board(){
    populate();
}
void Board::populate(){
    Square temp;
    temp.setPiece(EMPTY);
    temp.setColor(NONE);
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            temp.setX(x);
            temp.setY(y);
            square_arr[x][y] = temp;
        }
    }
}
void Board::drawBoard(){
        // draw from cache.
        cout << "       a     b     c     d     e     f    g     h   " << endl;
        cout << "   +________________________________________________+" << endl;
        cout << "   |......      ......      ......      ......      |" << endl;
        cout << " 1 |......      ......      ......      ......      |" << endl;
        cout << "   |......      ......      ......      ......      |" << endl;
        cout << "   |      ......      ......      ......      ......|" << endl;
        cout << " 2 |      ......      ......      ......      ......|" << endl;
        cout << "   |      ......      ......      ......      ......|" << endl;
        cout << "   |......      ......      ......      ......      |" << endl;
        cout << " 3 |......      ......      ......      ......      |" << endl;
        cout << "   |......      ......      ......      ......      |" << endl;
        cout << "   |      ......      ......      ......      ......|" << endl;
        cout << " 4 |      ......      ......      ......      ......|" << endl;
        cout << "   |      ......      ......      ......      ......|" << endl;
        cout << "   |......      ......      ......      ......      |" << endl;
        cout << " 5 |......      ......      ......      ......      |" << endl;
        cout << "   |......      ......      ......      ......      |" << endl;
        cout << "   |      ......      ......      ......      ......|" << endl;
        cout << " 6 |      ......      ......      ......      ......|" << endl;
        cout << "   |      ......      ......      ......      ......|" << endl;
        cout << "   |......      ......      ......      ......      |" << endl;
        cout << " 7 |......      ......      ......      ......      |" << endl;
        cout << "   |......      ......      ......      ......      |" << endl;
        cout << "   |      ......      ......      ......      ......|" << endl;
        cout << " 8 |      ......      ......      ......      ......|" << endl;
        cout << "   |      ......      ......      ......      ......|" << endl;
        cout << "   +________________________________________________+" << endl;
        // save to cache
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