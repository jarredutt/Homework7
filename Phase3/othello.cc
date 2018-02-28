/*****************************************
Name: Rory Dunne

File: othello.cc

Purpose: Implement all purely virtual
function from game.h and more.

Date: 11/28/17
*****************************************/
#include "othello.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
namespace main_savitch_14{
Othello::Othello()
{
  restart();
}

 game* Othello::clone( ) const
 {
   return new Othello(*this);
 }
  // Compute all the moves that the next player can make:
 void Othello::compute_moves(std::queue<std::string>& moves)const
 {
   string m = "  ";

   for(char c = 'A'; c < 'I'; ++c)
   {
     m[0] = c;
     for(char n = '1'; n < '9'; ++n)
     {
       m[1] = n;
       if(is_legal(m))
       {
         moves.push(m);
       }
     }
   }
 }
// Display the status of the current game:
 void Othello::display_status( )const
 {
   cout << "  A B C D E F G H\n";
   for(int i=0; i < 8; ++i)
   {
     cout << i+1;
     for(int j = 0; j < 8; ++j)
     {
       cout << " ";
       if(spaces[i][j].is_black())
       {
         cout << GREEN << CIRCLE; //It's green because my terminal is blue
       }
       else if(spaces[i][j].is_white())
       {
         cout << WHITE << CIRCLE;
       }
       else if (spaces[i][j].is_empty())
       {
          cout << RED << SQUARE;
       }
     }
     cout << RESET << endl;
   }
/////////////////Counter///////////////////////
   int whitecount = 0, blackcount = 0;
   int i, j;
   for(i = 0; i < 8; ++i)
   {
     for(j = 0; j < 8; ++j)
     {
       if(spaces[i][j].is_black())
       blackcount += 1;
     }
   }//Counting Black

   for(i = 0; i < 8; ++i)
   {
     for(j = 0; j < 8; ++j)
     {
       if(spaces[i][j].is_white())
       whitecount += 1;
     }
   }//Counting White
   cout << "Black: " << blackcount << endl;
   cout << "White: " << whitecount << endl;
/////////////////Counter///////////////////////
 }
// Evaluate a spaces position:
// NOTE: positive values are good for the computer.
 int Othello::evaluate( )const
 {
   int best_value = 0;
   int whitecount = 0, blackcount = 0;
   int i, j;

   for(i = 0; i < 8; ++i)
   {
     for(j = 0; j < 8; ++j)
     {
       if(spaces[i][j].is_black())
       blackcount += 1;
     }
   }//Counting Black

   for(i = 0; i < 8; ++i)
   {
     for(j = 0; j < 8; ++j)
     {
       if(spaces[i][j].is_white())
       whitecount += 1;
     }
   }//Counting White

   best_value = whitecount - blackcount; //gets which move gets white most pieces
   return best_value;
 }

 game::who Othello::winning() const
 {
   int i,j;
   int whitecount = 0;
   int blackcount = 0;
   for(i = 0; i < 8; ++i)
   {
     for(j = 0; j < 8; ++j)
     {
       if(spaces[i][j].is_black())
       blackcount += 1;
     }
   }

   for(i = 0; i < 8; ++i)
   {
     for(j = 0; j < 8; ++j)
     {
       if(spaces[i][j].is_white())
       whitecount += 1;
     }
   }
   if(whitecount < blackcount)
   {
     return HUMAN;
   }

   else
   {
      return COMPUTER;
   }

 }

// Return true if the current game is finished:
 bool Othello::is_game_over( )const
 {
   int i, j;
   int piececount = 0;
   for(i = 0; i < 8; ++i) //goes through entire board
   {
     for(j = 0; j < 8; ++j)
     {
       if(spaces[i][j].is_empty() == false) //increments for every piece
       {
         ++piececount;
       }
     }
   }
   if(piececount == 64) //if 64 pieces the game is over
   {
     return true;
   }
   else
   {
     return false;
   }
   //needs code for is there are no legal moves for either players
 }
// Return true if the given move is legal for the next player:
 bool Othello::is_legal(const std::string& move)const
 {
   int a = int(toupper(move[0]) - 'A');//columns
   int b = int(move[1] - '1');//rows
/////////////////////////////////////////////////
   if(move == "helpmeobiwan" || move == "ilose")//Cheats
   {
     return true;
   }
/////////////////////////////////////////////////
   if(a > 7 || b > 7) //Checks for going off the board
   {
     return false;
   }
/////////////////////////////////////////////////
   if(spaces[b][a].is_empty() == false)//Makes sure the spot is empty
   {
     return false;
   }
/////////////////////////////////////////////////

/////////////////////////////////////////////////
   if(game::next_mover() == HUMAN)
   {
     if(spaces[b-1][a].is_white() == true)
     {
       for(int i = b - 1; i >= 0; --i)
       {
         if(spaces[i][a].is_empty() == true)
         {
           break;
         }
         if(spaces[i][a].is_black() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b+1][a].is_white() == true)
     {
       for(int i = b +1; i <= 7; ++i)
       {
         if(spaces[i][a].is_empty() == true)
         {
           break;
         }
         if(spaces[i][a].is_black() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b-1][a-1].is_white() == true)
     {
       for(int i = b - 1, j = a -1; i >= 0 && j >= 0; --i, --j)
       {
         if(spaces[i][j].is_empty() == true)
         {
           break;
         }
         if(spaces[i][j].is_black() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b-1][a+1].is_white() == true)
     {
       for(int i = b - 1, j = a +1; i >= 0 && j <= 7; --i, ++j)
       {
         if(spaces[i][j].is_empty() == true)
         {
           break;
         }
         if(spaces[i][j].is_black() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b+1][a-1].is_white() == true)
     {
       for(int i = b + 1, j = a - 1; i <= 7 && j >= 0; ++i, --j)
       {
         if(spaces[i][j].is_empty() == true)
         {
           break;
         }
         if(spaces[i][j].is_black() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b+1][a+1].is_white() == true)
     {
       for(int i = b + 1, j = a +1; i <= 7 && j <= 7; ++i, ++j)
       {
         if(spaces[i][j].is_empty() == true)
         {
           break;
         }
         if(spaces[i][j].is_black() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b][a-1].is_white() == true)
     {
       for(int i = a -1; i >= 0; --i)
       {
         if(spaces[b][i].is_empty() == true)
         {
           break;
         }
         if(spaces[b][i].is_black() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b][a+1].is_white() == true)
     {
       for(int i = a + 1; i <= 7; ++i)
       {
         if(spaces[b][i].is_empty() == true)
         {
           return false;
         }
         if(spaces[b][i].is_black() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     else{return false;}
   }
///////////////////////////////////////////
   else if(game::next_mover() == COMPUTER)
   {
     if(spaces[b-1][a].is_black() == true)
     {
       for(int i = b - 1; i >= 0; --i)
       {
         if(spaces[i][a].is_empty() == true)
         {
           break;
         }
         if(spaces[i][a].is_white() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b+1][a].is_black() == true)
     {
       for(int i = b +1; i <= 7; ++i)
       {
         if(spaces[i][a].is_empty() == true)
         {
           break;
         }
         if(spaces[i][a].is_white() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b-1][a-1].is_black() == true)
     {
       for(int i = b - 1, j = a -1; i >= 0 && j >= 0; --i, --j)
       {
         if(spaces[i][j].is_empty() == true)
         {
           break;
         }
         if(spaces[i][j].is_white() == true)
         {
           return true;
         }
       }
///////////////////////////////////////////
     }
     if(spaces[b-1][a+1].is_black() == true)
     {
       for(int i = b - 1, j = a +1; i >= 0 && j <= 7; --i, ++j)
       {
         if(spaces[i][j].is_empty() == true)
         {
           break;
         }
         if(spaces[i][j].is_white() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b+1][a-1].is_black() == true)
     {
       for(int i = b + 1, j = a - 1; i <= 7 && j >= 0; ++i, --j)
       {
         if(spaces[i][j].is_empty() == true)
         {
           break;
         }
         if(spaces[i][j].is_white() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b+1][a+1].is_black() == true)
     {
       for(int i = b + 1, j = a +1; i <= 7 && j <= 7; ++i, ++j)
       {
         if(spaces[i][j].is_empty() == true)
         {
           break;
         }
         if(spaces[i][j].is_white() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b][a-1].is_black() == true)
     {
       for(int i = a -1; i >= 0; --i)
       {
         if(spaces[b][i].is_empty() == true)
         {
           break;
         }
         if(spaces[b][i].is_white() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
     if(spaces[b][a+1].is_black() == true)
     {
       for(int i = a + 1; i <= 7; ++i)
       {
         if(spaces[b][i].is_empty() == true)
         {
           return false;
         }
         if(spaces[b][i].is_white() == true)
         {
           return true;
         }
       }
     }
///////////////////////////////////////////
   }
   else
   {return false;}
 }
//VIRTUAL FUNCTIONS THAT MUST BE OVERRIDDEND
 void Othello::restart()
 {
   int i, j;
   for(i = 0; i < 8; ++i)
   {
     for(j = 0; j < 8; ++j)
     {
       spaces[i][j].make_empty(); //the pieces were starting off
       //as random colors
     }
   }
   spaces[3][3].make_white(); //should be 4,4 and 4,5
   spaces[3][4].make_black();

   spaces[4][3].make_black(); //should be 5,4 and 5,5
   spaces[4][4].make_white();

   game::restart();
 }

 void Othello::make_move(const std::string& move)
 {
   queue<string> moves;
   int a = int(toupper(move[0]) - 'A');
   int b = int(move[1] - '1');

//////////////CHEATCODES THAT END THE GAME//////////////
  if(move == "helpmeobiwan") //Player1 Wins
  {
    int i, j;
    for(i = 0; i < 8; ++i)
    {
      for(j = 0; j < 8; ++j)
      {
        spaces[i][j].make_black();
      }
    }
  }
  if(move == "ilose") //Player1 Loses
  {
    int i, j;
    for(i = 0; i < 8; ++i)
    {
      for(j = 0; j < 8; ++j)
      {
        spaces[i][j].make_white();
      }
    }
  }
//////////////CHEATCODES THAT END THE GAME//////////////

/////////////////////PASS//////////////////////////////
    compute_moves(moves);
    if(moves.empty())
    {
      cout << "No moves, skipping." << endl;
      game::make_move(move);//increments movecount to switch mover
      return;
    }
/////////////////////PASS//////////////////////////////

   if(game::next_mover() == HUMAN)
   {

     spaces[b][a].make_black(); //[b][a] because it's backwards if not

/////////////////////////////////////////////////////
//Vertical capture downwards
/////////////////////////////////////////////////////
     for(int i = b + 1; i <= 7; ++i)
     {
       if(spaces[i][a].is_empty() == true)
       {break;}

       if(spaces[i][a].is_black() == true)
       {
         for(int j = b + 1; j <= 7; ++j)//goes back through when it
         {                             //hits the same clor piece
           if(spaces[j][a].is_black()) //stops the row capture
           break;                      //when it hits a black

           else
           spaces[j][a].flip();
         }
         break;
       }
     }
/////////////////////////////////////////////////////////////
//Vertical capture upwards
/////////////////////////////////////////////////////////////
     for(int i = b - 1; i >= 0; --i)
     {
       if(spaces[i][a].is_empty() == true)
       {break;}

       if(spaces[i][a].is_black() == true)
       {
         for(int j = b - 1; j >= 0; --j) //goes back through when
         {                              //it hits the same color piece
           if(spaces[j][a].is_black())
           break;

           else
           spaces[j][a].flip();
         }
         break;
       }
      }
/////////////////////////////////////////////////////////////
//Capture pieces to the right
/////////////////////////////////////////////////////////////
      for(int i = a + 1; i <= 7; ++i)
      {
        if(spaces[b][i].is_empty() == true)
        {break;}

        if(spaces[b][i].is_black() == true)
        {
          for(int j = a + 1; j <= 7; ++j)
          {
            if(spaces[b][j].is_black())
            break;

            else
            spaces[b][j].flip();
          }
          break;
        }
      }
/////////////////////////////////////////////////////////////
//Capture pieces to the left
/////////////////////////////////////////////////////////////
      for(int i = a - 1; i >= 0; --i)
      {
        if(spaces[b][i].is_empty() == true)
        {break;}

        if(spaces[b][i].is_black() == true)
        {
          for(int j = a - 1; j >= 0; --j)
          {
            if(spaces[b][j].is_black())
            break;

            else
            spaces[b][j].flip();
          }
          break;
        }
       }
/////////////////////////////////////////////////////////////
//Capture pieces to the left from H-A and up from 8-1
/////////////////////////////////////////////////////////////
       for(int i = b - 1, j = a -1; i >= 0 && j >= 0; --i, --j)
       {
         if(spaces[i][j].is_empty() == true)
         {break;}

         if(spaces[i][j].is_black() == true)
         {
           for(int c = b - 1, d = a -1; c >= 0 && d >= 0; --c, --d)
           {
             if(spaces[c][d].is_black())
             break;

             else
             spaces[c][d].flip();
           }
           break;
         }
        }
/////////////////////////////////////////////////////////////
//Capture pieces to the right from A-H and down from 1-8
/////////////////////////////////////////////////////////////
        for(int i = b + 1, j = a +1; i <= 7 && j <= 7; ++i, ++j)
        {
          if(spaces[i][j].is_empty() == true)
          {break;}

          if(spaces[i][j].is_black() == true)
          {
            for(int c = b + 1, d = a +1; c < 7 && d < 7; ++c, ++d)
            {
              if(spaces[c][d].is_black())
              break;

              else
              spaces[c][d].flip();
            }
            break;
          }
         }
/////////////////////////////////////////////////////////////
//Capture pieces to the left from H-A and down from 1-8
/////////////////////////////////////////////////////////////
       for(int i = b + 1, j = a -1; i <= 7 && j >=0; ++i, --j)
       {
         if(spaces[i][j].is_empty() == true)
         {break;}

         if(spaces[i][j].is_black() == true)
         {
           for(int c = b + 1, d = a -1; c <= 7 && d >= 0; ++c, --d)
           {
             if(spaces[c][d].is_black())
             break;

             else
             spaces[c][d].flip();
           }
           break;
         }
        }
/////////////////////////////////////////////////////////////
//Capture pieces to the right from A-H and up from 8-1
/////////////////////////////////////////////////////////////
       for(int i = b - 1, j = a +1; i >= 0 && j <= 7; --i, ++j)
       {
         if(spaces[i][j].is_empty() == true)
         {break;}

         if(spaces[i][j].is_black() == true)
         {
           for(int c = b - 1, d = a +1; c >= 0 && d <= 7; --c, ++d)
           {
             if(spaces[c][d].is_black())
             break;

             else
             spaces[c][d].flip();
           }
           break;
         }
        }
    }

   else if(game::next_mover()==COMPUTER)
   {
     spaces[b][a].make_white(); //[b][a] because it's backwards if not
/////////////////////////////////////////////////////////////
//Vertical capture downwards
/////////////////////////////////////////////////////////////
     for(int i = b + 1; i <= 7; ++i)
     {
       if(spaces[i][a].is_empty() == true)
       {break;}

       if(spaces[i][a].is_white() == true)
       {
         for(int j = b + 1; j <= 7; ++j)
         {
           if(spaces[j][a].is_white())
           break;

           else
           spaces[j][a].flip();
         }
         break;
       }
     }
/////////////////////////////////////////////////////////////
//Vertical capture upwards
/////////////////////////////////////////////////////////////
     for(int i = b - 1; i >= 0; --i)
     {
       if(spaces[i][a].is_empty() == true)
       {break;}

       if(spaces[i][a].is_white() == true)
       {
         for(int j = b - 1; j >= 0; --j)
         {
           if(spaces[j][a].is_white())
           break;

           else
           spaces[j][a].flip();
         }
         break;
       }
      }
/////////////////////////////////////////////////////////////
//Capture pieces to the right
/////////////////////////////////////////////////////////////
      for(int i = a + 1; i <= 7; ++i)
      {
        if(spaces[b][i].is_empty() == true)
        {break;}

        if(spaces[b][i].is_white() == true)
        {
          for(int j = a + 1; j <= 7; ++j)
          {
            if(spaces[b][j].is_white())
            break;

            else
            spaces[b][j].flip();
          }
          break;
        }
      }
/////////////////////////////////////////////////////////////
//Capture pieces to the left
/////////////////////////////////////////////////////////////
      for(int i = a - 1; i >= 0; --i)
      {
        if(spaces[b][i].is_empty() == true)
        {break;}

        if(spaces[b][i].is_white() == true)
        {
          for(int j = a - 1; j >= 0; --j)
          {
            if(spaces[b][j].is_white())
            break;

            else
            spaces[b][j].flip();
          }
          break;
        }
       }
/////////////////////////////////////////////////////////////
//Capture pieces to the left from H-A and up from 8-1
/////////////////////////////////////////////////////////////
    for(int i = b - 1, j = a -1; i >= 0 && j >= 0; --i, --j)
    {
      if(spaces[i][j].is_empty() == true)
      {break;}

      if(spaces[i][j].is_white() == true)
      {
        for(int c = b - 1, d = a -1; c >= 0 && d >= 0; --c, --d)
        {
          if(spaces[c][d].is_white())
          break;

          else
          spaces[c][d].flip();
        }
        break;
      }
     }
/////////////////////////////////////////////////////////////
//Capture pieces to the right from A-H and down from 1-8
/////////////////////////////////////////////////////////////
     for(int i = b + 1, j = a +1; i <= 7 && j <= 7; ++i, ++j)
     {
       if(spaces[i][j].is_empty() == true)
       {break;}

       if(spaces[i][j].is_white() == true)
       {
         for(int c = b + 1, d = a +1; c <= 7 && d <= 7; ++c, ++d)
         {
           if(spaces[c][d].is_white())
           break;

           else
           spaces[c][d].flip();
         }
         break;
       }
      }
/////////////////////////////////////////////////////////////
//Capture pieces to the left from H-A and down from 1-8
/////////////////////////////////////////////////////////////
    for(int i = b + 1, j = a -1; i <= 7 && j >=0; ++i, --j)
    {
      if(spaces[i][j].is_empty() == true)
      {break;}

      if(spaces[i][j].is_white() == true)
      {
        for(int c = b + 1, d = a -1; c < 7 && d > 0; ++c, --d)
        {
          if(spaces[c][d].is_white())
          break;

          else
          spaces[c][d].flip();
        }
        break;
      }
     }
/////////////////////////////////////////////////////////////
//Capture pieces to the right from A-H and up from 8-1
/////////////////////////////////////////////////////////////
    for(int i = b - 1, j = a +1; i >= 0 && j <= 7; --i, ++j)
    {
      if(spaces[i][j].is_empty() == true)
      {break;}

      if(spaces[i][j].is_white() == true)
      {
        for(int c = b - 1, d = a +1; c > 0 && d < 7; --c, ++d)
        {
          if(spaces[c][d].is_white())
          break;

          else
          spaces[c][d].flip();
        }
        break;
      }
     }
   }//bottom of else if
   game::make_move(move);//increments move_count, which makes a
                         //ternary operator return the opposite mover
 }

}//for the savitch namespace
