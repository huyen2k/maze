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

void Text::render( SDL_Renderer* screen, int x, int y, SDL_Rect* clip){
    if(!loadFromRenderedText(screen)){
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
    SDL_RenderCopy( screen, Tex, clip, &renderQuad );
}

bool update_start(SDL_Renderer* screen){
    int color_tutorial[4] = {0, 246, 255, 1};
    int color_start[4] = {255, 0, 0, 1};

    Button start_button(BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
    Text start_text("START", color_start, 46);

    SDL_Event e;
    int quit = 0;
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                return 0;
            }
            start_button.hand_input(&e);
        }
        ifstream file("tutorial.txt");
        string s;
//        SDL_SetRenderDrawColor( screen, 0, 0, 255, 0);
//        SDL_RenderClear( screen );
        int beg = 0;
        for(int i = 0; i < 2; i ++){
            getline(file, s);
            Text tutorial(s, color_tutorial, 30);
            tutorial.render(screen, 0, beg);
            beg += tutorial.getHeight();

        }
        start_text.render(screen, BUTTON_X, BUTTON_Y);

        SDL_RenderPresent(g_render);
        if(game_start) return 1;
    }
    return 1;
}

