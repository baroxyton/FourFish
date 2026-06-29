#pragma once
#include <bitset>
#include "BitBoard.hpp"

struct MinimaxResult{
  int eval;
  int move;
};

class Engine{
  public:
    Engine();
    void loadBoard(BitBoard board);
   int bestMove(int depth);
   int eval(int depth);
   bool redTurn;
   BitBoard getBoard();
   ~Engine();

  private:
   BitBoard board;
   int staticEval(STATE_t board); 
   int minimax(STATE_t board, int turn, int depth, int alpha, int beta);
};
