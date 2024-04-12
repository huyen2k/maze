#include "Button.h"

Button::~Button(){
    //dtor
}

void Button::hand_input(SDL_Event *e){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        int x, y;

        SDL_GetMouseState(&x, &y);

        bool inside = 1;

        if(x < Rect.x || x > Rect.x + Rect.w) inside = 0;
        if(y < Rect.y || y > Rect.y + Rect.h) inside = 0;

        if(inside){
            for(int i = 0; i < 4; i ++)
                color_button[i] = color_button_down[i];
            if(e->type == SDL_MOUSEBUTTONDOWN) check_enter = 1;
        }
        else {
            for(int i = 0; i < 4; i ++)
                color_button[i] = color_button_up[i];
        }
    }
}

void Button::render(SDL_Renderer *screen){
    SDL_SetRenderDrawColor( screen, color_button[0], color_button[1], color_button[2], color_button[3]);
    SDL_RenderFillRect(screen, &Rect);
}

