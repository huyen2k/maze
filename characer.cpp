#include "characer.h"
#include "common.h"

SDL_Rect running_clip[roundplay][total][cnt_frame];

characer::characer(){
    Texture_ = nullptr;
    type = 3;
    current_x = 1, current_y = 1;
    dir = -1;
}

characer::~characer(){
    SDL_DestroyTexture(Texture_);
}

bool characer::LoadImage(std::string path, SDL_Renderer* screen){
    SDL_Texture* new_texture = nullptr;

    SDL_Surface* load_surface = IMG_Load(path.c_str());

    if(load_surface != nullptr){
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        SDL_FreeSurface(load_surface);
    }
    Texture_ = new_texture;
    return Texture_ != nullptr;
}

void characer::Render(SDL_Renderer* screen, int x, int y, SDL_Rect* clip){
    if(!LoadImage(frame_img[round_in][type], screen)){
        printf("Have error with image %s\n", SDL_GetError());
    }
    SDL_Rect renderQuad = wall[x][y];

    //Render to screen
    SDL_RenderCopy(screen, Texture_, clip, &renderQuad);
    //printf("check render %s\n", screen);
}

void characer::runAnimation(SDL_Renderer* screen, SDL_Event event){
    if(event.type == SDL_QUIT) return ;
    static int frame = 0;

    SDL_Rect* currentClip = &running_clip[round_in][type][ frame / 4 ]; // Divide by cnt_frame + 1 so the image runs circularly
    Render(screen, current_x, current_y, currentClip);
    has_point[current_x][current_y] = 1;

//    SDL_RenderPresent(screen);
    //Go to next frame
    ++frame;

    //Cycle animation
    if(frame / 4 >= cnt_frame)
    {
        frame = 0;
    }
}

void characer::handinput(SDL_Event e){
    // do di theo bang 2D nen current_x -> row
    // do di theo bang 2D nen current_y -> col
    int ktype = -1;
    if(e.type == SDL_KEYDOWN){
        switch (e.key.keysym.sym){
            case SDLK_UP:
                ktype = 0;
                type = 0;
                break;
            case SDLK_DOWN:
                type = 2;
                ktype = 2;
                break;
            case SDLK_RIGHT:
                type = 3;
                ktype = 3;
                break;
            case SDLK_LEFT:
                type = 1;
                ktype = 1;
                break;
        }
    }

    handrun(ktype);
}

void characer::handrun(int type){
    if(type == -1) return;
//    static int cnt = 0;

//    if(cnt / 4 >= 4) {
//        cnt = 0;
//        return;
//    }
//    ++cnt;

    current_x += step_x[type];
    current_y += step_y[type];
    if(!visited[current_x][current_y] || current_x == 0 || current_x == cntheight - 1 ||
       current_y == 0 || current_y == cntwidth - 1) current_x -= step_x[type], current_y -= step_y[type];
}

