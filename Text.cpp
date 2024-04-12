#include "Text.h"
#include "common.h"
#include "Button.h"

Text::~Text(){
    SDL_DestroyTexture(Tex);
    Tex = nullptr;
    TTF_CloseFont(g_font);
    g_font = nullptr;
}

bool Text::loadFromRenderedText(SDL_Renderer* screen){
    //Render text surface

    g_font = TTF_OpenFont( "img/Lato-BoldItalic.ttf", sz);

    SDL_Surface* textSurface = TTF_RenderText_Solid( g_font, textureText.c_str(), textColor );
    if( textSurface == NULL ){
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        cout << sz << '\n';
    }
    else{
        //Create texture from surface pixels
        Tex = SDL_CreateTextureFromSurface( screen, textSurface );
        if( Tex == NULL ){
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else{
            //Get image dimensions
            T_width = textSurface->w;
            T_height = textSurface->h;
//            cout << textSurface->w << " " << textSurface->h << '\n';
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return Tex != NULL;
}

void Text::render(SDL_Renderer* screen, SDL_Rect* src, SDL_Rect* dst){
    if(!loadFromRenderedText(screen)){
        printf("Error %s\n", TTF_GetError());
    };

    //Render to screen
    SDL_RenderCopy( screen, Tex, src, dst);
}

