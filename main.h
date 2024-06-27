

#ifndef galactic_space
#define  galactic_space

#define STATUS_STATE_WAITING 0
#define STATUS_STATE_LIVES 1
#define STATUS_STATE_GAME 2
#define STATUS_STATE_GAMEOVER 3
#define STATUS_STATE_WIN 4
#define STATUS_STATE_PAUSED 5

#define NUM_Monster 100
#define NUM_LEDGES 120
#define NUM_COIN   100
#define NUM_LIFE   30

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"




typedef struct
{
  float x, y;
  int ht,wt;
  float dx, dy;
  int health;
  short lives;
  char *name;
  int onLedge, isDead;
  int animFrame, facingright, slowingDown,coincount;
} Man;

typedef struct
{
  int x, y, baseX, baseY, mode;
  float phase;
} Monster;

typedef struct {
    float x;
    float y;
    int collected;
} Coin;

typedef struct {
    float x;
    float y;
    int collect;
}Life;

typedef struct
{
  int x, y, w, h;
} Ledge;

typedef struct
{
  float scrollX;

  //Players
  Man man;

  //Monsters
  Monster Monsters[NUM_Monster];

  Coin coins[NUM_COIN];
  Ledge ledges[NUM_LEDGES];
  Life lifes[NUM_LIFE];


  //Images
  SDL_Texture *Monster;
  SDL_Texture *life;
  SDL_Texture *coin;
  SDL_Texture *manFrames[2];
  SDL_Texture *brick;
  SDL_Texture *fire;
  SDL_Texture *label, *label2;
  SDL_Texture *background;
  SDL_Texture *first;
  int labelW, labelH, label2W, label2H,label3W, label3H,label3;


  //Fonts
  TTF_Font *font;
  //time
  int time, deathCountdown;
  int statusState;

  //Sounds
  int musicChannel;
  Mix_Chunk *bgMusic, *jumpSound, *landSound, *dieSound,*yaySound,*ysound;

  //Renderer
  SDL_Renderer *renderer;

  //Window
  SDL_Window *window;
} Game;

//Prototypes (function references)
void doRender(SDL_Renderer *renderer, Game *game);

#endif

