#ifndef GHOST_H
#define GHOST_H
#include "common.h"
#include "characer.h"

const int speed = 3;

extern SDL_Rect ghost_frame[3];

class ghost
{
    public:
        ghost();
        ~ghost();

        bool LoadImage(std::string path, SDL_Renderer* screen);

        void set_begin(SDL_Renderer* screen, int x, int y, std::string path){
            current_x = x, current_y = y;
            if(!LoadImage(path, screen))
                printf("Can load image, %s\n", SDL_GetError());
            ghost_frame[0].x = 0;
            ghost_frame[0].y = 0;
            ghost_frame[0].w = rect_width[round_in];
            ghost_frame[0].h = rect_height[round_in];

            ghost_frame[1].x = 0;
            ghost_frame[1].y = 0;
            ghost_frame[1].w = rect_width[round_in];
            ghost_frame[1].h = rect_height[round_in];
        }

        void Render(SDL_Renderer* screen, int x, int y, SDL_Rect* clip);

        ii find_path(int main_x, int main_y);

        void run(SDL_Renderer* screen, int main_x, int main_y);

        int current_x, current_y;

    private:
        SDL_Texture *tex;

};

#endif // GHOST_H
