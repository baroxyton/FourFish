#include <cstddef>
#include <cstdint>
#define STATE_t uint64_t

class BitBoard{
  public:
  BitBoard();
  BitBoard(STATE_t stateRed, STATE_t stateYellow);
  ~BitBoard();
  void clear();

  private:
  void joinStates();
  STATE_t stateRed;
  STATE_t stateYellow;
  STATE_t stateCombined;
  int width;
  int height;
};

