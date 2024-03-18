#ifndef COMMON_H
#define COMMON_H
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<bits/stdc++.h>

using namespace std;

extern SDL_Window* g_window;
extern SDL_Renderer* g_render;

const int SCREEN_WIDTH = 770;
const int SCREEN_HEIGHT = 770;

const int rect_width = 36;
const int rect_height = 36;

const int cntheight = SCREEN_HEIGHT / rect_height;
const int cntwidth = SCREEN_WIDTH / rect_width;

extern int visited[cntheight][cntwidth];
extern int dir[4];
extern SDL_Rect wall[cntheight][cntwidth];

bool initdata();
void basic_wall();
bool inmaze(int x, int y);

#endif // COMMON_H
