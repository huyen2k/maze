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
extern SDL_Renderer* background;

const int SCREEN_WIDTH = 760;
const int SCREEN_HEIGHT = 760;

const int roundplay = 3;
const int rect_width[roundplay] = {36, 26, 16};
const int rect_height[roundplay] = {36, 26, 16};

const int color_wall[4] = {0, 0, 0, 1};
const int color_road[4] = {255, 255, 255, 1};
const int color_border[4] = {158, 13, 5, 1};
const int color_des[4] = {66, 92, 230, 1};

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

extern int rannum; //seed rand maze
extern ii endgame; //pos which game win
extern int round_in; //round you are in

enum{
    up,
    left,
    down,
    right,
    total,
};
extern int dir[4];

extern int cntheight;
extern int cntwidth;

extern vector<vector<int> > visited;
extern vector<vector<SDL_Rect> > wall;

const int cnt_frame = 3;

extern SDL_Rect running_clip[roundplay][total][cnt_frame];
extern int game_round;

void quitSDL();
void change_size();
bool initdata();
bool inmaze(int x, int y);
void fillscreen();
void maze(SDL_Renderer* screen);

#endif // COMMON_H
