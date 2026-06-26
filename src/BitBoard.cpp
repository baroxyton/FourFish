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

void BitBoard::setDimensions(int width, int height){
  this->height = height;
  this->width = width;
}

int BitBoard::getField(int x,int y) const { // 0-indexed
  int shift = y + x * height; // Rotated representation for efficiency; shift field to LSB
  static const STATE_t CLEAR_ALL_BUT_LSB = 1ULL;

  // none = 0
  STATE_t hasRed = (stateRed >> shift) & CLEAR_ALL_BUT_LSB; // red = 1
  STATE_t hasYellow = (stateYellow >> shift) & CLEAR_ALL_BUT_LSB; // yellow = 2
  return hasYellow * 2 + hasRed;
}


BitBoard::~BitBoard(){

};
