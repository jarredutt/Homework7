/*****************************************
Name: Rory Dunne

File: pieces.h

Purpose: Create a class to hold pieces
or spaces and declare all member functions
then implement them inline

Date: 11/28/17
*****************************************/
#ifndef PIECES_H
#define PIECES_H
#include <iostream>
#include <cstdlib>
#include <string>

class pieces //Definitions are all inline
{
public:
  bool is_white() const
  {
    if(white == true)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool is_black() const
  {
    if(black == true)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool is_empty() const
  {
    if (black == false && white == false)
    return true;
    else return false;
  }

  void make_empty()
  {
    white = false;
    black = false;
  }

  void make_white()
  {
    white = true;
    black = false;
  }

  void make_black()
  {
    black = true;
    white = false;
  }

  void flip()
  {
    if (black == true)
    {
      white = true;
      black = false;
      return;
    }
    if (white == true)
    {
      black = true;
      white = false;
    }
  }

private:

  bool black;
  bool white;
  bool empty;
};
#endif
