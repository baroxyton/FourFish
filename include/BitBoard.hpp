#pragma once
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
    void play(int row);
    int getField(int x,int y) const;
    bool canPlay(int row) const;
    bool isRedTurn() const;
    bool hasWon(int color) const;
    bool isOver() const;
    bool isDraw() const;
    STATE_t getBoard(int board) const;


    BitBoard operator>>(int shift) const;
    BitBoard operator<<(int shift) const;
    BitBoard operator^(BitBoard board) const;
    STATE_t columnMask;
    STATE_t firstRowMask;
    STATE_t lastRowMask;
    STATE_t ABRowMask;
    int width;
    int height;



  private:
    void joinStates();
    STATE_t getRow(int row, STATE_t board) const;
    STATE_t getColumn(int column, STATE_t board) const;
    int turn;
    bool over;

    STATE_t stateRed;
    STATE_t stateYellow;
    STATE_t stateCombined;

};

