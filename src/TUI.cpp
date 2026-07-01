#include "TUI.hpp"
#include <chrono>
#include <ostream>
#include <string>
#include <thread>
#include <iostream>
#include "BitBoard.hpp"

int DEPTH = 10;

TUI::TUI(){
  board.clear();
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

  // Print numbers
  std::cout << "          ";
  for(int i = 0; i < width; i++){
    std::cout << " " << i << "  ";
  }
  std::cout << std::endl;
}

bool TUI::winCheck(){
    if(board.hasWon(redField)){
      std::cout << "Red won!" << std::endl;
      
      return true;
    }
    if(board.hasWon(yellowField)){
      std::cout << "Yellow won!" << std::endl;
      return true;
    }
    if(board.isDraw()){
      std::cout << "It's a draw!" << std::endl;
      return true;
    }
  return false;
}

void TUI::start(){
  while(true){
    clear();
    renderBoard();
    bool played = false;
    while(!played){
      int move = std::stoi(getInput("enter move (0-6): "));
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
      break;
    }
    std::cout << "Engine is thinking.." << std::endl;
    engine.loadBoard(board);
    int engineMove = engine.bestMove(DEPTH);
    if(engineMove == -1){
      over = true;
      std::cout << "Engine resigned" << std::endl;
      break;
    }
    board.play(engineMove);
    renderBoard();
    std::cout << "Engine move: " << engineMove << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    over = winCheck();
    if(over){
      break;
    }
  }
}

TUI::~TUI(){

}
