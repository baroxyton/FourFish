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

float Engine::staticEvalBoard(const BitBoard& board){

}

float Engine::staticEval(const BitBoard& boardRed, const BitBoard& boardYellow){
  return staticEvalBoard(boardRed) - staticEvalBoard(boardYellow);
}

Engine::~Engine(){

}
