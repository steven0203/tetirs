#ifndef ONEPLAY_H
#define ONEPLAY_H
#include"board.h"
#include"tetromino.h"
#include"minos.h"
#include"ncursesw/ncurses.h"
#include<clocale>
#include"panel.h"
#include"gametime.h"
#include<vector>
#include<string>
using namespace std;
class OnePlay
{
	public:
	OnePlay();
	void exucate();
	void setStartLevel(int);
	int getScore();
	int getRow();	
	int getResult();
	void setSpeeds(vector<int>);
	protected:
	gametime clock;
	int result;//1 is play again,2 is back to menu,3 exit
	WINDOW *win[3];
	PANEL *panel[3];
	int startlevel;
	int level;
	int score;
	int row;
	vector<int> speeds;
	board PlayBoard;
	tetromino *mino;
	tetromino *nextmino;
	int calculateScore(int,tetromino *);
	int calculateScore(int,int);
	void PrintBoard(int,int,board &);
	void printTime();
	tetromino *CreateMino(board &,int =0);
	void setborder(int,int,int,int);
	void printMino(int ,int ,string,tetromino *);
	void printHelp(int,int);
	int pause(string ,int );
};



#endif 
