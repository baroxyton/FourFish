#pragma once
#include <string>
#include "BitBoard.hpp"
#include "Engine.hpp"

class TUI{
  public:
    TUI();
    void loadBoard(BitBoard board);
    void start();
    ~TUI();


  private:
    std::string getInput(std::string prompt);
    void renderBoard();
    void clear();
    bool winCheck();
    BitBoard board;
    Engine engine;
};
