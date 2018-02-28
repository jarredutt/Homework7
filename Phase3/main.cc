#include "game.h"
#include "othello.h"
#include "colors.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
using namespace main_savitch_14;

int main()
{
  game::who winner;
  Othello myGame;
  winner = myGame.play();
  if(winner == game::HUMAN)
  {
    cout << "Player1 Wins" << endl;
  }
  else
  {
    cout << "Computer Wins" << endl;
  }
  return 0;
}
