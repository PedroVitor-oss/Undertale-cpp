#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#define maxKey 10

struct colorRGB{
	int r;
	int g;
	int b;

};
struct SpriteGame{
	int x, y,w,h = 0;
};

class Engine
{
	public:
		void Init(std::string title,int w,int h);
		void Update();
		int eventos(int type);
		void Clean(colorRGB color);
		void Quit();
		colorRGB createColorRGB(int m_r,int m_g,int m_b);
		SDL_Texture*  CreateTexture(std::string nameFile);
		void DrawTexture(SDL_Texture* texture,SpriteGame sprite,SDL_Rect boxArea);
		void DrawRect(SDL_Rect box,colorRGB cor);
		SpriteGame createSpriteGame(int x,int y,int w,int h);
		bool ColisionRect(SDL_Rect box1,SDL_Rect box2);
		void AddSave(std::string name,std::string value);
		void SetSave(std::string name,std::string value);
		std::string GetSave(std::string name);
		bool KeyIsPressed(int key);
	protected:

	private:
		SDL_Window* window = NULL;
		SDL_Renderer* screen = NULL;
		int quantKeyPressed = 0;
		int keyInPressed[255] = {0};
		void addKeyPressed(int key);
		void deletKeyPressed(int key);
		void reposicionamento();
		void showArray();
		std::string nameSave = "save/save.txt";
};

#endif // ENGINE_H
