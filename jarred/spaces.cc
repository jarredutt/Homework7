//*****************************************************************
//      CS2401- Project 6- The Othello Game, Phase 3- spaces.cc
//      Fall 2017- December 10, 2017
//      Author: Jarred Utt
//      Description: A class to hold the data of a single space to
//					 be used in some form to make a game board.
//*****************************************************************
#include "spaces.h"

Spaces::Spaces()
{
	state = 0;
	name = " ";
	space = ' ';
}

void Spaces::set_name(std::string new_name)
{
	name = new_name;
}

std::string Spaces::get_name()
{
	return name;
}

int Spaces::get_state()const
{
	return state;
}

char Spaces::get_space()
{
	return space;
}

void Spaces::set_state(int new_state)
{
	state = new_state;
}

void Spaces::flip()
{
	if (state == 1) // if black
	{
		state = 2;
		space = 'O';
	}
	else if (state == 2) //if white
	{
		state = 1;
		space = 'O';
	}
}

void Spaces::set_row(int rownum)
{
	row = rownum;
}

void Spaces::set_column(int colnum)
{
	column = colnum;
}

void Spaces::place_chip(int new_state)
{
	if (new_state == 1)
		space = 'O';
	if (new_state == 2)
		space = 'O';
	else if(new_state == 0)
		space = '.';
	state = new_state;
}

void Spaces::new_chip(int num)
{
	if (num % 2 == 0)
	{
		state = 1;
		space = 'O';
	}
	else if (num % 2 == 1)
	{
		state = 2;
		space = 'O';
	}
}

void Spaces::show_space() const
{
	if (state == 0)
		cout << B_GREEN << space << BOLD << GREEN << "|" << RESET;
	else if(state == 2)
		cout << B_GREEN << WHITE << space << BOLD << GREEN << "|" << RESET;		
	else if(state == 1)
		cout << B_GREEN << BLACK << space << BOLD << GREEN << "|" << RESET;		
}