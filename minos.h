#ifndef MINOS_H
#define MINOS_H
#include<iostream>
#include<vector>
#include"board.h"
#include"tetromino.h"

using namespace std;

class mino_O:public tetromino
{
	public:
	mino_O(board &);
	virtual void turn();
};

class mino_I:public tetromino
{
	public:
	mino_I(board &);
	virtual void turn();
};

class mino_T:public tetromino
{
	public:
	mino_T(board &);
	virtual void turn();
};

class mino_S:public tetromino
{
	public:
	mino_S(board &);
	virtual void turn();
};

class mino_Z:public tetromino
{
	public:
	mino_Z(board &);
	virtual void turn();
};

class mino_L:public tetromino
{
	public:
	mino_L(board &);
	virtual void turn();
};

class mino_J:public tetromino
{
	public:
	mino_J(board &);
	virtual void turn();
};
#endif
