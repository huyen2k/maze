#ifndef BUTTON_H
#define BUTTON_H
#include "common.h"

const int BUTTON_WIDTH = SCREEN_WIDTH / 6;
const int BUTTON_HEIGHT = SCREEN_HEIGHT / 6;
const int BUTTON_X = 450;
const int BUTTON_Y = 450;

const int color_button_up[] = {255, 255, 255, 255};
const int color_button_down[] = {0, 0, 0, 1};

class Button
{
    public:
        //init value
        Button(int x, int y, int width, int height){
            Rect.x = x;
            Rect.y = y;
            Rect.w = width;
            Rect.h = height;
        };
        //deallocated memory
        ~Button();

        //Renders texture at given point
        void render(SDL_Renderer* screen);

        void hand_input(SDL_Event *e);

        //Gets image dimensions
        int get_postion_x(){return Rect.x;};
        int get_postion_y(){return Rect.y;};

        void setColor(int color[]) {
            for(int i = 0; i < 4; i ++)
                color_button[i] = color[i];
        };

    private:
        SDL_Rect Rect;
        int color_button[4];
};

#endif // BUTTON_H
