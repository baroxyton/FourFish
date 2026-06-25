#include "BitBoard.hpp"

BitBoard::BitBoard(){
  clear();
}

BitBoard::BitBoard(STATE_t stateRed, STATE_t stateYellow){
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

BitBoard::~BitBoard(){

};
