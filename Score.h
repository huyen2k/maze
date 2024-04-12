#ifndef SCORE_H
#define SCORE_H
#include "common.h"


class Score
{
    public:
        Score();
        ~Score();

        bool LoadImage(std::string path, SDL_Renderer* screen);

        void render(SDL_Renderer* screen, int x, int y);

        void render_number(SDL_Renderer* screen, int x, int y);

    private:
        SDL_Texture* Tex;
        int n_width, n_height;
};

#endif // SCORE_H
