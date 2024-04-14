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
extern TTF_Font* g_font;

const int SCREEN_WIDTH = 760;
const int SCREEN_HEIGHT = 760;
const int BUTTON_WIDTH = SCREEN_WIDTH / 6;
const int BUTTON_HEIGHT = SCREEN_HEIGHT / 6;
const int BUTTON_X = 450;
const int BUTTON_Y = 450;

const int roundplay = 3;
const int rect_width[roundplay] = {36, 26, 16};
const int rect_height[roundplay] = {36, 26, 16};
const int num_food[roundplay] = {15, 20, 25};
const int size_text[roundplay] = {36, 24, 12};

const int color_wall[4] = {83, 103, 201, 1};
const int color_road[4] = {5, 5, 5, 1};
const int color_des[4] = {242, 2, 49, 1}; // mau cua dich den
const int color_point[4] = {220, 215, 171, 1};
const int color_text[4] = {0, 0, 0, 0};
const int color_button_up[] = {255, 255, 255, 255};
const int color_button_down[] = {0, 0, 0, 1};

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

extern int rannum; //seed rand maze
extern ii endgame; //pos which game win
extern int round_in; //round you are in
extern bool game_start; //true when you enter play game
extern int score;

extern int begin_x, begin_y;
extern int cnt_change_maze;

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

extern vector<vector<bool> > visited;
extern vector<vector<bool> > has_point;
extern vector<vector<pair<bool, int> > > has_food;
extern vector<vector<SDL_Rect> > wall;
extern vector<ii> list_road;

const int cnt_frame = 3;

extern int game_round;

void quitSDL();
void change_size(int round_in);
bool initdata();
bool inmaze(int x, int y);
void fillscreen(SDL_Renderer* screen);
void maze(SDL_Renderer* screen);
void clear_visited(int x, int y);

#endif // COMMON_H
