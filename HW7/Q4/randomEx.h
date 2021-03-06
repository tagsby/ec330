#ifndef exh
#define exh
#include "player.h"

class exPlayer:public player{
public:
  exPlayer(square **initTable);     // initialize player
  boardSquare nextMove();        // computes a next move for the player and stores coordinates in (xx,yy)
  void otherMove(boardSquare bs);// records the move of the opponent

private:
	int **table; // maintain my own copy of the board
};
#endif
