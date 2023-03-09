#include "player.h"

player::player(float x, float y, float l, float a)
{
	X = x;
	Y = y;
	L = l;
	A = a;
	boxArea = {X,Y,L,A};
}
void player::setPosition(float x,float y)
{
	X = x;
	Y = y;
}
