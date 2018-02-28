/*****************************************
Name: Rory Dunne

File: Othello.h

Purpose: Declare all purely virtual functions
from game.h as members of othello and Declare
private variables necessary for the game

Date: 11/28/17
*****************************************/
#ifndef OTHELLO_H
#define OTHELLO_H
#include "game.h"
#include "pieces.h"
#include "colors.h"
#include <iostream>
#include <string>
namespace main_savitch_14
{

class Othello : public game{
public:
  Othello();
//PURELY VIRTUALS
   game* clone( ) const;
    // Compute all the moves that the next player can make:
   void compute_moves(std::queue<std::string>& moves) const;
  // Display the status of the current game:
   void display_status( ) const;
  // Evaluate a board position:
  int evaluate( ) const;
  // Return true if the current game is finished:
  bool is_game_over( ) const;
  // Return true if the given move is legal for the next player:
  bool is_legal(const std::string& move) const;
//VIRTUAL FUNCTIONS THAT MUST BE OVERRIDDEND
  void make_move(const std::string& move);
  void restart();
  who winning() const;

private:

  static const int width = 8;
  static const int height = 8;
  pieces spaces[width][height]; //the board
  int whitecount, blackcount;

  };
}//for the savitch namespace
#endif
