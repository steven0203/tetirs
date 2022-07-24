#ifndef GAMETIME_H
#define GAMETIME_H
#include<ctime>

class gametime
{
	public:
	gametime();
	void setTime();
	void time_pass();
	void time_continue();
	int gethr();
	int getmi();
	int getsc();
	int getTime();
	private:
	time_t StartTime;
	time_t NowTime;
	int Time;
	int now_hour;
	int now_minute;
	int now_second;
	void time_record();
};
#endif





