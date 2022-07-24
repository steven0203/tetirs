#include"SETTING.h"
#include"OnePlay.h"
#include"TwoPlay.h"



int main()
{
	SETTING menu(10,3600);
	OnePlay game1;
	TwoPlay game2;
	vector<int> speed(10);
	speed[0]=8000;speed[1]=6500;
	speed[2]=5000;speed[3]=3500;
	speed[4]=2000;speed[5]=1500;
	speed[6]=1000;speed[7]=750;
	speed[8]=500;speed[9]=250;
	game1.setSpeeds(speed);
	game2.setSpeeds(speed);
	while(menu.getChoise()!=2)
	{
		menu.exucate();
		if(menu.getChoise()==0)
		{
			game1.setStartLevel(menu.getLevel());
			game1.exucate();
			while(game1.getResult()==1)game1.exucate();
		}
		else if(menu.getChoise()==1)
		{
			game2.setStartLevel(menu.getLevel());
			game2.setTimeLimit(menu.get2PTime());
			game2.exucate();
			while(game2.getResult()==1)game2.exucate();
		}
		if(game1.getResult()==3||game2.getResult()==3)break;
	}
 	return 0;
}
