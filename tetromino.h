#ifndef TETROMINO_H
#define TETROMINO_H

#include"board.h"
#include<vector>
using namespace std;

class tetromino
{
	public:
		tetromino(board &,int);
		virtual void turn()=0; 
		int move(double,int);//Return 1 means it's no problem on moving.0  means it can move anymore.
		int create();//Return 0 means it can't create new mino.Return 1 means it's ok to create new mino.
		int getShape();
		int hold();
		void drop();
		void addRow(int);
	protected:
		int mino[4][4];
		board &MinoBoard;
		int positionX;
		double positionY;
		int shape;//1:o,2:I,3:T,4:S,5:Z,6:L,7:J
		int type;
		int MovecheckX(int ,vector<int>,vector<double>);//0 means it can't move,1 means it can move
		int MovecheckY(double,vector<int> ,vector<double>);//0 means it can't move,1 means it can move
		int turncheck(double,int);
		void cleanMino();
		void putMino();
		void clockwise(int);
		void counterclockwise(int);
};

#endif 
