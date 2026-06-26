#include <cstddef>
#include <cstdint>
#define STATE_t uint64_t

#define redField 0
#define yellowField 1
#define emptyField 2

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
  bool isOver();
  bool isDraw();
  bool hasWon(int color);
  int getBoard();

  BitBoard operator>>(int shift) const;
  BitBoard operator<<(int shift) const;
  BitBoard operator^(BitBoard board) const;



  private:
  void joinStates();
  int getRow(int row);
  int getColumn(int column);
  int turn;
  bool over;
  STATE_t stateRed;
  STATE_t stateYellow;
  STATE_t stateCombined;
  int width;
  int height;
};

