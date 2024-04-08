#include "Fruit.h"

vector<SDL_Rect> list_food;

Fruit::Fruit(){
    Tex = nullptr;
}

Fruit::~Fruit(){
    SDL_DestroyTexture(Tex);
    Tex = nullptr;
}

void pre_image(){
    for(int i = 0; i < IMG_WIDTH; i += FRUIT_WIDTH)
    for(int j = 0; j < IMG_HEIGHT; j += FRUIT_HEIGHT){
        SDL_Rect tmp;
        tmp.x = i;
        tmp.y = j;
        tmp.w = FRUIT_WIDTH;
        tmp.h = FRUIT_HEIGHT;
        list_food.push_back(tmp);
    }
}

bool Fruit::LoadImage(std::string path, SDL_Renderer* screen){
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

void Fruit::render_img(SDL_Renderer* screen, int x, int y, SDL_Rect* clip){
    if(!LoadImage(src_img, screen)){
        printf("Have error with image in fruit %s\n", SDL_GetError());
    }
    SDL_Rect renderQuad = wall[x][y];

    //Render to screen
    SDL_RenderCopy(screen, Tex, clip, &renderQuad);
}
