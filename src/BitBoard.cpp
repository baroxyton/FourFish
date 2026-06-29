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

  this->columnMask = 0;
  for(int i = 0; i < height; i++){
    this->columnMask = (this->columnMask << 1ULL) + 1ULL;
  }

  this->firstRowMask = 0;
  this->lastRowMask = 0;
  for(int i = 0; i < width; i++){
    this->firstRowMask = (this->firstRowMask << height) + 1ULL;
    this->ABRowMask = (this->ABRowMask << height) + 3ULL;
    this->lastRowMask = (this->lastRowMask << height) | (1ULL << (height-1ULL));
  }
}

STATE_t BitBoard::getColumnCombined(int column){
  return (stateCombined >> (column * height)) & columnMask;
}

bool BitBoard::canPlay(int column){
  return getColumnCombined(column) > columnMask;
}

bool BitBoard::isRedTurn(){
 return turn%2 == 0;
}

void BitBoard::play(int column){
  STATE_t move = getColumnCombined(column);
  move = ((((move) << 1)^1) & ~move) << (column * height);

  if(isRedTurn()){
    stateRed = stateRed ^ move;
  }
  else{
    stateYellow = stateYellow ^ move;
  }

  joinStates();
}

int BitBoard::getField(int x,int y) const { // 0-indexed
  int shift = y + x * height; // Rotated representation for efficiency; shift field to LSB
  static const STATE_t CLEAR_ALL_BUT_LSB = 1ULL;

  // none = 0
  STATE_t hasRed = (stateRed >> shift) & CLEAR_ALL_BUT_LSB; // red = 1
  STATE_t hasYellow = (stateYellow >> shift) & CLEAR_ALL_BUT_LSB; // yellow = 2
  return hasYellow * 2 + hasRed;
}

bool BitBoard::hasWon(int color){
  STATE_t board;
  if(color == redField){
    board = stateRed;
  }
  else{
    board = stateYellow;
  }

  // check column win
  // **** -> ** -> *
  //            prevent wraparound bug,   isolate 2x in a row           isalote 4x in a row
  bool won =   (board & ((board&~ABRowMask) >> 2)) & (((board & ((board&~ABRowMask) >> 2)))&(~ABRowMask)) >> 1;

  // check row win
  won = won || (board & (board >> 2 * height)) & (((board >> 2 * height) & board) >> 1 * height);

  // check NE diagonal
  won = won || (board & ((board&~ABRowMask) >> (2 * (height+1)))) & (((board & ((board&~ABRowMask) >> (2 * (height+1)))))&(~ABRowMask)) >> (height+1);
  // check SW diagonal
  won = won || (board & ((board&~ABRowMask) >> (2 * (height-1)))) & (((board & ((board&~ABRowMask) >> (2 * (height-1)))))&(~ABRowMask)) >> (height-1);
  return won;
}


BitBoard::~BitBoard(){

};
