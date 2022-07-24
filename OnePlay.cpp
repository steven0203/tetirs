#include<cstdlib>
#include"OnePlay.h"
#include<clocale>
#include<ctime>
#include"board.h"
#include"tetromino.h"
#include"minos.h"
#include"ncursesw/ncurses.h"
#include"gametime.h"

using namespace std;
OnePlay::OnePlay():startlevel(1),score(0),PlayBoard(),row(0),result(0)
{
	srand(time(NULL));
	curs_set(0);
	win[0]=newwin(14,41,14,27);
	win[1]=newwin(14,41,14,29);
	win[2]=newwin(36,100,3,3);
	for(int i=0;i<3;++i)panel[i]=new_panel(win[i]);
	update_panels();
	doupdate();
	speeds.push_back(10000);speeds.push_back(5000);speeds.push_back(2500);speeds.push_back(1250);speeds.push_back(2500);	
	nodelay(win[2],TRUE);nodelay(win[1],TRUE);nodelay(win[0],TRUE);
	keypad(win[2],TRUE);keypad(win[1],TRUE);keypad(win[0],TRUE);
}



void OnePlay::exucate()
{
	top_panel(panel[2]);
	update_panels();
	doupdate();
	row=0;
	score=0;
	box(win[2],0,0);
	setborder(3,28,6,10);
	setborder(6,39,22,22);
	setborder(3,62,6,10);
	setborder(18,25,13,13);
	int hold=0,hold_time=1;
	int height,width,enter,go_on=TRUE,create=1,stop=0,mv;
	float u=1;level=startlevel;
	vector<int> clean;
	clock.setTime();
	printTime();
	PlayBoard.SetAll(0);
	nextmino=CreateMino(PlayBoard);
	mvwprintw(win[2],20,26,"score:");
	mvwprintw(win[2],21,26,"%10d",score);
	mvwprintw(win[2],22,26,"lines:%4d",row);
	printHelp(23,26);
	mvwprintw(win[2],19,26,"level:%3d",level);
	mvwprintw(win[2],4,30,"hold");
	while(go_on)
	{	
		if(create==1)
		{
			hold_time=1;
			mino=nextmino;
			nextmino=CreateMino(PlayBoard);
			printMino(4,63,"next",nextmino);
			wrefresh(win[2]);
			create=0;
			if(mino->create()==0)
			{
				delete mino;
				result=pause("GAMEOVER",1);
				go_on=FALSE;
				break;
			}
		}
		while((enter=wgetch(win[2]))==ERR)
		{
			clock.time_pass();
			printTime();
			mv=mino->move(u/speeds[level-1],0);	
			PrintBoard(7,40,PlayBoard);
			wrefresh(win[2]);
			if(mv==0)
			{
				stop=1;break;
			}
			u=1;
		}
		if(enter=='p')
		{
			result=pause("PAUSE",0);
			if(result==0){clock.time_continue();}
			else {go_on=FALSE;}
		}
		if(stop==0)
		{
			switch(enter)
			{
				case KEY_UP:
				{
					mino->turn();
					PrintBoard(7,40,PlayBoard);
					wrefresh(win[2]);
					break;
				}
				case KEY_DOWN:{u=speeds[level-1];break;}
				case KEY_RIGHT:
				{
					mino->move(0,1);
					PrintBoard(7,40,PlayBoard);
					wrefresh(win[2]);
					break;
				}
				case KEY_LEFT:
				{
					mino->move(0,-1);
					PrintBoard(7,40,PlayBoard);
					wrefresh(win[2]);
					break;
				}
				case '/':
				{
					mino->drop();
					PrintBoard(7,40,PlayBoard);
					wrefresh(win[2]);
					break;
				}
				case '.':
				{
					if(hold_time==0)break;
					else if(hold==0)
					{
						hold=mino->hold();
						printMino(4,29,"hold",mino);
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
						printMino(4,29,"hold",mino);
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
		if(stop==1)
		{
			stop=0;
			create=1;
			score+=calculateScore(level,mino);
			mvwprintw(win[2],21,26,"%10d",score);
			delete mino;
			clean=PlayBoard.check();
			if(!clean.empty())
			{
				PlayBoard-=clean;
				row+=clean.size();
				score+=calculateScore(level,clean.size());
				if(level<speeds.size()&&(level-startlevel)!=row/10)++level;
			}
			mvwprintw(win[2],19,26,"level:%3d",level);
			mvwprintw(win[2],21,26,"%10d",score);
			mvwprintw(win[2],22,26,"lines:%4d",row);
			PrintBoard(7,40,PlayBoard);
			wrefresh(win[2]);
		}       
	}
	werase(win[2]);
}

void OnePlay::PrintBoard(int starty,int startx,board &b)
{
	int color;
	for(int i=2;i<22;++i)
	{
		for(int j=0;j<10;++j)
		{
			color=b.GetGrid(i,j);
			if(b.GetGrid(i,j)==8)mvwprintw(win[2],i-2+starty,2*j+startx,"田");
			else if(b.GetGrid(i,j)!=0)
			{
				wattron(win[2],COLOR_PAIR(color));
				mvwprintw(win[2],i-2+starty,2*j+startx,"回");
				wattroff(win[2],COLOR_PAIR(color));
			}
			else if(b.GetGrid(i,j)==0)mvwprintw(win[2],i-2+starty,2*j+startx,"  ");
		} 
	}
}

tetromino *OnePlay::CreateMino(board &b,int shape)
{
	int choise=rand()%7;
	if(shape!=0)choise=shape-1;
	tetromino *mino;
	switch(choise)
	{
		case 0:mino=new mino_O(b);break;
		case 1:mino=new mino_I(b);break;
		case 2:mino=new mino_T(b);break;
		case 3:mino=new mino_S(b);break;
		case 4:mino=new mino_Z(b);break;
		case 5:mino=new mino_L(b);break;
		case 6:mino=new mino_J(b);break;
	}
	return mino;
}

void OnePlay::setborder(int starty,int startx,int height,int width)
{
	mvwaddch(win[2],starty,startx,ACS_ULCORNER);
	mvwaddch(win[2],starty,startx+width-1,ACS_URCORNER);
	mvwaddch(win[2],starty+height-1,startx,ACS_LLCORNER);
	mvwaddch(win[2],starty+height-1,startx+width-1,ACS_LRCORNER);
	mvwhline(win[2],starty,startx+1,ACS_HLINE,width-2);
	mvwhline(win[2],starty+height-1,startx+1,ACS_HLINE,width-2);
	mvwvline(win[2],starty+1,startx,ACS_VLINE,height-2);
	mvwvline(win[2],starty+1,startx+width-1,ACS_VLINE,height-2);
}
int OnePlay::calculateScore(int L,tetromino *item)
{
	int shape=item->getShape(),score;
	switch(shape)
	{
		case 1:score=L*13;break;
		case 2:score=L*14;break;
		case 3:score=L*15;break;
		case 4:score=L*16;break;
		case 5:score=L*16;break;
		case 6:score=L*17;break;
		case 7:score=L*17;break;
		default:score=0;break;
	}
	return score;
}

int OnePlay::calculateScore(int L,int lines)
{
	return L*(lines*50*(1+lines*0.2));
}

void OnePlay::printTime()
{
	int hr=clock.gethr();
	int mi=clock.getmi();
	int sc=clock.getsc();
	mvwprintw(win[2],2,40,"TIME: %3d:%2d:%2d",hr,mi,sc);
}

void OnePlay::printMino(int starty,int startx,string label,tetromino *item)
{
	int shape=item->getShape();
	mvwprintw(win[2],starty,startx+1,"%s",label.c_str());
	wattron(win[2],COLOR_PAIR(shape));
	switch(shape)
	{
		case 1:
		{
			mvwprintw(win[2],starty+1,startx,"  回回  ");
			mvwprintw(win[2],starty+2,startx,"  回回  ");
			mvwprintw(win[2],starty+3,startx,"        ");
			break;
		}
		case 2:
		{
			mvwprintw(win[2],starty+1,startx,"回回回回");
			mvwprintw(win[2],starty+2,startx,"        ");
			mvwprintw(win[2],starty+3,startx,"        ");
			break;
		}
		case 3:
		{
			mvwprintw(win[2],starty+1,startx,"    回  ");
			mvwprintw(win[2],starty+2,startx,"  回回回");
			mvwprintw(win[2],starty+3,startx,"        ");
			break;
		}
		case 4:
		{
			mvwprintw(win[2],starty+1,startx,"    回回");
			mvwprintw(win[2],starty+2,startx,"  回回  ");
			mvwprintw(win[2],starty+3,startx,"        ");
			break;
		}
		case 5:
		{
			mvwprintw(win[2],starty+1,startx,"  回回  ");
			mvwprintw(win[2],starty+2,startx,"    回回");
			mvwprintw(win[2],starty+3,startx,"        ");
			break;
		}
		case 6:
		{
			mvwprintw(win[2],starty+1,startx,"      回");
			mvwprintw(win[2],starty+2,startx,"  回回回");
			mvwprintw(win[2],starty+3,startx,"        ");
			break;
		}
		case 7:
		{
			mvwprintw(win[2],starty+1,startx,"  回    ");
			mvwprintw(win[2],starty+2,startx,"  回回回");
			mvwprintw(win[2],starty+3,startx,"        ");
			break;
		}
		default:break;
	}
	wattroff(win[2],COLOR_PAIR(shape));
}
void OnePlay::printHelp(int starty,int startx)
{
	mvwaddch(win[2],starty,startx,ACS_RARROW);mvwprintw(win[2],starty,startx+1,":right");
	mvwaddch(win[2],starty+1,startx,ACS_LARROW);mvwprintw(win[2],starty+1,startx+1,":left");
	mvwaddch(win[2],starty+2,startx,ACS_DARROW);mvwprintw(win[2],starty+2,startx+1,":accerate");
	mvwaddch(win[2],starty+3,startx,ACS_UARROW);mvwprintw(win[2],starty+3,startx+1,":turn");
	mvwprintw(win[2],starty+4,startx,"/:drop");
	mvwprintw(win[2],starty+5,startx,".:hold");
	mvwprintw(win[2],starty+6,startx,"p:pause");
}

int OnePlay::pause(string condition,int con)
{
	top_panel(panel[2]);
	int go_on=TRUE;
	int choose=0,enter,ch,choise_num;
	string choise[4];
	choise[0]=". RESUME";
	choise[1]=". AGAIN";
	choise[2]=". BACK TO MENU";
	choise[3]=". EXIT";
	if(con!=0&&con!=1)return 0;
	box(win[con],0,0);
	top_panel(panel[con]);
	update_panels();
	doupdate();
	wattron(win[con],COLOR_PAIR(1));
	mvwprintw(win[con],1,15,"%s",condition.c_str());
	wattroff(win[con],COLOR_PAIR(1));
	while(go_on)
	{
		for(int i=0;i<4-con;++i)
		{
			if(i==choose)wattron(win[con],A_REVERSE);
			mvwprintw(win[con],3+2*i,16,"%d%s",i+1,choise[i+con].c_str());
			if(i==choose)wattroff(win[con],A_REVERSE);
		}
		wrefresh(win[con]);
		enter=wgetch(win[con]);
		switch(enter)
		{
			case KEY_UP:choose-=1;choose=choose<0?choose+=(4-con):choose;break;
			case KEY_DOWN:choose+=1;choose=choose>=4-con?choose-=(4-con):choose;break;
			case '\n':go_on=FALSE;
			default:break;
		}
	}
	top_panel(panel[2]);
	update_panels();
	doupdate();
	werase(win[con]);
	return choose+con;
}
int OnePlay::getResult()
{
	return result;
}

void OnePlay::setSpeeds(vector<int> s)
{
	speeds=s;
}


void OnePlay::setStartLevel(int l)
{
	startlevel=l;
}
