#ifndef TWOPLAY_H
#define TWOPLAY_H
#include<cstdlib>
#include"panel.h"
#include"ncursesw/ncurses.h"
#include<vector>
#include<string>
#include"board.h"
#include"gametime.h"
#include"tetromino.h"
#include"minos.h"
#include"OnePlay.h"

using namespace std;



class TwoPlay:public OnePlay
{
	public :
		TwoPlay();
		void exucate();
		int getScore_2();
		int getRow_2();
		void setTimeLimit(int);
	protected:
		//result :1 play again,2 back to menu ,3 exit
		int KO;
		int KO2;
		int level2;
		int score2;
		int row2;
		int TimeLimit;
		void printTime();
		board PlayBoard2;
		tetromino *mino2;
		tetromino *nextmino2;
		int gameover();
		void printHelp(int,int,int);
};





#endif
