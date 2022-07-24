#include"minos.h"
#include"tetromino.h"
#include"board.h"
#include<iostream>
#include"ncursesw/ncurses.h"
#include<vector>


mino_O::mino_O(board &GameBoard):tetromino(GameBoard,1)
{
	mino[0][1]=1;
	mino[0][2]=1;
	mino[1][1]=1;
	mino[1][2]=1;
}

void mino_O::turn()
{
	return;
}


mino_I::mino_I(board &GameBoard):tetromino(GameBoard,2)
{
	for(int j=0;j<4;++j)
	{
		mino[0][j]=2;	
	}
}

void mino_I::turn()
{
	int dataX,y,x;
	double dataY;
	cleanMino();
	dataY=positionY;dataX=positionX;
	switch(type)
	{
		case 0:
		{
			int i;
			for(i=0;i<3;++i)
			{
				y=dataY+i;x=dataX;
				if(MinoBoard.GetGrid(y,x)!=0||y>=22)break;
			}
			dataY-=(3-i);
			for(int j=0;j<4;++j){mino[0][j]=0;}
			for(int j=0;j<4;++j){mino[j][1]=2;}
			break;
		}
		case 1:
		{
			int i;
			for(i=-1;i<3;++i)
			{
				y=dataY-1;x=dataX+i;
				if(x<0||x>9)break;
				else if(MinoBoard.GetGrid(y,x)!=0)break;
			}
			dataX-=(i>0?3-i:i);
			for(int j=0;j<4;++j){mino[j][1]=0;}
			for(int j=0;j<4;++j){mino[0][j]=2;}
			break;
		}
		default:break;
	}
	if(turncheck(dataY,dataX)!=0)
	{   
		positionY=dataY;
		positionX=dataX;
		type++;type=(type>1?0:type);
	}
	else
	{
		switch(type)
		{
			case 0:
			for(int j=0;j<4;++j)mino[j][1]=0;
			for(int j=0;j<4;++j)mino[0][j]=2;
			break;
			case 1:
			for(int j=0;j<4;++j)mino[0][j]=0;
            for(int j=0;j<4;++j)mino[j][1]=2;
		}
	}
	putMino();
}

mino_T::mino_T(board &GameBoard):tetromino(GameBoard,3)
{
	mino[0][1]=3;
	mino[1][0]=3;
	mino[1][1]=3;
	mino[1][2]=3;
}

void mino_T::turn()
{
	int dataX,y,x;
	double dataY;
	cleanMino();
	dataY=positionY;dataX=positionX;
	switch(type)
	{
		case 0:
		{
			y=dataY+1;x=dataX;
			if(y>=22||MinoBoard.GetGrid(y,x)!=0){dataY-=1.00;}break;
		}
		case 1:
		{
			y=dataY;x=dataX-1;
			if(x<0){dataX+=1;}
			else if(MinoBoard.GetGrid(y,x)!=0){dataX+=1;}break;
		}
		case 3:
		{
			y=dataY;x=dataX+1;
			if(x>9){dataX-=1;}
			else if(MinoBoard.GetGrid(y,x)!=0){dataX-=1;}break;
		}
		default: break;
	}
	clockwise(3);
	if(turncheck(dataY,dataX)==1)
	{	
		positionY=dataY;
		positionX=dataX;
		type++;type=(type>=4?0:type);
	}
	else counterclockwise(3);
	putMino();
}

mino_S::mino_S(board &GameBoard):tetromino(GameBoard,4)
{
	mino[0][1]=4;
	mino[0][2]=4;
	mino[1][0]=4;
	mino[1][1]=4;
}

void mino_S::turn()
{
	int dataX,y,x,y2,x2;
	double dataY;
	cleanMino();
	dataY=positionY;dataX=positionX;
	switch(type)
	{
		case 0:
		{
			y=dataY+1;x=dataX;
			if(y>=22){dataY-=1.00;}
			else if(MinoBoard.GetGrid(y,x)!=0){dataY-=1.00;}
			break;
		}
		case 1:
		{
			y=dataY+1;x=dataX-1;y2=dataY;x2=dataX+1;
			if(MinoBoard.GetGrid(y,x)!=0)dataY-=1.00;
			if(x2>9){dataX-=1;}
			else if(MinoBoard.GetGrid(y2,x2)!=0){dataX-=1;}
			break;				
		}
		case 2:
		{
			y=dataY+1;x=dataX+1;
			if(MinoBoard.GetGrid(y,x)!=0)dataX-=1;break;
		}
		case 3:
		{
			y=dataY;x=dataX-1;
			if(x<0||MinoBoard.GetGrid(y,x)!=0)dataX+=1;break;
		}
		default:break;
	}
	counterclockwise(3);
	if(turncheck(dataY,dataX)==1)
	{   
		positionY=dataY;
		positionX=dataX;
		type++;type=(type>=4?0:type);
	}
	else clockwise(3);
	putMino();
}
mino_Z::mino_Z(board &GameBoard):tetromino(GameBoard,5)
{
	mino[0][0]=5;
	mino[0][1]=5;
	mino[1][1]=5;
	mino[1][2]=5;
}
void mino_Z::turn()
{
	int dataX,y,x,y2,x2;
	double dataY;
	cleanMino();
	dataY=positionY;dataX=positionX;
	switch(type)
	{
		case 0:
		{
			y=dataY+1;x=dataX;                                                                                                                          
			if(y>=22){dataY-=1.00;}
			else if(MinoBoard.GetGrid(y,x)!=0){dataY-=1.00;}
			break;
		}
		case 1:
		{
			y=dataY+1;x=dataX+1;y2=dataY;x2=dataX-1;
			if(MinoBoard.GetGrid(y,x)!=0)dataY-=1.00;
			if(x2<0){dataX+=1;}
			else if(MinoBoard.GetGrid(y2,x2)!=0){dataX+=1;}
			break;
		}
		case 2:
		{
			y=dataY+1;x=dataX-1;
			if(MinoBoard.GetGrid(y,x)!=0)dataX+=1;break;
		}
		case 3:
		{
			y=dataY;x=dataX+1;
			if(x>9||MinoBoard.GetGrid(y,x)!=0)dataX-=1;break;
		}
		default:break;
	}
	clockwise(3);
	if(turncheck(dataY,dataX)==1)
	{   
		positionY=dataY;
		positionX=dataX;
		type++;type=(type>=4?0:type);
	}
	else counterclockwise(3);
	putMino();
}


mino_L::mino_L(board &GameBoard):tetromino(GameBoard,6)
{
	mino[1][0]=6;
	mino[1][1]=6;
	mino[1][2]=6;
	mino[0][2]=6;
}

void mino_L::turn()
{
	int dataX,y,x,y2,x2,y3,x3;
	double dataY;
    cleanMino();
	dataY=positionY;dataX=positionX;
	switch(type)
	{
		case 0:
		{
			y=dataY+1;x=dataX;
			if(y>=22)dataY-=1.00;
			else if(MinoBoard.GetGrid(y,x)!=0)dataX-=1.00;
			break;
		}
		case 1:
		{
			y=dataY;x=dataX+1;y2=dataY;x2=dataX-1;y3=dataY+1;x3=dataX-1;
			if(x>9)dataX-=1;
			else if(MinoBoard.GetGrid(y,x)!=0)dataX-=1;
			else if(MinoBoard.GetGrid(y2,x2)!=0)dataX+=1;
			else if(MinoBoard.GetGrid(y3,x3)!=0)dataY-=1.00;
			break;
		}
		case 2:
		{
			y=dataY+1;x=dataX;y2=dataY+1;x2=dataX+1;
			if(MinoBoard.GetGrid(y,x)!=0)dataY-=1.00;
			else if(MinoBoard.GetGrid(y2,x2)!=0)dataX-=1;

			break;
		}
		case 3:
		{
			y=dataY;x=dataX-1;
			if(x<0||MinoBoard.GetGrid(y,x)!=0)dataX++;
			break;
		}
		default:break;
	}
	counterclockwise(3);
	if(turncheck(dataY,dataX)==1)
	{   
		positionY=dataY;
		positionX=dataX;
		type++;type=(type>=4?0:type);
	}
	else clockwise(3);
	putMino();
}

mino_J::mino_J(board &GameBoard):tetromino(GameBoard,7)
{
	mino[0][0]=7;
	mino[1][0]=7;
	mino[1][1]=7;
	mino[1][2]=7;
}

void mino_J::turn()
{
    int dataX,y,x,y2,x2,y3,x3;
	double dataY;
	cleanMino();
	dataY=positionY;dataX=positionX;
	switch(type)
	{
		case 0:
		{
			y=dataY+1;x=dataX;
			if(y>=22)dataY-=1.00;
			else if(MinoBoard.GetGrid(y,x)!=0)dataY-=1.00;
			break;
		}
		case 1:
		{
			y=dataY;x=dataX-1;y2=dataY;x2=dataX+1;y3=dataY+1;x3=dataX+1;
			if(x<0)dataX+=1;
			else if(MinoBoard.GetGrid(y,x)!=0)dataX+=1;
			else if(MinoBoard.GetGrid(y2,x2)!=0)dataX-=1;
			else if(MinoBoard.GetGrid(y3,x3)!=0)dataY-=1.00;
			break;
		}
		case 2:
		{
			y=dataY+1;x=dataX;y2=dataY+1;x2=dataX-1;
			if(MinoBoard.GetGrid(y,x)!=0)dataY-=1.00;
			else if(MinoBoard.GetGrid(y2,x2)!=0)dataX+=1;
			break;
		}
		case 3:
		{
			y=dataY;x=dataX+1;
			if(x>9||MinoBoard.GetGrid(y,x)!=0)dataX-=1;
			break;
		}
		default:break;
	}
	clockwise(3);
	if(turncheck(dataY,dataX)==1)
	{   
		positionY=dataY;
		positionX=dataX;
		type++;type=(type>=4?0:type);
	}
	else counterclockwise(3);
	putMino();
}
