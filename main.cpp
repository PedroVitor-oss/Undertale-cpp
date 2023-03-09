#include <string>
#include <iostream>
#include <Engine.h>
#include <windows.h>
#include <player.h>

Engine Game;
colorRGB colorTela;
SpriteGame spreiteNULL = {0,0,0,0};
SDL_Rect boxNull = {0,0,0,0};
SDL_Texture* batalhaTexture;
SDL_Texture* arenaTexture ;
SDL_Rect boxArena = {430,200,300,300};

bool inGame = true;

void Introdution();
void ruinas();
void showFalas(int inicio,int fi,SpriteGame falas[],SDL_Texture* img);
void DrawFight();

int main( int argc, char * argv[] )
{
    Game.Init("undertale",1200,700);
    colorTela = Game.createColorRGB(0,0,0);
     //create Saves
    if(Game.GetSave("viewIntro")== "" ){
       Game.AddSave("viewIntro","no");
    }
    if(Game.GetSave("fase")==""){
       Game.AddSave("fase","no");
       std::cout<<"novo save criado";
    }


    if(Game.GetSave("viewIntro")=="no"){
        Introdution();
        Game.SetSave("viewIntro","yes");
    }
    ruinas();


    Game.Quit();
   return 0;
}
void ruinas(){
    //textura batalha
    arenaTexture = Game.CreateTexture("img/arenaBatalha.bmp");
    batalhaTexture = Game.CreateTexture("img/batalha.bmp");
    //textura e sprites do personagem
    SDL_Texture* TexturePlayerRuinas = Game.CreateTexture("img/playerRuinas.bmp");
    SDL_Texture* TexturePlayerDark = Game.CreateTexture("img/playerDark.bmp");
    player frisk = player(255,320,50,60);
    frisk.sprites[0] = {5,20,19,29};
    //textura e sprites da ruinas
    SDL_Texture* TextureRuinas = Game.CreateTexture("img/ruinas.bmp");
    SpriteGame ruina1 = {1,12,652,249};
    SDL_Rect boxAreaRuina1 = {0,0,1500,700};
    int veloFrisk = 20;

    SDL_Rect boxColisions[20] = {
        {140,120,405,50},
        {50,175,85,50},
        {545,175,85,50},
        {0,235,48,270},
        {645,235,48,215},
        {50,505,40,50},
        {90,555,45,55},
        {135,610,45,50},
        {180,660,350,50},
        {500,620,45,50},
        {555,565,950,50},
        {695,400,650,50},
        {1500,400,50,200},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
    };
    //fase 1
    while(Game.GetSave("fase")=="no"){
        int keyCode = Game.eventos(SDL_KEYDOWN);
        /*movimentação*/
        {
            if(Game.KeyIsPressed(SDLK_UP))
            {
                boxAreaRuina1.y+=veloFrisk;
                for(int i =0;i<20;i++){
                    SDL_Rect newBox = {
                        boxAreaRuina1.x+boxColisions[i].x,
                        boxAreaRuina1.y+boxColisions[i].y,
                        boxColisions[i].w,
                        boxColisions[i].h,};

                    if(Game.ColisionRect(frisk.boxArea,newBox)){
                        boxAreaRuina1.y-=veloFrisk;
                    }
                }
            }
            if(Game.KeyIsPressed(SDLK_DOWN)){
                boxAreaRuina1.y-=veloFrisk;
                for(int i =0;i<20;i++){
                    SDL_Rect newBox = {
                        boxAreaRuina1.x+boxColisions[i].x,
                        boxAreaRuina1.y+boxColisions[i].y,
                        boxColisions[i].w,
                        boxColisions[i].h,};

                    if(Game.ColisionRect(frisk.boxArea,newBox)){
                        boxAreaRuina1.y+=veloFrisk;
                    }
                }
            }
            if(Game.KeyIsPressed(SDLK_RIGHT)){
                boxAreaRuina1.x-=veloFrisk;
                for(int i =0;i<20;i++){
                    SDL_Rect newBox = {
                        boxAreaRuina1.x+boxColisions[i].x,
                        boxAreaRuina1.y+boxColisions[i].y,
                        boxColisions[i].w,
                        boxColisions[i].h,};

                    if(Game.ColisionRect(frisk.boxArea,newBox)){
                        boxAreaRuina1.x+=veloFrisk;
                    }
                }
            }
            if(Game.KeyIsPressed(SDLK_LEFT)){
                boxAreaRuina1.x+=veloFrisk;
                for(int i =0;i<20;i++){
                    SDL_Rect newBox = {
                        boxAreaRuina1.x+boxColisions[i].x,
                        boxAreaRuina1.y+boxColisions[i].y,
                        boxColisions[i].w,
                        boxColisions[i].h,};

                    if(Game.ColisionRect(frisk.boxArea,newBox)){
                        boxAreaRuina1.x-=veloFrisk;
                    }
                }
            }

        }

        Game.Clean(colorTela);

        Game.DrawTexture(TextureRuinas,ruina1,boxAreaRuina1);
        Game.DrawTexture(TexturePlayerRuinas,frisk.sprites[0],frisk.boxArea);

        SDL_Rect Transition = {
        boxAreaRuina1.x+1350,
        boxAreaRuina1.y+300,
        150,150};
        if(Game.ColisionRect(frisk.boxArea,Transition)){
                Game.SetSave("fase","ruinas2");
            break;
        }
        Game.Update();
        Sleep(41);
    }

    //fase2
    SDL_Texture* TextureFlowey  = Game.CreateTexture("img/floweysprites.bmp");
    SDL_Rect boxFlowey = {450,610,20,20};
    SpriteGame SpriteFlowey = {6,15,23,23};
    ruina1 = {1,275,318,612-275};
    boxAreaRuina1 = {250,-500,700,700};
    SDL_Rect boxcutscene = {50,750,500,100};
    for(int i =0 ;i<20;i++){
        boxColisions[i] = {0,0,0,0};
    }
    boxColisions[0] = {-3500,210,7000,100};
    boxColisions[1] = {150,610,400,100};

    frisk.boxArea = {575,400,50,60};
    bool cutscene = 0;
    int lBoxCutScene = 600;
    while(Game.GetSave("fase") == "ruinas2"){
        int keyCode = Game.eventos(SDL_KEYDOWN);
         /*movimentação*/
        if(!cutscene){
            if(Game.KeyIsPressed(SDLK_UP))
                {
                boxAreaRuina1.y+=veloFrisk;
                for(int i =0;i<20;i++){
                    SDL_Rect newBox = {
                        boxAreaRuina1.x+boxColisions[i].x,
                        boxAreaRuina1.y+boxColisions[i].y,
                        boxColisions[i].w,
                        boxColisions[i].h,};

                    if(Game.ColisionRect(frisk.boxArea,newBox)){
                        boxAreaRuina1.y-=veloFrisk;
                    }
                }
            }
            if(Game.KeyIsPressed(SDLK_DOWN)){
                boxAreaRuina1.y-=veloFrisk;
                for(int i =0;i<20;i++){
                    SDL_Rect newBox = {
                        boxAreaRuina1.x+boxColisions[i].x,
                        boxAreaRuina1.y+boxColisions[i].y,
                        boxColisions[i].w,
                        boxColisions[i].h,};

                    if(Game.ColisionRect(frisk.boxArea,newBox)){
                        boxAreaRuina1.y+=veloFrisk;
                    }
                }
            }
            if(Game.KeyIsPressed(SDLK_RIGHT)){
                boxAreaRuina1.x-=veloFrisk;
                for(int i =0;i<20;i++){
                    SDL_Rect newBox = {
                        boxAreaRuina1.x+boxColisions[i].x,
                        boxAreaRuina1.y+boxColisions[i].y,
                        boxColisions[i].w,
                        boxColisions[i].h,};

                    if(Game.ColisionRect(frisk.boxArea,newBox)){
                        boxAreaRuina1.x+=veloFrisk;
                    }
                }
            }
            if(Game.KeyIsPressed(SDLK_LEFT)){
                boxAreaRuina1.x+=veloFrisk;
                for(int i =0;i<20;i++){
                    SDL_Rect newBox = {
                        boxAreaRuina1.x+boxColisions[i].x,
                        boxAreaRuina1.y+boxColisions[i].y,
                        boxColisions[i].w,
                        boxColisions[i].h,};

                    if(Game.ColisionRect(frisk.boxArea,newBox)){
                        boxAreaRuina1.x-=veloFrisk;
                    }
                }
            }

        }


        cutscene = Game.ColisionRect(frisk.boxArea,boxcutscene);

        Game.Clean(colorTela);
        SDL_Rect Transition = {
        boxAreaRuina1.x+300,
        boxAreaRuina1.y+200,
        110,130};

        Game.DrawTexture(TextureRuinas,ruina1,boxAreaRuina1);
        Game.DrawTexture(TexturePlayerDark,frisk.sprites[0],frisk.boxArea);
        Game.DrawRect(Transition,colorRGB({0,255,0}));
        boxcutscene = {boxAreaRuina1.x+50,boxAreaRuina1.y+650,lBoxCutScene,100};
        //Game.DrawRect(boxcutscene,colorRGB({200,100,0}));
        boxFlowey = {boxAreaRuina1.x+340, boxAreaRuina1.y+619,35,35};

        if(cutscene){
            Game.DrawTexture(TextureFlowey,SpriteFlowey,boxFlowey);

            SpriteGame spritesfalaFlowey[4];
            int quantFalas  = 0;
            for(int y =0;y<2;y++){
                for(int x = 0;x<2;x++){
                    spritesfalaFlowey[quantFalas] = {
                    x*635,y*150,635,150};
                    quantFalas++;
                }
            }
            SDL_Texture* falasFlowey = Game.CreateTexture("img/falasFlowey.bmp");
           // Game.DrawTexture(falasFlowey,spritesfalaFlowey[1], {50,600,1180,90});

            showFalas(0,2,spritesfalaFlowey,falasFlowey);
            std::cout<<"fim da conversa";
            cutscene = 0;
            lBoxCutScene = 0;
            frisk.boxArea.y+=10;
            DrawFight();
            SDL_Texture* floweyBatalhaTexture = Game.CreateTexture("img/floweyBatalha.bmp");
            SpriteGame SpritesFloweyBatalha[32];
            SDL_Rect boxFloweyBatalha = {550,100,70,80};
            SDL_Texture* heartRedTexture = Game.CreateTexture("img/heart.bmp");
            SpriteGame heartRedSprite = {7,6,16,16};
            SDL_Rect heart = {570,350,40,40};
            int veloHeart = 10;
           // SDL_Texture* hpTexture = Game.CreateTexture("img/hp.bmp");
            SDL_Rect hpBox = {468,560,260,21};
            int quantSprites = 0;
            for(int i =0;i<3;i++){
                for(int l=0;l<6;l++){
                    SpritesFloweyBatalha[quantSprites] = {44*l,47*i,44,47};
                    quantSprites++;
                }
            }
            SDL_Rect colisionBatalha[4] = {
                {440,200,300,10},
                {430,490,300,10},
                {430,200,10,300},
                {720,200,10,300}

            };
            while(1){
                Game.eventos(0);
                DrawFight();

                if(Game.KeyIsPressed(SDLK_UP)){
                    heart.y-=veloHeart;
                    for(int i =0;i<4;i++){
                        if(Game.ColisionRect(heart,colisionBatalha[i])){
                            heart.y+=veloHeart;
                        }
                    }
                }
                if(Game.KeyIsPressed(SDLK_DOWN)){
                    heart.y+=veloHeart;
                    for(int i =0;i<4;i++){

                        if(Game.ColisionRect(heart,colisionBatalha[i])){
                            heart.y-=veloHeart;
                        }
                    }
                }
                if(Game.KeyIsPressed(SDLK_RIGHT)){
                    heart.x+=veloHeart;
                    for(int i =0;i<4;i++){

                        if(Game.ColisionRect(heart,colisionBatalha[i])){
                            heart.x-=veloHeart;
                        }
                    }
                }
                if(Game.KeyIsPressed(SDLK_LEFT)){
                    heart.x-=veloHeart;
                    for(int i =0;i<4;i++){

                        if(Game.ColisionRect(heart,colisionBatalha[i])){
                            heart.x+=veloHeart;
                        }
                    }
                }

                Game.DrawTexture(heartRedTexture,heartRedSprite,heart);
                Game.DrawTexture(floweyBatalhaTexture,SpritesFloweyBatalha[0],boxFloweyBatalha);
                Game.DrawRect(hpBox,{255,242,0});
                Game.Update();
                Sleep(51);
               // break;
            }

            system("pause");

        }
        Game.Update();

        Sleep(51);
    }

}
void DrawFight(){

    Game.Clean({0,0,0});
    Game.DrawTexture(batalhaTexture,spreiteNULL,boxNull);
    Game.DrawTexture(arenaTexture,spreiteNULL,boxArena);
   // Game.Update();
}
void Introdution(){

    SDL_Texture* intro = Game.CreateTexture("img/intro.bmp");
    SpriteGame spritesIntro[13];
    for(int i =0;i<11;i++){
       spritesIntro[i] = Game.createSpriteGame(6,0+i*245,316,235);
    }
    spritesIntro[11] = {6,2696+350-235,316,235};
    spritesIntro[12] = {6,3072,316,235};
    int nubFrame = 0;
    int TempoIntro = 0;
    while(1){
        if(nubFrame<11){
            Game.eventos(0);
            Game.Clean(colorTela);
            Game.DrawTexture(intro,spritesIntro[nubFrame],boxNull);
            Game.Update();
            TempoIntro++;
            if(TempoIntro == 100){
                nubFrame++;
                TempoIntro = 0;
            }
            Sleep(51);
        }else if(nubFrame ==11){
            Game.eventos(0);
            Game.Clean(colorTela);
            Game.DrawTexture(intro,spritesIntro[11],boxNull);
            Game.Update();
            if(spritesIntro[11].y>2696){
                spritesIntro[11].y--;
            }else{
                nubFrame = 12;
            }
            Sleep(51);
        }else if (nubFrame == 12){
            TempoIntro++;
            Game.eventos(0);
            Game.Clean(colorTela);
            Game.DrawTexture(intro,spritesIntro[nubFrame],boxNull);
            Game.Update();
            Sleep(51);
            if(TempoIntro == 50){
                break;
            }
        }
    }
}
void showFalas(int inicio ,int fim ,SpriteGame falas[],SDL_Texture* img){
    for(int i= inicio;i<fim;i++){
        SDL_Rect boxText = {80,520,1050,180};
        Game.DrawTexture(img,falas[i],boxText);
        Game.Update();
        while(1){
            int keyCode = Game.eventos(SDL_KEYDOWN);
            if(keyCode == SDLK_z){
                break;
            }
        }

    }

}
