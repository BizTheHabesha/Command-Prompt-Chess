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


void Board::populate(){
    Square temp;
    temp.setPiece(EMPTY);
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            temp.setX(x);
            temp.setY(y);
            square_arr[x][y] = temp;
        }
    }
}
COLOR Board::playGame(){

    while(1){
        // redraw board
        // wait for user input
        // confirm & preform action
        system("CLS"); // clear
        break;
    }
}