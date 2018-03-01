//*****************************************************************
//      CS2401- Project 6- The Othello Game, Phase 3- spaces.h
//      Fall 2017- December 10, 2017
//      Author: Jarred Utt
//      Description: A header class to hold the data for a single 
//					 space of a game board.
//*****************************************************************
#ifndef SPACES_H
#define SPACES_H
#include <iostream>
#include "colors.h"


class Spaces
{
   public:
	Spaces();
	void set_name(std::string new_name);
	std::string get_name();
	void set_state(int new_state);
	int get_state()const;
	char get_space();
	void set_space(char new_space) {space = ' ';}
	void set_row(int rownum);
	void set_column(int colnum);
	void show_space() const;
	void place_chip(int new_state);
	void new_chip(int num);
	void flip();
   private:
	int state; //black = 1, white = 2, empty = 0
	std::string name; //'E6'
	int row;
	int column; 
	char space; //empty or 'O'
};
#endif