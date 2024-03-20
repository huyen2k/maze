#ifndef CHARACER_H
#define CHARACER_H
#include "common.h"

#define frame_up "img/up.png"
#define frame_left "img/left.png"
#define frame_down "img/down.png"
#define frame_right "img/right.png"

class characer
{
    public:
        characer();
        ~characer();

        SDL_Texture* Get_Texture() const {return Texture_;};

        SDL_Rect GetRect() const { return rect_;}

        bool LoadImage(std::string path, SDL_Renderer* screen);

        void Render(SDL_Renderer* des, const SDL_Rect* clip = nullptr);

        void Render(SDL_Renderer* screen, int x, int y, SDL_Rect* clip);

        void runAnimation(SDL_Renderer* screen, SDL_Event event);

        void handinput(SDL_Event e);

        void handrun(SDL_Renderer* screen);

        void init_data(){};

        int type;

    private:
        SDL_Texture* Texture_;
        SDL_Rect rect_;
};

#endif // CHARACER_H
