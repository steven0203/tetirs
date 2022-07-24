#include<string>
#include"panel.h"
#include"ncursesw/ncurses.h"
#include<clocale>
#include"SETTING.h"


using namespace std;


SETTING::SETTING(int maxl,int maxtime):choise(0),level(1),MAXlevel(maxl),MAXtime(maxtime),TimeLimit(1)
{
	setlocale(LC_ALL,"");
    initscr();
	nodelay(stdscr,TRUE);
	keypad(stdscr,TRUE);
	noecho();
	start_color();
	cbreak();
	curs_set(0);
    init_pair(1,COLOR_RED,COLOR_BLACK);
	init_pair(2,COLOR_GREEN,COLOR_BLACK);
	init_pair(3,COLOR_YELLOW,COLOR_BLACK);
	init_pair(4,COLOR_BLUE,COLOR_BLACK);
	init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(6,COLOR_CYAN,COLOR_BLACK);
	init_pair(7,COLOR_WHITE,COLOR_BLACK);
	win[0]=newwin(14,41,14,29);
	win[1]=newwin(14,41,14,29);
	win[2]=newwin(36,100,3,3);
	win[3]=newwin(14,41,14,29);
	for(int i=0;i<4;++i)panel[i]=new_panel(win[i]);
	update_panels();
	doupdate();
	nodelay(win[3],TRUE);nodelay(win[2],TRUE);nodelay(win[1],TRUE);nodelay(win[0],TRUE);
	keypad(win[3],TRUE);keypad(win[2],TRUE);keypad(win[1],TRUE);keypad(win[0],TRUE);

}
int SETTING::getChoise()
{
	return choise;
}

int SETTING::getLevel()
{	
	return level;
}

void SETTING::setMAXlevel(int l)
{
	MAXlevel=l;
}
void SETTING::setMAXtime(int t)
{
	MAXtime=t;
}
int SETTING::get2PTime()
{
	return TimeLimit;
}

void SETTING::exucate()
{
	top_panel(panel[2]);
	TimeLimit=1;
	level=1;
	box(win[2],0,0);
	mvwprintw(win[2],2,27,"_____   ______   _____   ____     ___   ____") ;
	mvwprintw(win[2],3,27,"|_   _| | ____| |_   _| |  __\\  |_ _| / __\\");
	mvwprintw(win[2],4,27,"  | |   |  _|     | |   | |_> |  | |  \\___ \\");
    mvwprintw(win[2],5,27,"  | |   | |___    | |   |  _ <   | |   ___> |");
    mvwprintw(win[2],6,27,"  |_|   |_____|   |_|   |_| \\_\\ |___| |____/");                          
	wrefresh(win[2]);
	box(win[3],0,0);
	int go_on=TRUE,enter;
	string ch[3];
	ch[0]="1 PLAYER";
	ch[1]="2 PLAYER";
	ch[2]="EXIT";
	while(go_on)
	{
		enter=wgetch(win[3]);
		for(int i=0;i<3;++i)
		{
			if(i==choise)wattron(win[3],A_REVERSE);
			mvwprintw(win[3],2+2*i,18,"%s",ch[i].c_str());
			if(i==choise)wattroff(win[3],A_REVERSE);
		}
		wrefresh(win[3]);
		switch(enter)
		{
			case KEY_UP:--choise;choise=choise<0?2:choise;break;
			case KEY_DOWN:++choise;choise=choise>2?0:choise;break;
			case '\n':go_on=FALSE;break;
			default:break;
		}
	}
	if(choise!=2){go_on=TRUE;}
	box(win[0],0,0);                                                                                                                                    
	box(win[1],0,0);
	top_panel(panel[choise]);
	update_panels();
	doupdate();
	curs_set(1);
	while(go_on&&choise==0)
	{
		mvwprintw(win[0],4,5,"SELECT START LEVEL:(max is %d)",MAXlevel);
		mvwprintw(win[0],5,7,"%3d",level);
		wrefresh(win[0]);
		enter=wgetch(win[0]);
		switch(enter)
		{
			case KEY_UP:++level;level=level>MAXlevel?level-1:level;break;
			case KEY_DOWN:--level;level=level<=0?level+1:level;break;
			case '\n':go_on=FALSE;break;
			deaault:break;
		}
	}
	int sect=0;
	while(go_on&&choise==1)
	{
		enter=wgetch(win[1]);
		if(sect==0)
		{	
			mvwprintw(win[1],4,5,"SELECT START LEVEL:(max is %d)",MAXlevel);
			mvwprintw(win[1],5,7,"%3d",level);
			switch(enter)
			{
				case KEY_UP:++level;level=level>MAXlevel?level-1:level;break;
				case KEY_DOWN:--level;level=level<=0?level+1:level;break;
				case '\n':sect=1;break;
			}
		}
		else if(sect==1)
		{
			mvwprintw(win[1],6,5,"SET GAMETIME:(max is %d,in sec)",MAXtime);
			mvwprintw(win[1],7,7,"%6d",TimeLimit);
			switch(enter)
			{
				case KEY_UP:++TimeLimit;TimeLimit=TimeLimit>MAXtime?TimeLimit-1:TimeLimit;break;
				case KEY_DOWN:--TimeLimit;TimeLimit=TimeLimit<=0?TimeLimit+1:TimeLimit;break;
				case '\n':go_on=FALSE;break;
			}
		}
		wrefresh(win[1]);
	}
	curs_set(0);
	top_panel(panel[2]);
	update_panels();
	doupdate();
	for(int i=0;i<4;++i)
	werase(win[i]);
	
}
SETTING::~SETTING()
{
	endwin();
}



