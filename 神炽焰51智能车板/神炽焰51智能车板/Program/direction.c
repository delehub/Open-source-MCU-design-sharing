#include "direction.h"
sbit AIN1=P2^5;
sbit AIN2=P2^6;
sbit BIN1=P2^4;
sbit BIN2=P2^3;
void Stop(void)
{
	AIN1=0;
	AIN2=0;
	BIN1=0;
	BIN2=0;
}

void Forward(void)
{
	AIN1=1;
	AIN2=0;
	BIN1=1;
	BIN2=0;
}

void Back(void)
{
	AIN1=0;
	AIN2=1;
	BIN1=0;
	BIN2=1;
}

void Right(void)
{
	AIN1=1;
	AIN2=0;
	BIN1=0;
	BIN2=1;
}

void Left(void)
{
	AIN1=0;
	AIN2=1;
	BIN1=1;
	BIN2=0;
}