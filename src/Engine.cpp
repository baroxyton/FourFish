#include "BitBoard.hpp"
#include "Engine.hpp"
#include <algorithm>
#include <bit>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

float FLOATINFTY = 5000;

Engine::Engine(){
  updateExploreOrder();
}

// Center first is faster -> more pruning
void Engine::updateExploreOrder(){
  exploreOrder.clear();
  std::vector<int> items;
  for(int i = 0; i < board.width; i++){
    items.push_back(i);
  }
  float center = (items[0] + items[items.size() -1])/2.0f;

  while(items.size() > 0){
    int bestIndex = -1;
    float bestDist = 1000;
    for(int i = 0; i < items.size(); i++){
      float dist = std::abs(items[i] - center);
      if(dist < bestDist){
        bestDist = dist;
        bestIndex = i;
      }
    }
    exploreOrder.push_back(items[bestIndex]);
    items.erase(items.begin() + bestIndex);
  }
}

int totes = 0;
void Engine::loadBoard(BitBoard board){
  this->board = board;
  updateExploreOrder();
}

BitBoard Engine::getBoard(){
  return this->board;
}

int Engine::bestMove(int depth){
  totes = 0;
  auto val = minimax(board, depth, -FLOATINFTY, FLOATINFTY).move;
  std::cout << std::to_string(totes) << std::endl;
  return val;
};

float Engine::staticEvalSide(const BitBoard& board, int side){
  STATE_t state = board.getBoard(side);

  // count 2 in a row
  // ** -> *
  STATE_t horizontalTwos = state & ((state&~board.firstRowMask)>>1);
  STATE_t verticalTwos = state & (state>>(board.height));
  STATE_t NETwos = state & ((state&~board.firstRowMask)>>(board.height+1));
  STATE_t NWTwos = state & ((state&~board.lastRowMask)>>(board.height-1));

  int totalTwos = std::popcount(horizontalTwos) + std::popcount(verticalTwos) + std::popcount(NETwos) + std::popcount(NWTwos);

  // count 3 in a row
  // *** -> *
  STATE_t horizontalThrees = state & ((state&~board.ABRowMask)>>2);
  STATE_t verticalThrees = state & (state>>(board.height*2));
  STATE_t NEThrees = state & ((state&~board.ABRowMask)>>((board.height+1)*2));
  STATE_t NWThrees = state & ((state&~board.lastTwoRowMask)>>(board.height-1)*2);
  int totalThrees = std::popcount(horizontalThrees) + std::popcount(verticalThrees) + std::popcount(NEThrees) + std::popcount(NWThrees);

  int score = totalTwos + totalThrees * 3;
  return score;
}

float Engine::staticEval(const BitBoard& board){
  // Heuristic
  return staticEvalSide(board, redField) - staticEvalSide(board, yellowField);
};

MinimaxResult Engine::minimax(BitBoard& board, int depth, float alpha, float beta){
  totes++;

  bool isRedTurn = board.isRedTurn();
  float bestResult = isRedTurn ? (-FLOATINFTY*2) : FLOATINFTY*2; 
  int bestMove = 3; // Default fallback value


  for(int i : exploreOrder){
    if(!board.canPlay(i)){
      continue;
    }

    BitBoard newBoard = board;
    newBoard.play(i);

    float result;
    // Base case
    if(isRedTurn && newBoard.hasWon(redField)){
      return {FLOATINFTY + depth, i}; 
    }
    if(!isRedTurn && newBoard.hasWon(yellowField)){
      return {-FLOATINFTY - depth, i};
    }
    if(depth == 0 || newBoard.isOver()){
      result = staticEval(newBoard);
    }

    // Recursive case
    else{
      result = minimax(newBoard, depth-1, alpha, beta).eval;
    }

    // Maximizer
    if(isRedTurn){
      if(result > bestResult){
        bestResult = result;
        alpha = std::max(alpha, result);
        bestMove = i;
      }
    }

    // Minimizer
    else{
      if(result < bestResult){
        bestResult = result;
        beta = std::min(beta, result);
        bestMove = i;
      }
    }

    if(beta <= alpha){
      break;
    }

  }
  return {bestResult, bestMove};
}

Engine::~Engine(){

}
