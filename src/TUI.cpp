#include "TUI.hpp"
#include <chrono>
#include <ostream>
#include <string>
#include <thread>
#include <iostream>
#include "BitBoard.hpp"

TUI::TUI(){
  this->startscreen = true;
  board.clear();
}

void TUI::exit(){
  this->running = false;
}

void TUI::clear(){
  std::cout << "\033[2J\033[1;1H";
}

std::string TUI::getInput(std::string prompt){
  std::cout << std::endl <<  prompt << std::endl;
  std::string result;
  std::cin >> result;
  return result;
}

void TUI::renderBoard(){
  int width = board.width;
  int height = board.height;

  clear();
  std::cout << "\n\n\n\n\n";

  for(int i = height-1; i >= 0; i--){
    std::cout << "          ";
    for(int j = 0; j < width; j++){
      int px = board.getField(j, i);
      if(px == redField){
        std::cout << "[🔴]";
      }
      if(px == yellowField){
        std::cout << "[🟡]";
      }
      if(px == emptyField){
        std::cout << "[  ]";
      }
    }
    std::cout << std::endl;
  }
}

bool TUI::winCheck(){
    if(board.hasWon(redField)){
      std::cout << "Red won!" << std::endl;
      
      this->exit();
      return true;
    }
    if(board.hasWon(yellowField)){
      std::cout << "Yellow won!" << std::endl;
      this->exit();
      return true;
    }
    if(board.isDraw()){
      std::cout << "It's a draw!" << std::endl;
      this->exit();
      return true;
    }
  return false;
}

void TUI::start(){
  int delay = 16; // ms
  while(running){
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    // TODO
    if(startscreen){
      clear();
      startscreen = false;
    }
    clear();
    renderBoard();
    bool played = false;
    while(!played){
      int move = std::stoi(getInput("enter move (1-7): "));
      bool canPlay = board.canPlay(move);
      if(canPlay){
        board.play(move);
        played = true;
      }
      else{
        std::cout << "Invalid move" << std::to_string(move) << std::endl;
      }
    }

    renderBoard();
    bool over = winCheck();
    if(over){
      continue;
    }
    std::cout << "Engine is thinking.." << std::endl;
    engine.loadBoard(board);
    int engineMove = engine.bestMove(14);
    if(engineMove == -1){
      over = true;
      std::cout << "Engine resigned" << std::endl;
      break;
    }
    board.play(engineMove);
    std::cout << "Engine move: " << engineMove << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    over = winCheck();
    if(over){
      continue;
    }
  }
}

TUI::~TUI(){

}
