#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "general.h"

struct Time
{
    unsigned char min;
    unsigned char sec;

    Time(unsigned char m = 0, unsigned char s = 0)
        : min(m), sec(s)
    {}
};

struct ShiftReg
{
	unsigned char id;
	
	ShiftReg(unsigned char i = 0)
		: id(i)
	{}
	
	void SerHigh()
	{
		switch(id)
		{
			case ROW_ID		:	
		}
	}
};

#endif //__STRUCTS_H__