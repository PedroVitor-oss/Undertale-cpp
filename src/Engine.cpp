#include "Engine.h"
#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>
using namespace std;
void Engine::Init(std::string t, int w, int h)
{
	if(SDL_Init(SDL_INIT_VIDEO)==0){
		window = SDL_CreateWindow( t.c_str(),SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,w,h,SDL_WINDOW_SHOWN);
		screen = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	}
}
void Engine::Update()
{
SDL_RenderPresent(screen);
}
int Engine::eventos(int type)
{

	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				Engine::Quit();
				return 0;
			break;
			case SDL_KEYDOWN:
					addKeyPressed(event.key.keysym.sym);
					return event.key.keysym.sym;
			break;
			case SDL_KEYUP:
					deletKeyPressed(event.key.keysym.sym);
					reposicionamento();
					return event.key.keysym.sym;
			break;
		}
	}
}
void Engine::Clean(colorRGB color)
{
	SDL_SetRenderDrawColor(screen,color.r,color.g,color.b,SDL_ALPHA_OPAQUE);
	SDL_RenderClear(screen);
	SDL_RenderPresent(screen);
}
void Engine::Quit()
{
	SDL_DestroyWindow(window);
		SDL_Quit();

}
colorRGB Engine::createColorRGB(int m_r, int m_g, int m_b)
{
	return colorRGB({m_r,m_g,m_b});
}
SDL_Texture* Engine::CreateTexture(std::string nameFile)
{
	SDL_Texture* newTexture =NULL;
	SDL_Surface* newImage = SDL_LoadBMP(nameFile.c_str());
	newTexture = SDL_CreateTextureFromSurface(screen, newImage);
	return newTexture;
}
void Engine::DrawTexture(SDL_Texture* texture,SpriteGame sprite,SDL_Rect boxArea)
{
	if(sprite.w!=0&&boxArea.w == 0){
		SDL_Rect boxFrameImg;
		boxFrameImg.h = sprite.h;
		boxFrameImg.w = sprite.w;
		boxFrameImg.x = sprite.x;
		boxFrameImg.y = sprite.y;
		SDL_RenderCopy(screen, texture,&boxFrameImg,NULL);
	}else if(sprite.w!=0&&boxArea.w != 0){
		SDL_Rect boxFrameImg;
		boxFrameImg.h = sprite.h;
		boxFrameImg.w = sprite.w;
		boxFrameImg.x = sprite.x;
		boxFrameImg.y = sprite.y;
		SDL_RenderCopy(screen, texture,&boxFrameImg,&boxArea);

	}else if(sprite.w==0&&boxArea.w != 0){
		SDL_RenderCopy(screen, texture,NULL,&boxArea);
	}else{
		SDL_RenderCopy(screen, texture,NULL,NULL);

	}
}
SpriteGame Engine::createSpriteGame(int x, int y, int w, int h)
{
	return {x,y,w,h};
}
void Engine::DrawRect(SDL_Rect box, colorRGB cor)
{
	SDL_SetRenderDrawColor(screen,cor.r,cor.g,cor.b,SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(screen,&box);
}
bool Engine::ColisionRect(SDL_Rect box1, SDL_Rect box2)
{
	if(box1.x+box1.w>box2.x&&box1.x<box2.x+box2.w&&
	   box1.y+box1.h>box2.y&&box1.y<box2.y+box2.h){
			return true;
	   }else{
			return false;
	   }
}
void Engine::AddSave(std::string name, std::string value)
{
	fstream arquivo;
	arquivo.open(nameSave,ios::app);
	arquivo<<name<<'-'<<value<<"\n";
	arquivo.close();
}
void Engine::SetSave(std::string name, std::string value)
{
	string arquivoAlterado;
	ifstream arquivo;
	arquivo.open(nameSave);
	string line;
	while(getline(arquivo,line)){
		string nameArquive;
		for(int i =0;i<name.length();i++){
			nameArquive+=line[i];
		}
		if(nameArquive == name){
			arquivoAlterado+=name+'-'+value+"\n";
		}else{
			arquivoAlterado+=line+"\n";
		}
	}
	arquivo.close();
	fstream arquivo2;
	arquivo2.open(nameSave);
	arquivo2<<arquivoAlterado;
	arquivo2.close();
}
string Engine::GetSave(std::string name)
{


	ifstream arquivo;
	arquivo.open(nameSave);
	string line;
	string strReturn;
	while(getline(arquivo,line)){
		string nameArquive;
		for(int i =0;i<name.length();i++){
			nameArquive+=line[i];
		}
		if(nameArquive == name){

			for(int i=nameArquive.length()+1;i<line.length();i++){
				strReturn+=line[i];
			}

			arquivo.close();

		}
	}
	return strReturn;
}

void Engine::addKeyPressed(int key)
{
	bool add = 1;
	for(int  i =0;i<255;i++){
		if(keyInPressed[i] == key){
			add = 0;
		}
	}
	if(add){
		//std::cout<<"nova tecla adicionada\n";
		showArray();
		keyInPressed[quantKeyPressed] = key;
		quantKeyPressed++;
	}
}

bool Engine::KeyIsPressed(int key)
{
	for(int i =0;i<quantKeyPressed;i++){
		if(key == keyInPressed[i])
			return true;
	}
	return false;
}
void Engine::deletKeyPressed(int key)
{
	for(int i =0;i<maxKey;i++){
		if(key == keyInPressed[i]){
				//std::cout<<"key deletado\n";
			keyInPressed[i] = -22;
			quantKeyPressed--;
		}
	}
}

void Engine::reposicionamento()
{
	for(int i=0;i<quantKeyPressed;i++){
		for(int l=0;l<quantKeyPressed-1;l++){
			if(keyInPressed[i] == -22){
				int temp = keyInPressed[l+1];
				 keyInPressed[l+1] = keyInPressed[l];
				 keyInPressed[l] = temp;
			}
		}
	}
	showArray();

}
void Engine::showArray()
{
	std::cout<<"[ ";
	for(int i =0;i<maxKey;i++){
		cout<<keyInPressed[i]<<", ";
	}
	std::cout<<" ]\n";
}
