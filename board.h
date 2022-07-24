#ifndef BOARD_H
#define BOARD_H
#include<iostream>
#include<vector>


using namespace std;

class board
{
	public:
	board();
	int getNullNum();
	void SetGrid(int,int,int);
	int GetGrid(int,int);
	void add();
	board &operator-=(vector<int>);
	board &operator--();
	vector<int> check();
	void SetAll(int);
	private:
	int grid[22][10];
	int Nullnum;
};



#endif
