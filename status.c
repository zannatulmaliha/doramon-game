

#include "SDL.h"
#include <stdio.h>
#include "main.h"

void status_intro(Game *game)
{
    char str[128] = "";
    char st[128] = "";

    sprintf(str, "x %d", (int)game->man.lives);

    sprintf(st, "DoraCake: x %d", (int)game->man.coincount);


    //Create label textures for status screen
    SDL_Color bl = { 169, 178, 198, 255 };

    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, str,bl );
    game->labelW = tmp->w;
    game->labelH = tmp->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);

    SDL_Color lightBlue = { 128, 192, 255, 255 };
    SDL_Color red = {132, 140, 207,255};

    SDL_Surface *tmp1 = TTF_RenderText_Blended(game->font, st,red);
    game->label3W =tmp1->w;
    game->label3H = tmp1->h;
    game->label3= SDL_CreateTextureFromSurface(game->renderer, tmp1);
    SDL_FreeSurface(tmp1);


    tmp = TTF_RenderText_Blended(game->font, "Galactic Escape", lightBlue);
    game->label2W = tmp->w;
    game->label2H = tmp->h;
    game->label2 = SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);
}

void draw_intro(Game *game)
{
    SDL_Renderer *renderer = game->renderer;
    //SDL_SetRenderDrawColor(renderer, 51, 51,51, 255);

    //Clear the screen
    //hello
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer,game->first, NULL,NULL);
    SDL_Rect rect = { 320-70, 240-24, 48, 48 };
    SDL_RenderCopyEx(renderer, game->manFrames[0],
                     NULL, &rect, 0, NULL, (game->man.facingright == 0));

    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect textRect = { 320-20, 240-game->labelH+50, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &textRect);
    SDL_Rect textRect2 = {320-game->label2W/2, 100-game->label2H/2-50, game->label2W, game->label2H };
    SDL_RenderCopy(renderer, game->label2, NULL, &textRect2);


    SDL_Rect textRect3 = { 320-game->label3W/2-20,190-game->label3H, game->label3W, game->label3H };
    SDL_RenderCopy(renderer, game->label3, NULL, &textRect3);

}

void close_intro(Game *game)
{
    SDL_DestroyTexture(game->label);
    game->label = NULL;

    SDL_DestroyTexture(game->label2);
    game->label2 = NULL;

    SDL_DestroyTexture(game->label3);
    game->label3 = NULL;
}


// Draw coins on the screen


void init_gameover(Game *game)
{
    //Create label textures for status screen
    SDL_Color white = { 255, 255, 255, 255 };

    char st[128] = "";

    sprintf(st, "DoraCake: x %d", (int)game->man.coincount);
    SDL_Color red = {132, 140, 207,255};

    SDL_Surface *tmp1 = TTF_RenderText_Blended(game->font, st,red);
    game->label3W =tmp1->w;
    game->label3H = tmp1->h;
    game->label3= SDL_CreateTextureFromSurface(game->renderer, tmp1);
    SDL_FreeSurface(tmp1);


    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "GAME OVER!", white);
    game->labelW = tmp->w;
    game->labelH = tmp->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);
}

void draw_gameover(Game *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //Clear the screen
    SDL_RenderClear(renderer);

    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect textRect = { 320-game->labelW/2, 240-game->labelH/2, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &textRect);


    SDL_Rect textRect3 = { 320-game->label3W/2-20,190-game->label3H, game->label3W, game->label3H };
    SDL_RenderCopy(renderer, game->label3, NULL, &textRect3);

}

void close_gameover(Game *game)
{
    SDL_DestroyTexture(game->label);
    game->label = NULL;
}

void init_gamewin(Game *game)
{
    //Create label textures for status screen
    SDL_Color white = { 255, 255, 255, 255 };

    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "You live..", white);
    game->labelW = tmp->w;
    game->labelH = tmp->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);
}

void draw_gamewin(Game *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //Clear the screen
    SDL_RenderClear(renderer);

    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect textRect = { 320-game->labelW/2, 240-game->labelH/2, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &textRect);
}

void close_gamewin(Game *game)
{
    SDL_DestroyTexture(game->label);
    game->label = NULL;
}




