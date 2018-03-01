all: othello_game
othello_game: spaces.o game.o othello.o main.o
	g++ -Wall spaces.o game.o othello.o main.o -o othello_game
spaces.o:
	g++ -c spaces.cc
game.o:
	g++ -c game.cc
othello.o:
	g++ -c othello.cc
main.o:
	g++ -c main.cc