//*****************************************************************
//      CS2401- Project 6- The Othello Game, Phase 3- othello.h
//      Fall 2017- December 10, 2017
//      Author: Jarred Utt
//      Description: A class header file for the class Othello,
//  				 which is derived from the parent class Game.
//*****************************************************************
#ifndef OTHELLO_H
#define OTHELLO_H
#include <queue>
#include <string>
#include "colors.h"
#include "spaces.h"
#include "game.h"
namespace main_savitch_14
{

class Othello:public game
{
    public:
	Othello();
	virtual ~Othello();
	void create_board();

	int searchBlackN(int j, int i);
	int searchWhiteN(int j, int i);
	int searchBlackNE(int j, int i);
	int searchWhiteNE(int j, int i);
	int searchBlackE(int j, int i);
	int searchWhiteE(int j, int i);
	int searchBlackSE(int j, int i);
	int searchWhiteSE(int j, int i);
	int searchBlackS(int j, int i);
	int searchWhiteS(int j, int i);
	int searchBlackSW(int j, int i);
	int searchWhiteSW(int j, int i);
	int searchBlackW(int j, int i);
	int searchWhiteW(int j, int i);
	int searchBlackNW(int j, int i);
	int searchWhiteNW(int j, int i);

	int csearchBlackN(int j, int i)const;
	int csearchWhiteN(int j, int i)const;
	int csearchBlackNE(int j, int i)const;
	int csearchWhiteNE(int j, int i)const;
	int csearchBlackE(int j, int i)const;
	int csearchWhiteE(int j, int i)const;
	int csearchBlackSE(int j, int i)const;
	int csearchWhiteSE(int j, int i)const;
	int csearchBlackS(int j, int i)const;
	int csearchWhiteS(int j, int i)const;
	int csearchBlackSW(int j, int i)const;
	int csearchWhiteSW(int j, int i)const;
	int csearchBlackW(int j, int i)const;
	int csearchWhiteW(int j, int i)const;
	int csearchBlackNW(int j, int i)const;
	int csearchWhiteNW(int j, int i)const;

	void display_winner();
	virtual void make_move(const std::string& move);
   	virtual void restart();
// *******************************************************************
// PURE VIRTUAL FUNCTIONS
// *******************************************************************
// (these must be provided for each derived class)
// Return a pointer to a copy of myself:
    virtual Othello* clone() const;

// Compute all the moves that the next player can make:
    virtual void compute_moves(std::queue<std::string>& moves) const;

// Display the status of the current game:
	virtual void display_status() const;
// Evaluate a board position:
// NOTE: positive values are good for the computer.
    virtual int evaluate() const;

// Return true if the current game is finished:
    virtual bool is_game_over() const 
    {
    	if (move_number == 60)
			return true;
		else
			return false;
	}
//Return true if the given move is legal for player to make
	virtual bool is_legal(const std::string& move)const;
    
    private:
	Spaces board[8][8];
	int move_number;
	int pass_number;
};

int get_num(const std::string move, int index);
}
#endif
