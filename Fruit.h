#ifndef FRUIT_H
#define FRUIT_H
#include "common.h"

#define src_img "img/fruit/food.png"

const int IMG_WIDTH = 128;
const int IMG_HEIGHT = 112;
const int FRUIT_WIDTH = 16;
const int FRUIT_HEIGHT = 16;
extern vector<SDL_Rect> list_food;

void pre_image(SDL_Renderer* screen);

class Fruit
{
    public:
        Fruit();
        ~Fruit();

        void pre_image(SDL_Renderer* screen);

        bool LoadImage(std::string path, SDL_Renderer* screen);

        void render_img(SDL_Renderer* screen, int x, int y, SDL_Rect* clip);

    private:
        SDL_Texture *Tex;
};

#endif // FRUIT_H
