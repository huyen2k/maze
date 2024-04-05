#include "Text.h"
#include "common.h"

Text::~Text(){
    SDL_DestroyTexture(Tex);
    Tex = nullptr;
}

bool Text::loadFromRenderedText(){
    //Render text surface

    g_font = TTF_OpenFont( "img/VNI-HelveB.ttf", sz);

    SDL_Surface* textSurface = TTF_RenderText_Solid( g_font, textureText.c_str(), textColor );
    if( textSurface == NULL ){
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else{
        //Create texture from surface pixels
        Tex = SDL_CreateTextureFromSurface( g_render, textSurface );
        if( Tex == NULL ){
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else{
            //Get image dimensions
            T_width = textSurface->w;
            T_height = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return Tex != NULL;
}

void Text::render( int x, int y, SDL_Rect* clip){
    if(!loadFromRenderedText()){
        printf("Error %s\n", TTF_GetError());
    };

    SDL_Rect renderQuad = { x, y, T_width, T_height };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy( g_render, Tex, clip, &renderQuad );
}

