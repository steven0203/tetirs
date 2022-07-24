#include<iostream>
#include<vector>
#include"ncurses.h"
#include"board.h"


using namespace std;


board::board():Nullnum(0)
{
	for(int i=0;i<22;++i)
	{
		for(int j=0;j<10;++j)
		{
			grid[i][j]=0;
		}
	}
}


int board::GetGrid(int y,int x)
{
	return grid[y][x];
}

void board::SetGrid(int y,int x,int num)
{
	grid[y][x]=num;
}


vector<int> board::check()
{
	vector<int> result;
	for(int i=21;i>0;--i)
	{
		for(int j=0;j<10;++j)
		{
			if(grid[i][j]>=8)continue;
			if(grid[i][j]==0)
			{
				break;
			}
			if(j==9)
			{
				result.push_back(i);
			}
		}
	}
	return result;
}

board &board::operator-=(vector<int> rows)
{
	int y;
	if(rows.empty())return *this;
	for(int i=0;i<rows.size();++i)
	{
		y=rows.at(i);
		for(int j=0;j<10;++j)
		{
			grid[y][j]=0;
		}
	}
	for(int i=rows.size()-1;i>=0;--i)
	{
		for(y=rows.at(i);y>0;--y)
		{
			for(int j=0;j<10;++j)
			{
				if(y==0)grid[y][j]=0;
				else
				{
					grid[y][j]=grid[y-1][j];
					grid[y-1][j]=0;
				}
			}
		}
	}
	return *this;
}
void board::add()
{
	int check=0;
	for(int i=0;i<10&&check==0;++i)
	{
		if(grid[0][i]!=0)++check;
	}
	if(check==0)
	{
		for(int j=0;j<10;++j)
		{
			for(int i=0;i<21;++i)
			{
				grid[i][j]=grid[i+1][j];
			}
		}
		for(int j=0;j<10;++j)
		{
			grid[21][j]=8;
		}
	}
	Nullnum++;
}

void board::SetAll(int num)
{
	for(int i=0;i<22;++i)
	{
		for(int j=0;j<10;++j)
		{
			grid[i][j]=num;
		}
	}
	Nullnum=0;
}

int board::getNullNum()
{
	return Nullnum;
}

board &board::operator--()
{
	vector<int> clean;
	for(int i=0;i<Nullnum;++i)
	{
		clean.push_back(21-i);
	}
	(*this)-=clean;
	Nullnum=0;
	return *this;
}

