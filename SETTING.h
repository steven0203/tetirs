#ifndef SETTING_H
#define SETTING_H
#include"panel.h"
#include"ncursesw/ncurses.h"
#include<string>

using namespace std;


class SETTING
{
	public:
		SETTING(int,int);
		~SETTING();
		void exucate();
		int getChoise();
		int getLevel();
		int get2PTime();
		void setMAXlevel(int);
		void setMAXtime(int);
	private:
		WINDOW *win[4];
		PANEL *panel[4];
		int choise;
		int level;
		int MAXlevel;
		int TimeLimit;
		int MAXtime;
};



#endif
