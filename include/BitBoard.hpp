#pragma once
#include <cstddef>
#include <cstdint>
#define STATE_t uint64_t

#define redField 0
#define yellowField 1
#define emptyField 2
#define EMPTY_BOARD 0ULL
#define CLEAR_ALL_BUT_LSB 1ULL

class BitBoard{
  public:
  BitBoard();
  BitBoard(STATE_t stateRed, STATE_t stateYellow);
  ~BitBoard();

  void clear();
  void setDimensions(int width, int height);
  int getField(int x,int y) const;
  bool canPlay(int row);
  void play(int row);
  bool isRedTurn();
  bool hasWon(int color);
  bool isOver();
  bool isDraw();
  STATE_t getBoard(int board);

  BitBoard operator>>(int shift) const;
  BitBoard operator<<(int shift) const;
  BitBoard operator^(BitBoard board) const;



  private:
  void joinStates();
  STATE_t getRowCombined(int row, int boardn);
  STATE_t getColumnCombined(int column, int boardn);
  int turn;
  bool over;

  STATE_t stateRed;
  STATE_t stateYellow;
  STATE_t stateCombined;
  STATE_t columnMask;
  STATE_t firstRowMask;
  STATE_t lastRowMask;
  STATE_t ABRowMask;

  int width;
  int height;
};

