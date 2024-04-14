#include "Score.h"

Score::Score(){
    Tex = NULL;
}

Score::~Score(){
    SDL_DestroyTexture(Tex);
    Tex = NULL;
}

bool Score::LoadImage(std::string path, SDL_Renderer* screen){
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

    for(int i = 0; i < number.size(); i ++){
        if(number[i] == '0'){
            LoadImage("img/number/0.png", screen);
            SDL_Rect renderQuad = {x, y, rect_width[round_in], rect_width[round_in]};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '1'){
            LoadImage("img/number/1.png", screen);
            SDL_Rect renderQuad = {x, y, rect_width[round_in], rect_width[round_in]};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '2'){
            LoadImage("img/number/2.png", screen);
            SDL_Rect renderQuad = {x, y, rect_width[round_in], rect_width[round_in]};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '3'){
            LoadImage("img/number/3.png", screen);
            SDL_Rect renderQuad = {x, y, rect_width[round_in], rect_width[round_in]};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '4'){
            LoadImage("img/number/4.png", screen);
            SDL_Rect renderQuad = {x, y, rect_width[round_in], rect_width[round_in]};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '5'){
            LoadImage("img/number/5.png", screen);
            SDL_Rect renderQuad = {x, y, rect_width[round_in], rect_width[round_in]};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '6'){
            LoadImage("img/number/6.png", screen);
            SDL_Rect renderQuad = {x, y, rect_width[round_in], rect_width[round_in]};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '7'){
            LoadImage("img/number/7.png", screen);
            SDL_Rect renderQuad = {x, y, rect_width[round_in], rect_width[round_in]};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '8'){
            LoadImage("img/number/8.png", screen);
            SDL_Rect renderQuad = {x, y, rect_width[round_in], rect_width[round_in]};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        else if(number[i] == '9'){
            LoadImage("img/number/9.png", screen);
            SDL_Rect renderQuad = {x, y, rect_width[round_in], rect_width[round_in]};
            SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
        }
        x += rect_width[round_in] / 2;
    }

}
