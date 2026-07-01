#pragma once
#include <vector>
#include "BitBoard.hpp"

struct MinimaxResult{
  float eval;
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
    float staticEvalSide(const BitBoard& board, int side); 
    float staticEval(const BitBoard& board); 
    MinimaxResult minimax(BitBoard& board, int depth, float alpha, float beta);
    void updateExploreOrder();
    std::vector<int> exploreOrder;
};
