//*****************************************************************
//      CS2401- Project 6- The Othello Game, Phase 3- main.cc
//      Fall 2017- December 10, 2017
//      Author: Jarred Utt
//      Description: A main file that allows a user to play a 1v1
//					 game of Othello with a computer AI.
//*****************************************************************
#include <iostream>
#include <string>
#include <cstdlib>
#include "spaces.h"
#include "colors.h"
#include "othello.h"

using namespace std;


int main()
{
	string temp;
	char answer = 'Y';
	while(answer == 'Y')
	{
		main_savitch_14::Othello mygame;
		mygame.play();
		if(mygame.is_game_over())
		{
			mygame.display_winner();
		}	
		cout << "Would you like to play again?(Y/N) ";
		cin >> answer;
		answer = toupper(answer);
	}
	return 0;
}   

