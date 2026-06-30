#pragma once
#include <string>
#include "BitBoard.hpp"
#include "Engine.hpp"

class TUI{
  public:
    TUI();
    void loadBoard(BitBoard board);
    void start();
    void exit();
    ~TUI();


  private:
    std::string getInput(std::string prompt);
    void renderBoard();
    void clear();
    bool running;
    bool startscreen;
    BitBoard board;
};
