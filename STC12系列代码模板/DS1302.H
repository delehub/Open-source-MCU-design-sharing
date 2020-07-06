#ifndef __DS1302_H__
#define __DS1302_H__
typedef struct S_TIME
	{
		unsigned char SEC;			//00~59
		unsigned char MIN;			//00~59
		unsigned char HR;			//00-23
		unsigned char DATE;			//00-31
		unsigned char MONTH;		//01-12
		unsigned char DAY;			//01-07
		unsigned char YEAR;			//00-99
	}S_TIME;
extern S_TIME TIME; 
void InitDS1302(void);
void GetDS1302_TIME(void);
void GetDS1302_DATE(void);
void SetDS1302_TIME(void);
void SetDS1302_DATE(void);


#endif