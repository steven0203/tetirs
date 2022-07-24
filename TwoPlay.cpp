#include<vector>
#include<cstdlib>
#include<string>
#include"ncursesw/ncurses.h"
#include"panel.h"
#include"board.h"
#include"gametime.h"
#include"tetromino.h"
#include"minos.h"
#include"OnePlay.h"
#include"TwoPlay.h"
using namespace std;
TwoPlay::TwoPlay():OnePlay(),KO(0),KO2(0),row2(0),score2(0),TimeLimit(180)
{
}
int TwoPlay::getScore_2()
{
	return score2;
}

int TwoPlay::getRow_2()
{
	return row2;
}

void TwoPlay::exucate()
{
	top_panel(panel[2]);
	update_panels();
	doupdate();
	row=0;row2=0;score=0;score2=0;
	box(win[2],0,0);
	setborder(3,4,6,10);setborder(3,55,6,10);
	setborder(6,15,22,22);setborder(6,65,22,22);
	setborder(3,39,6,10);setborder(3,88,6,10);
	setborder(17,1,14,13);setborder(17,51,14,13);
	int hold=0,hold_time=1,hold2=0,hold_time2=1,check1,check2;
	int height,width,enter,go_on=TRUE,create=1,stop=0,mv,mv2,create2=1,stop2=0,cleanrows=0,cleanrows2=0;
	float u=1,v=1;level=startlevel;level2=startlevel;KO=0;KO2=0;
	vector<int> clean;
	clock.setTime();
	printTime();
	PlayBoard.SetAll(0);PlayBoard2.SetAll(0);
	nextmino=CreateMino(PlayBoard);	nextmino2=CreateMino(PlayBoard2);
	mvwprintw(win[2],20,2,"score:");mvwprintw(win[2],20,52,"score:");
	mvwprintw(win[2],21,2,"%10d",score2);mvwprintw(win[2],21,52,"%10d",score);
	mvwprintw(win[2],22,2,"lines:%4d",row2);mvwprintw(win[2],22,52,"lines:%4d",row);
	printHelp(23,52,0);printHelp(23,2,1);
	mvwprintw(win[2],18,2,"KO:%4d",KO2);mvwprintw(win[2],18,52,"KO:%4d",KO);
	mvwprintw(win[2],5,25,"2P");mvwprintw(win[2],5,74,"1P");
	mvwprintw(win[2],19,2,"level:%3d",level2);mvwprintw(win[2],19,52,"level:%3d",level);
	mvwprintw(win[2],4,6,"hold");mvwprintw(win[2],4,57,"hold");
	while(go_on)
	{	
		if(create==1)
		{
			hold_time=1;
			mino=nextmino;
			nextmino=CreateMino(PlayBoard);
			printMino(4,89,"next",nextmino);
			wrefresh(win[2]);
			create=0;
			check1=mino->create();
			if(check1==0&&PlayBoard.getNullNum()!=0)
			{
				--PlayBoard;
				++KO2;
				mvwprintw(win[2],18,2,"KO:%4d",KO2);
				check1=mino->create();
			}
			if(check1==0&&PlayBoard.getNullNum()==0)
			{
				delete mino;
				result=pause("2P WiN    ",1);
				go_on=FALSE;
				break;
			}		
		}
		if(create2==1)
		{
			hold_time2=1;
			mino2=nextmino2;
			nextmino2=CreateMino(PlayBoard2);
			printMino(4,40,"next",nextmino2);
			wrefresh(win[2]);
			create2=0;
			check2=mino2->create();
			if(check2==0&&PlayBoard2.getNullNum()!=0)
			{
				--PlayBoard2;
				++KO;
				mvwprintw(win[2],18,52,"KO:%4d",KO);
				check2=mino2->create();
			}
			if(check2==0&&PlayBoard2.getNullNum()==0)
			{
				delete mino2;
				result=pause("1P WIN    ",1);
				go_on=FALSE;
				break;
			}

		}
		if(cleanrows!=0)
		{
			mino2->addRow(cleanrows);
			cleanrows=0;
		}
		if(cleanrows2!=0)
		{
			mino->addRow(cleanrows2);
			cleanrows2=0;
		}
		while((enter=wgetch(win[2]))==ERR)
		{
			clock.time_pass();
			printTime();
			if(clock.getTime()==TimeLimit)
			{
				go_on=FALSE;
				result=gameover();
				break;
		    }
			mv=mino->move(u/speeds[level-1],0);	
			mv2=mino2->move(v/speeds[level-1],0);
			PrintBoard(7,66,PlayBoard);
			PrintBoard(7,16,PlayBoard2);
			wrefresh(win[2]);
			if(mv==0)
			{
				stop=1;break;
			}
			if(mv2==0)
			{
				stop2=1;break;
			}
			u=1;v=1;
		}
		if(enter=='p')
		{ 
			result=pause("PAUSE",0);
			if(result==0)clock.time_continue();
			else {go_on=FALSE;}
		}
		if(stop==0)
		{
			switch(enter)
			{
				case KEY_UP:
				{
					mino->turn();
					PrintBoard(7,66,PlayBoard);
					wrefresh(win[2]);
					break;
				}
				case KEY_DOWN:{u=speeds[level-1];break;}
				case KEY_RIGHT:
				{
					mino->move(0,1);
					PrintBoard(7,66,PlayBoard);
					wrefresh(win[2]);
					break;
				}
				case KEY_LEFT:
				{
					mino->move(0,-1);
					PrintBoard(7,66,PlayBoard);
					wrefresh(win[2]);
					break;
				}
				case '/':
				{
					mino->drop();
					PrintBoard(7,66,PlayBoard);
					wrefresh(win[2]);
					break;
				}						
				case '.':
				{
					if(hold_time==0)break;
					else if(hold==0)
					{
						hold=mino->hold();
						printMino(4,56,"hold",mino);
						delete mino;
						wrefresh(win[2]);
						create=1;
						--hold_time;
					}
					else if(hold!=0)
					{
						int tmp;
						tmp=hold;
						hold=mino->hold();			
						printMino(4,56,"hold",mino);
						delete mino;
						mino=CreateMino(PlayBoard,tmp);
						mino->create();
						--hold_time;
					}
					break;		
				}
				default:break;
			}
		}
		if(stop2==0)
		{
			switch(enter)
			{
				case 'w':
				{
					mino2->turn();
					PrintBoard(7,16,PlayBoard2);
					wrefresh(win[2]);
					break;
				}
				case 's':{v=speeds[level-1];break;}
				case 'd':
				{
					mino2->move(0,1);
					PrintBoard(7,16,PlayBoard2);
					wrefresh(win[2]);
					break;
				}
				case 'a':
				{
					mino2->move(0,-1);
					PrintBoard(7,16,PlayBoard2);
					wrefresh(win[2]);
					break;
				}
				case 'c':
				{
					mino2->drop();
					PrintBoard(7,16,PlayBoard2);
					wrefresh(win[2]);
					break;
				}						
				case 'v':
				{
					if(hold_time2==0)break;
					else if(hold2==0)
					{
						hold2=mino2->hold();
						printMino(4,5,"hold",mino2);
						delete mino2;
						wrefresh(win[2]);
						create2=1;
						--hold_time2;
					}
					else if(hold2!=0)
					{
						int tmp;
						tmp=hold2;
						hold2=mino2->hold();			
						printMino(4,5,"hold",mino2);
						delete mino2;
						mino2=CreateMino(PlayBoard2,tmp);
						mino2->create();
						--hold_time2;
					}
					break;		
				}
				default:break;
			}
			
		}
		if(stop==1)
		{
			stop=0;
			create=1;
			score+=calculateScore(level,mino);
			mvwprintw(win[2],21,52,"%10d",score);
			delete mino;
			clean=PlayBoard.check();
			if(!clean.empty())
			{
				PlayBoard-=clean;
				row+=clean.size();
				score+=calculateScore(level,clean.size());
				if(level<speeds.size()&&(level-startlevel)!=row/10)++level;
				cleanrows=clean.size();
			}
			mvwprintw(win[2],19,52,"level:%3d",level);
			mvwprintw(win[2],21,52,"%10d",score);
			mvwprintw(win[2],22,52,"lines:%4d",row);
			PrintBoard(7,66,PlayBoard);
			wrefresh(win[2]);
		}
		if(stop2==1)
		{
			stop2=0;
			create2=1;
			score2+=calculateScore(level2,mino2);
			mvwprintw(win[2],21,2,"%10d",score2);
			delete mino2;
			clean=PlayBoard2.check();
			if(!clean.empty())
			{
				PlayBoard2-=clean;
				row2+=clean.size();
				score2+=calculateScore(level2,clean.size());
				if(level2<speeds.size()&&(level2-startlevel)!=row2/10)++level2;
				cleanrows2=clean.size();
			}
			mvwprintw(win[2],19,2,"level:%3d",level2);
			mvwprintw(win[2],21,2,"%10d",score2);
			mvwprintw(win[2],22,2,"lines:%4d",row2);
			PrintBoard(7,16,PlayBoard2);
			wrefresh(win[2]);
		}       
	}
	werase(win[2]);
}




void TwoPlay::printHelp(int starty,int startx,int mode)
{
	if(mode==0){OnePlay::printHelp(starty,startx);}
	else if(mode==1)
	{
		mvwprintw(win[2],starty,startx,"d:right");
		mvwprintw(win[2],starty+1,startx,"a:left");
		mvwprintw(win[2],starty+2,startx,"s:accerate");
		mvwprintw(win[2],starty+3,startx,"w:turn");
		mvwprintw(win[2],starty+4,startx,"c:drop");
		mvwprintw(win[2],starty+5,startx,"v:hold");
		mvwprintw(win[2],starty+6,startx,"p:pause");
	}
}

int TwoPlay::gameover()
{
	int r,re;
	if(KO>KO2)r=1;
	else if(KO<KO2)r=2;
	else if(KO==KO2&&score2>score)r=2;
	else if(KO==KO2&&score2<score)r=1;
	else if(KO==KO2&&score2==score)r=3;
	switch(r)
	{
		case 1:{re=pause("1P WIN     ",1);break;}
		case 2:{re=pause("2P WIN     ",1);break;}
		case 3:{re=pause("DRAW !!!!  ",1);break;}
		default:break;
	}
	return re;
}

void TwoPlay::printTime()
{
	int t=TimeLimit-clock.getTime();
	int hr=t/3600;
	int mi=(t%3600)/60;
	int sc=t%60;
	mvwprintw(win[2],2,40,"%2d:%2d:%2d",hr,mi,sc);
}
void TwoPlay::setTimeLimit(int t)
{
	TimeLimit=t;
}
