#ifndef PLAYER_H
#define PLAYER_H
#include <Engine.h>

class player
{
	public:
		float X;
		float Y;
		float L;
		float A;
		SDL_Rect boxArea;
		SpriteGame sprites[999];
		player(float x,float  y ,float l,float a);
		void setPosition(float x,float y);


	private:

};

#endif // PLAYER_H
