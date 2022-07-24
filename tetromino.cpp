
#include"tetromino.h"
#include"ncursesw/ncurses.h"
#include<vector>
#include"board.h"
using namespace std;


tetromino::tetromino(board &b,int MinoShape):MinoBoard(b),shape(MinoShape),positionX(4),positionY(1.00),type(0)
{
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			mino[i][j]=0;
		}
	}
}

int tetromino::move(double moveY,int moveX)
{
	int y,x,go_y,go_x;
	vector<double> dataY(4);
	vector<int> dataX(4);
	int k=0;
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			if(mino[i][j]!=0)
			{
				dataY[k]=positionY+(i-1);
				dataX[k]=positionX+(j-1);
				y=dataY[k];
				x=dataX[k];
				MinoBoard.SetGrid(y,x,0);
				++k;
			}
		}
	}
	go_y=MovecheckY(moveY,dataX,dataY);go_x=MovecheckX(moveX,dataX,dataY);
  	if(go_y==1&&go_x==1)
	{
		positionY+=moveY;
		positionX+=moveX;
	}
	else if(go_y==1)positionY+=moveY;
	putMino();
	if(go_y==0)return 0;
	else return 1;
}
int tetromino::create()
{
	int correct=1,y,x;
	for(int i=0;i<2&&correct==1;++i)
	{
		for(int j=0;j<10&&correct==1;++j)
		{
			if(MinoBoard.GetGrid(i,j)!=0)--correct;
		}
	}
	if(correct==1)putMino();
	return correct;
}
int tetromino::getShape()
{
	return shape;
}


int tetromino::MovecheckX(int moveX,vector<int> dataX,vector<double> dataY)
{
	int correct=1,x,y;
	for(int i=0;i<4&&correct==1;++i)
	{
		x=dataX[i]+moveX;
		y=dataY[i];
		if(x>9||x<0||MinoBoard.GetGrid(y,x)!=0)--correct;
	}
	return correct;
}

int tetromino::MovecheckY(double moveY,vector<int> dataX,vector<double> dataY)
{
	int correct=1,x;
	double y;
	for(int i=0;i<4&&correct==1;++i)
	{
		y=dataY[i]+moveY;
		x=dataX[i];
		if(y>=22||MinoBoard.GetGrid((int)y,x)!=0)--correct;
	}
	return correct;
}


int tetromino::turncheck(double dataY,int dataX)
{
	int fault=0,x,y;
	for(int i=0;i<4&&fault==0;++i)
	{
		for(int j=0;j<4&&fault==0;++j)
		{
			if(mino[i][j]==0)continue;
			x=dataX+(j-1);
			y=dataY+(i-1);
			if(x>9||y>=22||x<0){++fault; break;}
			if(mino[i][j]!=0&&MinoBoard.GetGrid(y,x)!=0)
			{
				++fault;
			}
		}
	}
	return (fault==0?1:0);
}

void tetromino::clockwise(int range)
{
	int tmp[4][4];
	for(int i=0;i<range;++i)
	{
		for(int j=0;j<range;++j)
		{
			tmp[i][j]=mino[i][j];
		}
	}
	for(int i=0;i<range;++i)
	{
		for(int j=0;j<range;++j)
		{
			mino[i][j]=tmp[range-j-1][i];
		}
	}
}

void tetromino::counterclockwise(int range)
{
	int tmp[4][4];
	for(int i=0;i<range;++i)
	{
		for(int j=0;j<range;++j)
		{
			tmp[i][j]=mino[i][j];
		}
	}
	for(int i=0;i<range;++i)
	{
		for(int j=0;j<range;++j)
		{
			mino[i][j]=tmp[j][range-i-1];
		}
	}
}

void tetromino::cleanMino()
{
	int y,x;
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			if(mino[i][j]!=0)
			{
				y=positionY+(i-1);
				x=positionX+(j-1);
				MinoBoard.SetGrid(y,x,0);
			}
		}
	}
}

void tetromino::putMino()
{
	int y,x;
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			if(mino[i][j]!=0)
			{
				y=positionY+(i-1);
				x=positionX+(j-1);    
				MinoBoard.SetGrid(y,x,shape);
			}
		}
	}
}

void tetromino::drop()
{
	while(move(1,0)!=0);
}
int tetromino::hold()
{
	cleanMino();
	return shape;
}

void tetromino::addRow(int rownum)
{
	int mode=0;
	for(int i=1;i<=rownum;++i)
	{
		if(mode==0)
		{
			cleanMino();
			mode=turncheck(positionY+i,positionX)==0?1:0;
			putMino();
		}
		if(mode==1)				
		{
			if(positionY<2)break;
			MinoBoard.add();
			positionY-=1.00;
		}
		else if(mode==0)
		{
			cleanMino();
			MinoBoard.add();
			putMino();
		}
	}
}
