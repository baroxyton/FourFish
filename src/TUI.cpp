#include "TUI.hpp"
#include <chrono>
#include <ostream>
#include <string>
#include <thread>
#include <iostream>
#include "BitBoard.hpp"

TUI::TUI(){
  this->startscreen = true;
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
  clear();
  int width = board.width;
  int height = board.height;

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      int px = board.getField(i, j);
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
    }
  }
}

TUI::~TUI(){

}
