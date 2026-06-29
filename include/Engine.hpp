#pragma once
#include "BitBoard.hpp"

struct MinimaxResult{
  int eval;
  int move;
};

class Engine{
  public:
    bool redTurn;
    Engine();
    void loadBoard(BitBoard board);
    int bestMove(int depth);
    MinimaxResult eval(int depth);
    BitBoard getBoard();
    float staticEval();
    ~Engine();

  private:
    BitBoard board;
    float staticEvalBoard(const BitBoard& boardRed, int color); 
    float staticEval(const BitBoard& boardRed, const BitBoard& boardYellow, int color); 
    int minimax(STATE_t board, int turn, int depth, float alpha, float beta);
};
