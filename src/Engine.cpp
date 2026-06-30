#include "BitBoard.hpp"
#include "Engine.hpp"
#include <bit>
#include <cmath>

Engine::Engine(){

}

void Engine::loadBoard(BitBoard board){
  this->board = board;
}

// TODO: after minimax
int Engine::bestMove(int depth){

}

BitBoard Engine::getBoard(){
  return this->board;
}

float Engine::staticEvalSide(const BitBoard& board, int side){
  STATE_t state = board.getBoard(side);

  // count 2 in a row
  STATE_t horizontalTwos = state & ((state&~board.firstRowMask)>>1);
  STATE_t verticalTwos = state & (state>>(board.height));
  STATE_t NETwos = state & ((state&~board.firstRowMask)>>(board.height+1));
  STATE_t NWTwos = state & ((state&~board.firstRowMask)>>(board.height-1));
  
  int totalTwos = std::popcount(horizontalTwos) + std::popcount(verticalTwos) + std::popcount(NETwos) + std::popcount(NWTwos);

  // count 3 in a row
  STATE_t horizontalThrees = state & ((state&~board.ABRowMask)>>2);
  STATE_t verticalThrees = state & (state>>(board.height*2));
  STATE_t NEThrees = state & ((state&~board.ABRowMask)>>((board.height+1)*2));
  STATE_t NWThrees = state & ((state&~board.ABRowMask)>>(board.height-1)*2);
  int totalThrees = std::popcount(horizontalThrees) + std::popcount(verticalThrees) + std::popcount(NEThrees) + std::popcount(NWThrees);
  
  int score = totalTwos + totalThrees * 3;
}

float Engine::staticEval(const BitBoard& board){
  if(board.hasWon(redField)){
    return INFINITY;
  }
  if(board.hasWon((yellowField))){
    return -INFINITY;
  }
  if(board.isDraw()){
    return 0;
  }
  return staticEvalSide(board, redField) - staticEvalSide(board, yellowField);
};

Engine::~Engine(){

}
