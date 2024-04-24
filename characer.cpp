#include "characer.h"

SDL_Rect running_clip[total][cnt_frame];

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
    SDL_DestroyTexture(Texture_);
    Texture_ = NULL;
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

    SDL_Rect renderQuad = wall[x][y];

    //Render to screen
    SDL_RenderCopy(screen, Texture_, clip, &renderQuad);
    //printf("check render %s\n", screen);
}

void characer::runAnimation(SDL_Renderer* screen, SDL_Event event){
    if(event.type == SDL_QUIT) return ;
    static int frame = 0;

    SDL_Rect* currentClip = &running_clip[type][ frame / 9 ]; // Divide by cnt_frame + 1 so the image runs circularly
    Render(screen, current_x, current_y, currentClip);

    //Go to next frame
    ++frame;

    //Cycle animation
    if(frame / 9 >= cnt_frame)
    {
        frame = 0;
    }
}

void characer::handinput(SDL_Event e, SDL_Renderer* screen){
    // do di theo bang 2D nen current_x -> row
    // do di theo bang 2D nen current_y -> col
    has_postion1[current_x][current_y] = 0;

    int ktype = -1;
    if(e.type == SDL_KEYDOWN){
        switch (e.key.keysym.sym){
            case SDLK_w:
                ktype = 0;
                type = 0;
                break;
            case SDLK_s:
                type = 2;
                ktype = 2;
                break;
            case SDLK_d:
                type = 3;
                ktype = 3;
                break;
            case SDLK_a:
                type = 1;
                ktype = 1;
                break;
        }
    }

    if(!LoadImage(frame_img[type], screen)){
        printf("Have error with image %s\n", SDL_GetError());
    }

    handrun(ktype);

    if(has_food[current_x][current_y].first){
        has_point[current_x][current_y] = 1;
        Mix_PlayChannel( -1, g_eatfood, 0 );
        score += 5;
        has_postion1[current_x][current_y] = 0;
        srand(time(0));
        int k = rand() % int(list_road.size() - 1);
        has_food[current_x][current_y].first = 0;
        has_food[current_x][current_y].second = -1;
        current_x = list_road[k].first;
        current_y = list_road[k].second;
        has_postion1[current_x][current_y] = 1;
    }
    if(!has_point[current_x][current_y]){
        Mix_PlayChannel( -1, g_eatdot, 0 );
        score += 1;
        has_point[current_x][current_y] = 1;
    }
    has_postion1[current_x][current_y] = 1;

}

void characer::handrun(int type){
    if(type == -1) return;

    current_x += step_x[type];
    current_y += step_y[type];
    if(!visited[current_x][current_y] || current_x == 0 || current_x == cntheight - 1 ||
       current_y == 0 || current_y == cntwidth - 1)
       current_x -= step_x[type], current_y -= step_y[type];

}

