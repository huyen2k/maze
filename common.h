#ifndef COMMON_H
#define COMMON_H
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<bits/stdc++.h>

using namespace std;
using ii = pair<int, int>;

extern SDL_Window* g_window;
extern SDL_Renderer* g_render;

const int SCREEN_WIDTH = 760;
const int SCREEN_HEIGHT = 760;

const int rect_width = 16;
const int rect_height = 16;

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

enum{
    up,
    left,
    down,
    right,
    total,
};

const int cntheight = SCREEN_HEIGHT / rect_height;
const int cntwidth = SCREEN_WIDTH / rect_width;

extern int visited[cntheight][cntwidth];
extern int dir[4];
extern SDL_Rect wall[cntheight][cntwidth];

const int cnt_frame = 3;

extern SDL_Rect running_clip[total][cnt_frame];
extern int step_x, step_y;
extern int current_x, current_y;

bool initdata();
void basic_wall();
bool inmaze(int x, int y);
void fillscreen();
void maze();

#endif // COMMON_H
