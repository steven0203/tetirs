#include<ctime>
#include"gametime.h"

gametime::gametime()
{
	setTime();
}

void gametime::setTime()
{
	StartTime=time(NULL);
	NowTime=StartTime;
	Time=NowTime-StartTime;
	time_record();
}

void gametime::time_pass()
{
	NowTime=time(NULL);
	Time=NowTime-StartTime;
	time_record();
}

int gametime::gethr()
{
	return now_hour;
}

int gametime::getmi()
{
	return now_minute;
}

int gametime::getsc()
{
	return now_second;
}

void gametime::time_record()
{
	now_hour=(int)Time/3600;
	now_minute=(int)((Time%3600)/60);
	now_second=(int)(Time%60);
}

void gametime::time_continue()
{
	NowTime=time(NULL);
	StartTime=NowTime-Time;
}

int gametime::getTime()
{
	return NowTime-StartTime;
}
