#include "BitBoard.hpp"
#include "Engine.hpp"
#include <bitset>

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

float Engine::staticEvalBoard(const BitBoard& board, int color){

}

float Engine::staticEval(const BitBoard& boardRed, const BitBoard& boardYellow, int color){
  
}

Engine::~Engine(){

}
