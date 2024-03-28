#ifndef BUTTON_H
#define BUTTON_H
#include "common.h"

const int BUTTON_WIDTH = SCREEN_WIDTH / 6;
const int BUTTON_HEIGHT = SCREEN_HEIGHT / 6;
const int BUTTON_X = 450;
const int BUTTON_Y = 450;

class Button
{
    public:
        //init value
        Button();
        //deallocated memory
        ~Button();

         #if defined(SDL_TTF_MAJOR_VERSION)
        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
        #endif

        void free();

        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        void setBlendMod(SDL_BlendMode blending);

        void setAlpha(Uint8 alpha);

        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        SDL_Rect* Rect;
};

#endif // BUTTON_H
