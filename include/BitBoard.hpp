#include <cstddef>
#include <cstdint>
#define STATE_t uint64_t

class BitBoard{
  public:
  BitBoard();
  BitBoard(STATE_t stateRed, STATE_t stateYellow);
  ~BitBoard();

  private:
  void joinStates();
  STATE_t stateRed;
  STATE_t stateYellow;
  STATE_t stateCombined;
};

