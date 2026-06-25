#include "BitBoard.hpp"

BitBoard::BitBoard(){
  setDimensions(7,6);
  clear();
}

BitBoard::BitBoard(STATE_t stateRed, STATE_t stateYellow){
  setDimensions(7,6);
  this->stateYellow = stateYellow;
  this->stateRed = stateRed;
  joinStates();
};

void BitBoard::joinStates(){
  this->stateCombined = this->stateYellow ^ this->stateRed;
}

void BitBoard::clear(){
  this->stateYellow = 0;
  this->stateRed = 0;
  this->stateCombined = 0;
}

void BitBoard::setDimensions(const int& width, const int& height){
  this->height = height;
  this->width = width;
}


BitBoard::~BitBoard(){

};
