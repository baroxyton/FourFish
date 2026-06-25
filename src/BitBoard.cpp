#include "BitBoard.hpp"

BitBoard::BitBoard(){
  stateYellow = 0;
  stateRed = 0;
  stateCombined = 0;
};


BitBoard::BitBoard(STATE_t stateRed, STATE_t stateYellow){
  this->stateYellow = stateYellow;
  this->stateRed = stateRed;
};

void BitBoard::joinStates(){
  this->stateCombined = this->stateYellow ^ this->stateRed;
}

BitBoard::~BitBoard(){

};
