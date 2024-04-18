#include "Button.h"

Button::~Button(){
    SDL_DestroyTexture(Tex);
    Tex = NULL;
}

bool Button::LoadImage(std::string path, SDL_Renderer* screen){
    SDL_Texture* new_texture = nullptr;

    SDL_Surface* load_surface = IMG_Load(path.c_str());

    if(load_surface != nullptr){
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        SDL_FreeSurface(load_surface);
    }
    Tex = new_texture;
    return Tex != nullptr;
}

void Button::hand_input(SDL_Event *e, SDL_Renderer* screen){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        int x, y;

        SDL_GetMouseState(&x, &y);

        bool inside = 1;

        if(x < Rect.x || x > Rect.x + Rect.w) inside = 0;
        if(y < Rect.y || y > Rect.y + Rect.h) inside = 0;

        if(inside){
            if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN){
                std::string pth = path + "_down.png";
                if(!LoadImage(pth, screen)){
                    printf("Have error with image in button %s\n", SDL_GetError());
                }
            }
            if(e->type == SDL_MOUSEBUTTONDOWN) check_enter = 1;
        }
        else {
            std::string pth = path + "_up.png";
            if(!LoadImage(pth, screen)){
                printf("Have error with image in button %s\n", SDL_GetError());
            }
        }
    }
}

void Button::render(SDL_Renderer *screen, SDL_Rect dsrect){
    SDL_RenderCopy(screen, Tex, NULL, &dsrect);
}

