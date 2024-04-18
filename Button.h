#ifndef BUTTON_H
#define BUTTON_H
#include "common.h"

class Button
{
    public:
        //init value
        Button(std::string path_, SDL_Rect rect_){
            Rect = rect_;
            path = path_;
            check_enter = 0;
            Tex = nullptr;
        };
        //deallocated memory
        ~Button();

        bool LoadImage(std::string path, SDL_Renderer* screen);

        //Renders texture
        void render(SDL_Renderer *screen, SDL_Rect dsrect);

        void hand_input(SDL_Event *e, SDL_Renderer* screen);

        //Gets image dimensions
        int get_postion_x(){return Rect.x;};
        int get_postion_y(){return Rect.y;};

        void setColor(int color[]) {
            for(int i = 0; i < 4; i ++)
                color_button[i] = color[i];
        };

        SDL_Texture* getTex(){return Tex; };

        SDL_Rect *get_Rect(){return &Rect;};

        bool check_enter;
        std::string path;

    private:
        SDL_Rect Rect;
        SDL_Texture* Tex;
        int color_button[4];
};

#endif // BUTTON_H
