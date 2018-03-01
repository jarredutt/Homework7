//*****************************************************************
//      CS2401- Project 6- The Othello Game, Phase 3- othello.cc
//      Fall 2017- December 10, 2017
//      Author: Jarred Utt
//      Description: Implementation for Othello class derived from 
//				     the game class that allows the user to play a 
//					 game of Othello. Includes functions for searching,
//					 legal moves, and making move.     
//*****************************************************************
#include "othello.h"

namespace main_savitch_14
{
Othello::Othello()
{
	create_board(); 
	move_number=0; 
	pass_number=0;
}

Othello::~Othello()
    {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j].set_state(0);
			board[i][j].set_space(' ');
		}
	}
}

void Othello::create_board()
{
	std::string tmp;
	char ch, num;
	int i, j;
	for (i = 0, ch = 'A'; i <= 7; ++i)
	{
		for (j = 0, num = '1'; j <= 7; ++j)
		{
			board[i][j].set_row(i+1);
			board[i][j].set_column(j+1);
			tmp = ch;
			tmp += num;
			board[i][j].set_name(tmp);
			num++;
		}
		ch++;
	}
	board[3][3].place_chip(2);
	board[3][4].place_chip(1);
	board[4][3].place_chip(1);
	board[4][4].place_chip(2);
}

Othello* Othello::clone( ) const
{
	Othello* copy;
	copy = new Othello;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			copy->board[i][j] = board[i][j];
		}
	}
	return copy;
}

void Othello::display_status( ) const
{
	cout << " ";
	for (int i = 0; i <= 7; ++i)
		cout << GREEN << "|" << BLACK  << i + 1;
	cout << GREEN<< "|" << endl;
	char ch = 'A';
	for (int i = 0; i <= 7; ++i)
	{
		cout << BLACK << ch << GREEN << "|";
		for (int j = 0; j <= 7; ++j)
		{
			board[i][j].show_space();
		}
		cout << BLACK << endl;
		++ch;
	}
}

void Othello::make_move(const std::string& move) 
{ 
	int j = get_num(move, 0);
	int i = get_num(move, 1);
	int trash;
	
	if(moves_completed() % 2 == 0)
	{
		board[j][i].new_chip(moves_completed());
		trash = searchBlackN(j, i);
		trash = searchBlackNE(j, i);
		trash = searchBlackE(j, i);
		trash = searchBlackSE(j, i);
		trash = searchBlackS(j, i);
		trash = searchBlackSW(j, i);
		trash = searchBlackW(j, i);
		trash = searchBlackNW(j, i);
	}
	else
	{
		board[j][i].new_chip(moves_completed());
		trash = searchWhiteN(j, i);
		trash = searchWhiteNE(j, i);
		trash = searchWhiteE(j, i);
		trash = searchWhiteSE(j, i);
		trash = searchWhiteS(j, i);
		trash = searchWhiteSW(j, i);
		trash = searchWhiteW(j, i);
		trash = searchWhiteNW(j, i);
	}
	move_number++;
	game::make_move(move); 
}
    
void Othello::restart()
{
	create_board();
	game::restart();
}

    void Othello::compute_moves(std::queue<std::string>& moves) const 
{
	std::string move;
	for (char ch1 = 'A'; ch1 <= 'H'; ch1++)
	{
		for (char ch2 = '1'; ch2 <= '8'; ch2++)
		{
			move = ch1;
			move += ch2;
			if (is_legal(move))
				moves.push(move);
		}
	}
}

int Othello::evaluate( ) const 
{
	int black_count = 0;
	int white_count = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j].get_state() == 1)
				black_count++;
			else if (board[i][j].get_state() == 2)
				white_count++;
		}
	}
	if (black_count > white_count)
		return -1;
	else if (white_count > black_count)
		return 1;
	else
		return 0;
}

bool Othello::is_legal(const std::string& move) const
{
	int j = get_num(move, 0);
	int i = get_num(move, 1);
	if (i == -1 || j == -1)
		return false;
	if (board[j][i].get_state() == 1 || board[j][i].get_state() == 2)
		return false;
	if (moves_completed() % 2 == 0)
	{
		if (csearchBlackN(j, i) == 1 || csearchBlackNE(j, i) == 1 || csearchBlackE(j, i) == 1 || csearchBlackSE(j, i) == 1 || csearchBlackS(j, i) == 1 || csearchBlackSW(j, i) == 1 || csearchBlackW(j, i) == 1 || csearchBlackNW(j, i) == 1)
		{
			return true;
		}
		return false;
	}
	else
	{
		if (csearchWhiteN(j, i) == 1 || csearchWhiteNE(j, i) == 1 || csearchWhiteE(j, i) == 1 || csearchWhiteSE(j, i) == 1 || csearchWhiteS(j, i) == 1 || csearchWhiteSW(j, i) == 1 || csearchWhiteW(j, i) == 1 || csearchWhiteNW(j, i) == 1)
		{
			return true;
		}
		return false;
	}

}  

int get_num(const std::string move, int index) 
{
	char ch = move.at(index);
	if (ch == 'A' || ch == 'a' || ch == '1')
		return 0;
	if (ch == 'B' || ch == 'b' || ch == '2')
		return 1;
	if (ch == 'C' || ch == 'c' || ch == '3')
		return 2;
	if (ch == 'D' || ch == 'd' || ch == '4')
		return 3;
	if (ch == 'E' || ch == 'e' || ch == '5')
		return 4;
	if (ch == 'F' || ch == 'f' || ch == '6')
		return 5;
	if (ch == 'G' || ch == 'g' || ch == '7')
		return 6;
	if (ch == 'H' || ch == 'h' || ch == '8')
		return 7;
	return -1;
}

void Othello::display_winner()
{
	int theWinner = this->evaluate();
	if(theWinner == 0)
		cout << "Miraculously there is a tie somehow, both win!\n";

	else if (theWinner == 1)
		cout << "White is the winner!\n";

	else if (theWinner == -1)
		cout << "Black is the winner!\n";
}

int Othello::searchBlackN(int j, int i)
{
	if (j == 0) //top row
		return 0;
	else
	{
		if (board[j-1][i].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j-1][i].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black
			board[j][i].flip();			
			return 5;
		}
		if (board[j-1][i].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = searchBlackN(j-1, i); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//move
		}
	}

}

int Othello::searchWhiteN(int j, int i)
{
	if (j == 0) //top row
		return 0;
	else
	{
		if (board[j-1][i].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j-1][i].get_state() == 2)
		{	//above is white
			board[j][i].flip();
			return 5;
		}
		else
		{					//above is black
			int tmp = searchWhiteN(j-1, i);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//move
		}
	}
}

int Othello::searchBlackNE(int j, int i)
{
	if (j == 0 || i == 7)
		return 0;
	else
	{
		if (board[j-1][i+1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j-1][i+1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black
			board[j][i].flip();			
			return 5;
		}
		if (board[j-1][i+1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = searchBlackNE(j-1, i+1); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::searchWhiteNE(int j, int i)
{
	if (j == 0 || i == 7)
		return 0;
	else
	{
		if (board[j-1][i+1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j-1][i+1].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			board[j][i].flip();
			return 5;
		}
		if (board[j-1][i+1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = searchWhiteNE(j-1, i+1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//move
		}
	}
}

int Othello::searchBlackE(int j, int i)
{
	if (i == 7) 
		return 0;
	else
	{
		if (board[j][i+1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j][i+1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black
			board[j][i].flip();			
			return 5;
		}
		if (board[j][i+1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = searchBlackE(j, i+1); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//move
		}
	}
}

int Othello::searchWhiteE(int j, int i)
{	
	if (i == 7)
		return 0;
	else
	{
		if (board[j][i+1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j][i+1].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			board[j][i].flip();
			return 5;
		}
		if (board[j][i+1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = searchWhiteE(j, i+1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//move
		}
	}
}

int Othello::searchBlackSE(int j, int i)
{
	if (j == 7 || i == 7) 
		return 0;
	else
	{
		if (board[j+1][i+1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j+1][i+1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black
			board[j][i].flip();			
			return 5;
		}
		if (board[j+1][i+1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = searchBlackSE(j+1, i+1); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//move
		}
	}
}

int Othello::searchWhiteSE(int j, int i)
{
	if (j == 7 || i == 7)
		return 0;
	else
	{
		if (board[j+1][i+1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j+1][i+1].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			board[j][i].flip();
			return 5;
		}
		if (board[j+1][i+1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = searchWhiteSE(j+1, i+1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::searchBlackS(int j, int i)
{
	if (j == 7) 
		return 0;
	else
	{
		if (board[j+1][i].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j+1][i].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black
			board[j][i].flip();			
			return 5;
		}
		if (board[j+1][i].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = searchBlackS(j+1, i); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::searchWhiteS(int j, int i)
{	
	if (j == 7)
		return 0;
	else
	{
		if (board[j+1][i].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j+1][i].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			board[j][i].flip();
			return 5;
		}
		if (board[j+1][i].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = searchWhiteS(j+1, i);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::searchBlackSW(int j, int i)
{
	if (j == 7 || i == 0) 
		return 0;
	else
	{
		if (board[j+1][i-1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j+1][i-1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black
			board[j][i].flip();			
			return 5;
		}
		if (board[j+1][i-1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = searchBlackSW(j+1, i-1); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::searchWhiteSW(int j, int i)
{	
	if (j == 7 || i == 0)
		return 0;
	else
	{
		if (board[j+1][i-1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j+1][i-1].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			board[j][i].flip();
			return 5;
		}
		if (board[j+1][i-1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;}
		else
		{					//above is black
			int tmp = searchWhiteSW(j+1, i-1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::searchBlackW(int j, int i)
{
	if (i == 0) 
		return 0;
	else
	{
		if (board[j][i-1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j][i-1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black
			board[j][i].flip();			
			return 5;
		}
		if (board[j][i-1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = searchBlackW(j, i-1); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::searchWhiteW(int j, int i)
{	
	if (i == 0)
		return 0;
	else
	{
		if (board[j][i-1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j][i-1].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			board[j][i].flip();
			return 5;
		}
		if (board[j][i-1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = searchWhiteW(j, i-1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//there was a white at end		
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::searchBlackNW(int j, int i)
{
	if (j == 0 || i == 0) 
		return 0;
	else
	{
		if (board[j-1][i-1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j-1][i-1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black
			board[j][i].flip();			
			return 5;
		}
		if (board[j-1][i-1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = searchBlackNW(j-1, i-1); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//there was a black at end			
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::searchWhiteNW(int j, int i)
{	
	if (j == 0 || i == 0)
		return 0;
	else
	{
		if (board[j-1][i-1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j-1][i-1].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			board[j][i].flip();
			return 5;
		}
		if (board[j-1][i-1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = searchWhiteNW(j-1, i-1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//there was a white at end		
				board[j][i].flip();
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchBlackN(int j, int i)const
{
	if (i == 0) //top row
		return 0;
	else
	{
		if (board[j-1][i].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j-1][i].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black			
			return 5;
		}
		if (board[j-1][i].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = csearchBlackN(j-1, i); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}

}

int Othello::csearchWhiteN(int j, int i)const
{
	if (j == 0) //top row
		return 0;
	else
	{
		if (board[j-1][i].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j-1][i].get_state() == 2)
		{	//above is white
			return 5;
		}
		else
		{					//above is black
			int tmp = csearchWhiteN(j-1, i);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchBlackNE(int j, int i)const
{
	if (j == 0 || i == 7)
		return 0;
	else
	{
		if (board[j-1][i+1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j-1][i+1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black			
			return 5;
		}
		if (board[j-1][i+1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = csearchBlackNE(j-1, i+1); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchWhiteNE(int j, int i)const
{
	if (j == 0 || i == 7)
		return 0;
	else
	{
		if (board[j-1][i+1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j-1][i+1].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			return 5;
		}
		if (board[j-1][i+1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = csearchWhiteNE(j-1, i+1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchBlackE(int j, int i)const
{
	if (i == 7) 
		return 0;
	else
	{
		if (board[j][i+1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j][i+1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black			
			return 5;
		}
		if (board[j][i+1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = csearchBlackE(j, i+1); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchWhiteE(int j, int i)const
{	
	if (i == 7)
		return 0;
	else
	{
		if (board[j][i+1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j][i+1].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			return 5;
		}
		if (board[j][i+1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = csearchWhiteE(j, i+1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchBlackSE(int j, int i)const
{
	if (j == 7 || i == 7) 
		return 0;
	else
	{
		if (board[j+1][i+1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j+1][i+1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black			
			return 5;}
		if (board[j+1][i+1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = csearchBlackSE(j+1, i+1); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchWhiteSE(int j, int i)const
{
	if (j == 7 || i == 7)
		return 0;
	else
	{
		if (board[j+1][i+1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j+1][i+1].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			return 5;}
		if (board[j+1][i+1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = csearchWhiteSE(j+1, i+1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchBlackS(int j, int i)const
{
	if (j == 7) 
		return 0;
	else
	{
		if (board[j+1][i].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j+1][i].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black			
			return 5;
		}
		if (board[j+1][i].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = csearchBlackS(j+1, i); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchWhiteS(int j, int i)const
{	
	if (j == 7)
		return 0;
	else
	{
		if (board[j+1][i].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j+1][i].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			return 5;
		}
		if (board[j+1][i].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = csearchWhiteS(j+1, i);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchBlackSW(int j, int i)const
{
	if (j == 7 || i == 0) 
		return 0;
	else
	{
		if (board[j+1][i-1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j+1][i-1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black			
			return 5;
		}
		if (board[j+1][i-1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = csearchBlackSW(j+1, i-1); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchWhiteSW(int j, int i)const
{	
	if (j == 7 || i == 0)
		return 0;
	else
	{
		if (board[j+1][i-1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j+1][i-1].get_state() == 2 && board[j][i].get_state() == 1)
			//above is white
			return 5;
	}
		if (board[j+1][i-1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = csearchWhiteSW(j+1, i-1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
}

int Othello::csearchBlackW(int j, int i)const
{
	if (i == 0) 
		return 0;
	else
	{
		if (board[j][i-1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j][i-1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black			
			return 5;
		}
		if (board[j][i-1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = csearchBlackW(j, i-1); 	
			if (tmp == 5 && board[j][i].get_state() == 2)
			{	//black at end			
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchWhiteW(int j, int i)const
{	
	if (i == 0)
		return 0;
	else
	{
		if (board[j][i-1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j][i-1].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			return 5;
		}
		if (board[j][i-1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = csearchWhiteW(j, i-1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchBlackNW(int j, int i)const
{
	if (j == 0 || i == 0) 
		return 0;
	else
	{
		if (board[j-1][i-1].get_state() == 0)
		{ 	//above space is empty
			return 0;
		}
		if (board[j-1][i-1].get_state() == 1 && board[j][i].get_state() == 2)
		{ 	//above space is black;			
			return 5;
		}
		if (board[j-1][i-1].get_state() == 1 && board[j][i].get_state() == 1)
			return 0;
		else
		{					//above space is white
			int tmp = csearchBlackNW(j-1, i-1); 	
			if (tmp == 5 && board[j][i].get_state() == 2){	//black at end			
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}

int Othello::csearchWhiteNW(int j, int i)const
{	
	if (j == 0 || i == 0)
		return 0;
	else
	{
		if (board[j-1][i-1].get_state() == 0)
		{	//above is empty
			return 0;
		}
		if (board[j-1][i-1].get_state() == 2 && board[j][i].get_state() == 1)
		{	//above is white
			return 5;
		}
		if (board[j-1][i-1].get_state() == 2 && board[j][i].get_state() == 2)
		{
			return 0;
		}
		else
		{					//above is black
			int tmp = csearchWhiteNW(j-1, i-1);
			if (tmp == 5 && board[j][i].get_state() == 1)
			{	//white at end		;
				return tmp;
			}
			if (tmp !=5)
				return 0;	//no move
			return 1;		//possible move
		}
	}
}
}