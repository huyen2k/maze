#include "Score.h"

Score::Score(int sz_){
    Tex = NULL;
    sz = sz_;
}

Score::~Score(){
    SDL_DestroyTexture(Tex);
    Tex = NULL;
}

bool Score::LoadImage(std::string path, SDL_Renderer* screen){
    SDL_DestroyTexture(Tex);
    Tex = NULL;
    SDL_Texture* new_texture = nullptr;

    SDL_Surface* load_surface = IMG_Load(path.c_str());

    if(load_surface != nullptr){
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if(load_surface != NULL){
            n_width = load_surface->w;
            n_height = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    Tex = new_texture;
    return Tex != nullptr;
}

void Score::render(SDL_Renderer* screen, int x, int y){
    if(!LoadImage(src_score, screen)){
        printf("Have error with image in score %s\n", SDL_GetError());
    }
    SDL_Rect renderQuad = {x, y, rect_width[round_in] * 3, rect_width[round_in]};

    SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
}

void Score::render_number(SDL_Renderer* screen, int x, int y, int score){

    string number = std::to_string(score);
//    cout << score << '\n';
    for(int i = 0; i < number.size(); i ++){
        if(number[i] == '0'){
            if(!LoadImage("img/number/0.png", screen)){
                printf("Have error with image in number 0 %s\n", SDL_GetError());
            }
            SDL_Rect renderQuad = {x, y, sz, sz};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '1'){
            if(!LoadImage("img/number/1.png", screen)){
                printf("Have error with image in number 1 %s\n", SDL_GetError());
            }
            SDL_Rect renderQuad = {x, y, sz, sz};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '2'){
            if(!LoadImage("img/number/2.png", screen)){
                printf("Have error with image in number 2 %s\n", SDL_GetError());
            }
            SDL_Rect renderQuad = {x, y, sz, sz};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '3'){
            if(!LoadImage("img/number/3.png", screen)){
                printf("Have error with image in number 3 %s\n", SDL_GetError());
            }
            SDL_Rect renderQuad = {x, y, sz, sz};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '4'){
            if(!LoadImage("img/number/4.png", screen)){
                printf("Have error with image in number 4 %s\n", SDL_GetError());
            }
            SDL_Rect renderQuad = {x, y, sz, sz};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '5'){
            if(!LoadImage("img/number/5.png", screen)){
                printf("Have error with image in number 5 %s\n", SDL_GetError());
            }
            SDL_Rect renderQuad = {x, y, sz, sz};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '6'){
            if(!LoadImage("img/number/6.png", screen)){
                printf("Have error with image in number 6 %s\n", SDL_GetError());
            }
            SDL_Rect renderQuad = {x, y, sz, sz};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '7'){
            if(!LoadImage("img/number/7.png", screen)){
                printf("Have error with image in number 7 %s\n", SDL_GetError());
            }
            SDL_Rect renderQuad = {x, y, sz, sz};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '8'){
            if(!LoadImage("img/number/8.png", screen)){
                printf("Have error with image in number 8 %s\n", SDL_GetError());
            }
            SDL_Rect renderQuad = {x, y, sz, sz};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '9'){
            if(!LoadImage("img/number/9.png", screen)){
                printf("Have error with image in number 9 %s\n", SDL_GetError());
            }
            SDL_Rect renderQuad = {x, y, sz, sz};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        x += sz / 1;
    }

}
