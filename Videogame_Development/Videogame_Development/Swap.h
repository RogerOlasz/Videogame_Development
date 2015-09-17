#ifndef __Swap_H__
#define __Swap_H__

template<class TYPE_VAR>

void Swap(TYPE_VAR& a, TYPE_VAR& b)
{
	TYPE_VAR tmp;
	tmp = a;
	a = b;
	b = tmp;
}

#endif //__Swap_H__
