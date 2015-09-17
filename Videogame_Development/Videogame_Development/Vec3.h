#ifndef __Vec3_H__
#define __Vec3_H__

#include <iostream>

template<class TYPE>
class Vec3{

public:
	TYPE z;

	Vec3<TYPE>() 
	{
		z = 0;
	}

	void SetPosition(TYPE posit)
	{
		z = posit;
	}

	int GetPosition()
	{
		return z;
	}

	~Vec3<TYPE>(){ }

};

#endif //__Vec3_H__
