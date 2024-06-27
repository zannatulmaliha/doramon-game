#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include<time.h>
#include "main.h"
#include "status.h"
#include "status.c"

#define GRAVITY  0.35f

void initMonsters(Game *game)
{
    //init Monsters
    for(int i = 0; i < NUM_Monster; i++)
    {
        game->Monsters[i].baseX = 320+rand()%38400;
        game->Monsters[i].baseY = rand()%480;
        game->Monsters[i].mode = rand()%2;
        game->Monsters[i].phase = 2*3.14*(rand()%360)/360.0f;
    }
}

void initCoins(Game *game)
{
    for (int i = 0; i < NUM_COIN; i++)
    {
        game->coins[i].x = 500 + rand() % 36000; // Adjust x position based on your game's requirements
        game->coins[i].y = rand() % 400;         // Adjust y position based on your game's requirements
        game->coins[i].collected = 0;            // Set collected flag to false initially
    }
}

void drawCoins(Game *game,SDL_Renderer *renderer)
{

    for (int i = 0; i < NUM_COIN; i++)
    {
        if (!game->coins[i].collected)
        {
            SDL_Rect coinRect = { game->scrollX + game->coins[i].x, game->coins[i].y, 45, 45 };
            SDL_RenderCopy(renderer, game->coin, NULL, &coinRect);
        }
    }
}

void initlife(Game *game)
{
    for (int i = 0; i < NUM_LIFE; i++)
    {
        game->lifes[i].x = 500 + rand() % 36000; // Adjust x position based on your game's requirements
        game->lifes[i].y = rand() % 400;         // Adjust y position based on your game's requirements
        game->lifes[i].collect = 0;            // Set collected flag to false initially
    }
}

void drawlifes(Game *game,SDL_Renderer *renderer)
{

    for (int i = 0; i < NUM_LIFE; i++)
    {
        if (!game->lifes[i].collect)
        {
            SDL_Rect lifeRect = { game->scrollX + game->lifes[i].x, game->lifes[i].y, 80, 80 };
            SDL_RenderCopy(renderer, game->life, NULL, &lifeRect);
        }
    }
}

void renderCoinCount(SDL_Renderer *renderer, Game *game)
{
    // Define position and size of coin count display
    int x =  640- 100; // Adjust as needed
    int y = 20; // Adjust as needed
    int w = 80;
    int h = 40;

    // Create a string buffer to hold the coin count text
    char coinCountStr[10];
    sprintf(coinCountStr, "%d", game->man.coincount); // Format the coin count text

    // Load a font (assuming you have loaded a font previously)
    // Use SDL_TTF or your preferred method to load a font

    // Set the font color
    SDL_Color textColor = { 255, 255, 255, 255 }; // White color

    // Render the coin count text
    SDL_Surface* textSurface = TTF_RenderText_Blended(game->font, coinCountStr, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Get the width and height of the text surface
    int textW, textH;
    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);

    // Define the destination rectangle for rendering the text
    SDL_Rect dstRect = { x, y, textW, textH };

    // Render the text texture
    SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);

    // Clean up
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void renderHealthBar(SDL_Renderer *renderer, Game *game)
{
    // Define health bar dimensions and position
    int healthBarWidth = 200;
    int healthBarHeight = 20;
    int healthBarX = 20;
    int healthBarY = 20;

    // Calculate current health width
    int currentHealthWidth = (int)((game->man.health / 100.0) * healthBarWidth);

    // Define colors
    SDL_Color healthColor = {255, 0, 0, 255};  // Red
    SDL_Color borderColor = {255, 200, 200, 200};    // Black

    // Draw health bar background (border)
    SDL_Rect borderRect = {healthBarX, healthBarY, healthBarWidth, healthBarHeight};
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderFillRect(renderer, &borderRect);

    // Draw current health bar
    SDL_Rect healthRect = {healthBarX, healthBarY, currentHealthWidth, healthBarHeight};
    SDL_SetRenderDrawColor(renderer, healthColor.r, healthColor.g, healthColor.b, healthColor.a);
    SDL_RenderFillRect(renderer, &healthRect);
}


void loadGame(Game *game)
{
    SDL_Surface *surface = NULL;

    surface = IMG_Load("bgg.png");
    if(surface == NULL)
    {
        printf("Cannot find bg.png!\n\n");
        SDL_Quit();
        exit(1);
    }

    game->background = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);


    surface = IMG_Load("first.png");
    game->first = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("cake.png");
    game->coin = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("life.png");
    game->life = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);


    //Load images and create rendering textures from them
    surface = IMG_Load("monster.png");
    if(surface == NULL)
    {
        printf("Cannot find monster.png!\n\n");
        SDL_Quit();
        exit(1);
    }

    game->Monster = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("doramo.png");
    if(surface == NULL)
    {
        printf("Cannot find doramon.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    game->manFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("doramo.png");
    if(surface == NULL)
    {
        printf("Cannot find doramon!\n\n");
        SDL_Quit();
        exit(1);
    }
    game->manFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("fire.png");
    game->fire = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("stone.png");
    game->brick = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    //Load fonts
    game->font = TTF_OpenFont("Crazy-Pixel.ttf", 48);
    if(!game->font)
    {
        printf("Cannot find font file!\n\n");
        SDL_Quit();
        exit(1);
    }
    //Load sounds
    game->bgMusic = Mix_LoadWAV("mu.wav");
    if(game->bgMusic != NULL)
    {
        Mix_VolumeChunk(game->bgMusic, 50);
    }
    game->dieSound = Mix_LoadWAV("die.wav");
    game->jumpSound = Mix_LoadWAV("jump.wav");
    game->landSound = Mix_LoadWAV("land.wav");
    game->yaySound = Mix_LoadWAV("winso.wav");
    game->ysound=Mix_LoadWAV("yay.wav");
    game->label = NULL;
    game->label2 = NULL;
    game->label3 = NULL;

    game->man.x = 100;

    game->man.y = 240-40;
    game->man.dx = 0;
    game->man.dy = 0;
    game->man.onLedge = 0;
    game->man.animFrame = 0;
    game->man.facingright=1;
    game->man.slowingDown = 0;
    game->man.lives = 0;
    game->man.isDead = 0;
    game->man.coincount=0;
    game->statusState = STATUS_STATE_LIVES;
    game->man.ht=50,game->man.wt=50;

    status_intro(game);

    game->time = 0;
    game->scrollX = 0;
    game->deathCountdown = -1;

    initMonsters(game);
    initCoins(game);
    initlife(game);


    //init ledges
    for(int i = 0; i < NUM_LEDGES-20; i++)
    {
        game->ledges[i].w = 256;
        game->ledges[i].h = 64;
        game->ledges[i].x = i*384;
        if(i == 0)
            game->ledges[i].y = 400;
        else
            game->ledges[i].y = 300+100-rand()%200;
    }

    for(int i = NUM_LEDGES-20; i < NUM_LEDGES; i++)
    {
        game->ledges[i].w = 256;
        game->ledges[i].h = 64;
        game->ledges[i].x = 350+rand()%38400;
        if(i % 2 == 0)
            game->ledges[i].y = 200;
        else
            game->ledges[i].y = 350;
    }


}

void process(Game *game)
{
    game->time++;

    if(game->statusState == STATUS_STATE_LIVES)
    {
        if(game->time > 120)
        {
            close_intro(game);
            game->statusState = STATUS_STATE_GAME;
            game->musicChannel = Mix_PlayChannel(-1, game->bgMusic, -1);
        }
    }
    else if(game->statusState == STATUS_STATE_GAMEOVER)
    {
        if(game->time > 190)
        {
            SDL_Quit();
            exit(0);
        }
    }
    else if(game->statusState == STATUS_STATE_GAME)
    {
        if(!game->man.isDead)
        {
            //man movement
            Man *man = &game->man;
            man->x += man->dx;
            man->y += man->dy;

            if(man->dx != 0 && man->onLedge && !man->slowingDown)
            {
                if(game->time % 8 == 0)
                {
                    if(man->animFrame == 0)
                    {
                        man->animFrame = 1;
                    }
                    else
                    {
                        man->animFrame = 0;
                    }
                }
            }

            if(man->x > 38320)
            {
                init_gamewin(game);
                game->statusState = STATUS_STATE_WIN;
            }

            man->dy += GRAVITY;

            //Monster movement
            for(int i = 0; i < NUM_Monster; i++)
            {
                game->Monsters[i].x = game->Monsters[i].baseX;
                game->Monsters[i].y = game->Monsters[i].baseY;

                if(game->Monsters[i].mode == 0)
                {
                    game->Monsters[i].x = game->Monsters[i].baseX+sinf(game->Monsters[i].phase+game->time*0.06f)*75;
                }
                else
                {
                    game->Monsters[i].y = game->Monsters[i].baseY+cosf(game->Monsters[i].phase+game->time*0.06f)*75;
                }
            }
        }

        if(game->man.isDead && game->deathCountdown < 0)
        {
            game->deathCountdown = 120;
        }
        if(game->deathCountdown >= 0)
        {
            game->deathCountdown--;
            if(game->deathCountdown < 0)
            {

                game->man.ht-=10;
                game->man.wt-=10;
                game->man.health -= 10;  // Decrease health by 10
                if (game->man.health < 0)
                {
                    game->man.health = 0;  // Ensure health does not go below 0
                }
                game->man.lives--;
                if(game->man.ht<50 && game->man.wt<50)
                {
                    game->man.ht=50;
                    game->man.wt=50;
                }
                if(game->man.lives >= 0)
                {
                    status_intro(game);
                    game->statusState = STATUS_STATE_LIVES;
                    game->time = 0;

                    //reset
                    game->man.isDead = 0;
                    game->man.x = 100;
                    game->man.y = 240-40;
                    game->man.dx = 0;
                    game->man.dy = 0;
                    game->man.onLedge = 0;
                    initMonsters(game);
                }
                else
                {
                    init_gameover(game);
                    game->statusState = STATUS_STATE_GAMEOVER;
                    game->time = 0;
                }
            }
        }
    }

    game->scrollX = -game->man.x+320;
    if(game->scrollX > 0)
        game->scrollX = 0;
    if(game->scrollX < -38000+320)
        game->scrollX = -38000+320;
}

//useful utility function to see if two rectangles are colliding at all
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
    return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}

void collisionDetect(Game *game)
{
    //Check for collision with enemies
    for(int i = 0; i < NUM_Monster; i++)
    {
        if(collide2d(game->man.x, game->man.y, game->Monsters[i].x, game->Monsters[i].y, 48, 48, 32, 32))
        {
            if(!game->man.isDead)
            {
                if(game->man.ht<50 && game->man.wt<50)
                {
                    game->man.ht=50;
                    game->man.wt=50;
                }

                game->man.ht-=10;
                game->man.wt-=10;
                game->man.health -= 10;  // Decrease health by 10
                if (game->man.health < 0)
                {
                    game->man.health = 0;  // Ensure health does not go below 0
                }
                game->man.isDead = 1;
                Mix_HaltChannel(game->musicChannel);

                Mix_PlayChannel(-1, game->dieSound, 0);
            }
            break;
        }
    }

    //Check for falling
    if(game->man.y > 480)
    {
        if(!game->man.isDead)
        {
            game->man.health -= 10;  // Decrease health by 10
            if (game->man.health < 0)
            {
                game->man.health = 0;  // Ensure health does not go below 0
            }
            if(game->man.ht<50 && game->man.wt<50)
            {
                game->man.ht=50;
                game->man.wt=50;
            }
            game->man.ht-=10;
            game->man.wt-=10;
            game->man.isDead = 1;
            Mix_HaltChannel(game->musicChannel);
            Mix_PlayChannel(-1, game->dieSound, 0);
        }
    }

    //Check for collision with any ledges (brick blocks)
    for(int i = 0; i < NUM_LEDGES; i++)
    {
        float mw = 48, mh = 48;
        float mx = game->man.x, my = game->man.y;
        float bx = game->ledges[i].x, by = game->ledges[i].y, bw = game->ledges[i].w, bh = game->ledges[i].h;

        if(mx+mw/2 > bx && mx+mw/2<bx+bw)
        {
            //are we bumping our head?
            if(my < by+bh && my > by && game->man.dy < 0)
            {
                //correct y
                game->man.y = by+bh;
                my = by+bh;

                //bumped our head, stop any jump velocity
                game->man.dy = 0;
                game->man.onLedge = 1;
            }
        }
        if(mx+mw > bx && mx<bx+bw)
        {
            //are we landing on the ledge
            if(my+mh > by && my < by && game->man.dy > 0)
            {
                //correct y
                game->man.y = by-mh;
                my = by-mh;

                //landed on this ledge, stop any jump velocity
                game->man.dy = 0;
                if(!game->man.onLedge)
                {
                    Mix_PlayChannel(-1, game->landSound, 0);
                    game->man.onLedge = 1;
                }
            }
        }

        if(my+mh > by && my<by+bh)
        {
            //rubbing against right edge
            if(mx < bx+bw && mx+mw > bx+bw && game->man.dx < 0)
            {
                //correct x
                game->man.x = bx+bw;
                mx = bx+bw;

                game->man.dx = 0;
            }
            //rubbing against left edge
            else if(mx+mw > bx && mx < bx && game->man.dx > 0)
            {
                //correct x
                game->man.x = bx-mw;
                mx = bx-mw;

                game->man.dx = 0;
            }
        }
    }
    for (int i = 0; i < NUM_COIN; i++)
    {
        if (!game->coins[i].collected && collide2d(game->man.x, game->man.y, game->coins[i].x, game->coins[i].y, 48, 48, 45, 45))
        {
            game->coins[i].collected = 1;
            game->man.coincount++;
            Mix_PlayChannel(-1, game->yaySound, 0);

        }
    }

    for (int i = 0; i < NUM_LIFE; i++)
    {
        if (!game->lifes[i].collect && collide2d(game->man.x, game->man.y, game->lifes[i].x, game->lifes[i].y,45,45,game->man.ht, game->man.wt))
        {
            game->lifes[i].collect = 1;
            game->man.lives++;
            game->man.health += 10;  // increase health by 10
            if (game->man.health > 100)
            {
                game->man.health = 100;  // Ensure health does not go above 100
            }
            Mix_PlayChannel(-1, game->ysound, 0);
            game->man.wt += 10;
            game->man.ht += 10;
        }
    }

}

int processEvents(SDL_Window *window, Game *game)
{
    SDL_Event event;
    int done = 0;


    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_WINDOWEVENT_CLOSE:
        {
            if(window)
            {
                SDL_DestroyWindow(window);
                window = NULL;
                done = 1;
            }
        }
        break;
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                done = 1;
                break;

            case SDLK_SPACE:

                if(game->time>120 && game->statusState == STATUS_STATE_LIVES)
                {
                    game->statusState = STATUS_STATE_PAUSED;
                }
                else if(game->statusState == STATUS_STATE_PAUSED)
                {
                    game->statusState = STATUS_STATE_GAME;
                    game->musicChannel = Mix_PlayChannel(-1, game->bgMusic, -1);

                }
                break;
            case SDLK_UP:
                game->man.dy = -7;
                game->man.onLedge = 0;
                Mix_PlayChannel(-1, game->jumpSound, 0);

                break;
            }
        }
        break;
        case SDL_QUIT:
            //quit out of the game
            done = 1;
            break;
        }
    }




    game->man.dx += 0.9;
    if(game->man.dx > 6)
    {
        game->man.dx = 6;
    }

    game->man.dx *= 0.8f;

    // Update the character's Y position


    // Ensure the character doesn't go above the screen
    if (game->man.y < 0)
    {
        game->man.y = 0;
        game->man.dy = 0;
    }

    return done;
}

void doRender(SDL_Renderer *renderer, Game *game)
{

    if(game->statusState == STATUS_STATE_LIVES)
    {
        draw_intro(game);
        if(game->time>60)
            game->statusState = STATUS_STATE_PAUSED;  // Switch to paused state after intro

    }
    else if(game->statusState == STATUS_STATE_PAUSED)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, game->background, NULL, NULL);

        SDL_Color textColor = { 255, 255, 255, 255 };
        SDL_Surface* textSurface = TTF_RenderText_Blended(game->font, "Press Space to Play", textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        int textW = textSurface->w;
        int textH = textSurface->h;
        SDL_Rect textRect = { 320 - textW / 2, 240 - textH / 2, textW, textH };

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        SDL_RenderPresent(renderer);
    }
    else if(game->statusState == STATUS_STATE_GAMEOVER)
    {
        draw_gameover(game);
    }
    else if(game->statusState == STATUS_STATE_WIN)
    {
        draw_gamewin(game);
    }
    else if(game->statusState == STATUS_STATE_GAME)
    {


        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,game->background, NULL,NULL);

        //set the drawing color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


        renderHealthBar(renderer, game);
        renderCoinCount(renderer, game);

        for(int i = 0; i < NUM_LEDGES; i++)
        {
            SDL_Rect ledgeRect = { game->scrollX+game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h };
            SDL_RenderCopy(renderer, game->brick, NULL, &ledgeRect);
        }

        //draw the monster images
        for(int i = 0; i < NUM_Monster; i++)
        {
            SDL_Rect starRect = { game->scrollX+game->Monsters[i].x, game->Monsters[i].y, 64, 64 };
            SDL_RenderCopy(renderer, game->Monster, NULL, &starRect);
        }

        drawCoins(game,renderer);
        drawlifes(game,renderer);

        //draw a rectangle at man's position
        SDL_Rect rect = { game->scrollX+game->man.x, game->man.y, game->man.wt,game->man.ht};
        SDL_RenderCopyEx(renderer, game->manFrames[game->man.animFrame],
                         NULL, &rect, 0, NULL, (game->man.facingright == 0));

        if(game->man.isDead)
        {
            SDL_Rect rect = { game->scrollX+game->man.x-24+38/2+10, game->man.y-24-83/2, 38, 83 };
            SDL_RenderCopyEx(renderer, game->fire,
                             NULL, &rect, 0, NULL, (game->time%20 < 10));
        }
    }

    //We are done drawing, "present" or show to the screen what we've drawn

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    int mode = 0;
    int flags[] = { 0, SDL_WINDOW_FULLSCREEN, SDL_WINDOW_FULLSCREEN_DESKTOP };
    //argument checking
    for(int i = 1; i < argc; i++)
    {
        if(strcasecmp(argv[i], "-mode") == 0 && i+1 < argc)
        {
            mode = atoi(argv[i+1]);
            if(mode < 0 || mode > 2)
                mode = 0;
        }
    }


    Game Game;
    SDL_Window *window = NULL;                    // Declare a window
    SDL_Renderer *renderer = NULL;                // Declare a renderer

    SDL_Init(SDL_INIT_VIDEO  | SDL_INIT_AUDIO);              // Initialize SDL2



    srand((int)time(NULL));

    //Create an application window with the following settings:
    window = SDL_CreateWindow("Game",                     // window title
                              SDL_WINDOWPOS_UNDEFINED,           // initial x position
                              SDL_WINDOWPOS_UNDEFINED,           // initial y position
                              640,                               // width, in pixels
                              480,                               // height, in pixels
                              flags[mode]);                      // flags
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Game.renderer = renderer;
    Game.window = window;

    //Hide mouse
    SDL_ShowCursor(0);

    SDL_RenderSetLogicalSize(renderer, 640, 480);

    TTF_Init(); //initialize font system

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096); //initialize sound

    loadGame(&Game);

    // The window is open: enter program loop (see SDL_PollEvent)
    int done = 0;

    //Event loop
    while(!done)
    {
        //Check for events
        done = processEvents(window, &Game);

        process(&Game);
        collisionDetect(&Game);

        //Render display
        doRender(renderer, &Game);

        //don't burn up the CPU
        //SDL_Delay(10);
    }


    //Shutdown game and unload all memory
    SDL_DestroyTexture(Game.Monster);
    SDL_DestroyTexture(Game.manFrames[0]);
    SDL_DestroyTexture(Game.manFrames[1]);
    SDL_DestroyTexture(Game.brick);
    if(Game.label != NULL)
        SDL_DestroyTexture(Game.label);
    if(Game.label2 != NULL)
        SDL_DestroyTexture(Game.label2);
    if(Game.label3 != NULL)
        SDL_DestroyTexture(Game.label3);

    TTF_CloseFont(Game.font);

    Mix_FreeChunk(Game.bgMusic);
    Mix_FreeChunk(Game.dieSound);
    Mix_FreeChunk(Game.jumpSound);
    Mix_FreeChunk(Game.landSound);
    Mix_FreeChunk(Game.yaySound);
    // Close and destroy the window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    TTF_Quit();
    Mix_CloseAudio();

    // Clean up
    SDL_Quit();
    return 0;
}
