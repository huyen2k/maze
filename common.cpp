#include "common.h"

SDL_Window* g_window = nullptr;
SDL_Renderer* g_render = nullptr;
SDL_Rect wall[SCREEN_HEIGHT / rect_height][SCREEN_WIDTH / rect_width];
int visited[cntheight][cntwidth];
int dir[4] = {0, 1, 2, 3};

bool initdata(){
    bool success = 1;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        g_window = SDL_CreateWindow("newhello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(g_window != nullptr){
            g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
        }
    }
    memset(visited, 0, sizeof(visited));
    return success;
}

void basic_wall(){
    int xx = 0, yy = 0;
    for(int i = 0; i < cntheight; i ++){
        xx = 0;
        for(int j = 0; j < cntwidth; j ++){
            wall[i][j].x = xx;
            wall[i][j].y = yy;
            wall[i][j].h = rect_height;
            wall[i][j].w = rect_width;
            xx += rect_width;
            //std::cout << i << " " << j << " " << wall[i][j].x << " " << wall[i][j].y << '\n';
        }
        yy += rect_height;
    }
}

bool inmaze(int x, int y){
    if(x < 0 || x >= cntwidth) return 0;
    if(y < 0 || y >= cntheight) return 0;
    return 1;
}

