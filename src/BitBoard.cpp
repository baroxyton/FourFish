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
  this->turn = 0;
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

STATE_t BitBoard::getColumn(int column, STATE_t board) const {
  return (board >> (column * height)) & columnMask;
}

STATE_t BitBoard::getRow(STATE_t board, int width, int height, int row){
  STATE_t result = 0ULL;
  for(STATE_t i = 0; i < width; i++){
    result |= ((board << (height*i + row)) & CLEAR_ALL_BUT_LSB) >> row;
  }
  return result;
}

bool BitBoard::canPlay(int column) const {
  return getColumn(stateCombined, columnMask, height, column) > columnMask;
}

bool BitBoard::isRedTurn() const {
  return turn%2 == 0;
}

void BitBoard::play(int column){
  STATE_t move = getColumn(column, emptyField);
  move = ((((move) << 1ULL)|1ULL) & ~move) << (column * height);

  if(isRedTurn()){
    stateRed = stateRed | move;
  }
  else{
    stateYellow = stateYellow | move;
  }

  joinStates();
}

int BitBoard::getField(int x, int y) const {
  int shift = y + x * height; // Rotated representation for efficiency; shift field to LSB

  // none = 0
  STATE_t hasRed = (stateRed >> shift) & CLEAR_ALL_BUT_LSB; // red = 1
  STATE_t hasYellow = (stateYellow >> shift) & CLEAR_ALL_BUT_LSB; // yellow = 2
  return hasYellow * 2 + hasRed;
}

bool BitBoard::hasWon(int color) const{
  STATE_t board = getBoard(color);
  // check column win
  // **** -> ** -> *
  //            prevent wraparound bug,   isolate 2x in a row           isalote 4x in a row
  bool won =   (board & ((board&~ABRowMask) >> 2)) & (((board & ((board&~ABRowMask) >> 2)))&(~ABRowMask)) >> 1;

  // check row win
  won = won || (board & (board >> 2 * height)) & (((board >> 2 * height) & board) >> 1 * height);

  // check NE diagonal
  won = won || (board & ((board&~ABRowMask) >> (2 * (height+1)))) & (((board & ((board&~ABRowMask) >> (2 * (height+1)))))&(~ABRowMask)) >> (height+1);
  // check NW diagonal
  won = won || (board & ((board&~ABRowMask) >> (2 * (height-1)))) & (((board & ((board&~ABRowMask) >> (2 * (height-1)))))&(~ABRowMask)) >> (height-1);
  return won;
}

bool BitBoard::isOver() const {
  return hasWon(redField) || hasWon(yellowField) || ~stateCombined == EMPTY_BOARD;
}

bool BitBoard::isDraw() const {
  return (~stateCombined == EMPTY_BOARD) && !hasWon(redField) && !hasWon(yellowField);
}

STATE_t BitBoard::getBoard(int board) const {
  if(board == redField) return stateRed;
  if(board == yellowField) return stateYellow;
  if(board == emptyField) return stateCombined;
}

BitBoard::~BitBoard(){

};
