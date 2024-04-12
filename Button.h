#ifndef BUTTON_H
#define BUTTON_H
#include "common.h"
#include "Text.h"

class Button
{
    public:
        //init value
        Button(int x, int y, int width, int height){
            Rect = {x, y, width, height};
            check_enter = 0;
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

        SDL_Rect *get_Rect(){return &Rect;};

        bool check_enter;

    private:
        SDL_Rect Rect;
        int color_button[4];
};

#endif // BUTTON_H
