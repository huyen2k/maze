#include "characer.h"
#include "common.h"

SDL_Rect running_clip[total][cnt_frame];
int step_x = 0, step_y = 0;
int current_x = 1, current_y = 1;


void init_data(){
    for(int type = 0; type < total; type ++){
        int cnt = 0;
        for(int i = 0; i < cnt_frame; i ++){
            running_clip[type][i].x = cnt;
            running_clip[type][i].y = 0;
            running_clip[type][i].w = rect_width;
            running_clip[type][i].h = rect_height;
            cnt += rect_width;
        }
    }
}

characer::characer(){
    Texture_ = nullptr;
    type = 1;
}

characer::~characer(){
    //dtor
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
    bool ok = 1;
    switch (type){
        case 0:
            ok &= LoadImage(frame_up, screen);
            break;
        case 1:
            ok &= LoadImage(frame_left, screen);
            break;
        case 2:
            ok &= LoadImage(frame_down, screen);
            break;
        case 3:
            ok &= LoadImage(frame_right, screen);
            break;
    }
    SDL_Rect renderQuad = wall[x][y];

    //Render to screen
    SDL_RenderCopy(screen, Texture_, clip, &renderQuad);
}

void characer::runAnimation(SDL_Renderer* screen, SDL_Event event){
    if(event.type == SDL_QUIT) return ;
    static int frame = 0;
    SDL_SetRenderDrawColor(g_render, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, 0xFF );
    SDL_RenderClear(screen);
    maze(screen);

    SDL_Rect* currentClip = &running_clip[type][ frame / 4 ];
    Render(screen, current_x, current_y, currentClip);

    SDL_RenderPresent(screen);
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
    step_x = 0, step_y = 0;
    if(e.type == SDL_KEYDOWN){
        switch (e.key.keysym.sym){
            case SDLK_UP:
                step_x -= 1;
                type = 0;
                break;
            case SDLK_DOWN:
                step_x += 1;
                type = 2;
                break;
            case SDLK_RIGHT:
                step_y += 1;
                type = 3;
                break;
            case SDLK_LEFT:
                step_y -= 1;
                type = 1;
                break;
        }
    }
//    else if(e.type == SDL_KEYUP){
//        switch (e.key.keysym.sym){
//            case SDLK_UP:
//                step_y += 1;
//                break;
//            case SDLK_DOWN:
//                step_y -= 1;
//                break;
//            case SDLK_LEFT:
//                step_x += 1;
//                break;
//            case SDLK_RIGHT:
//                step_x -= 1;
//                break;
//        }
//    }
    current_x += step_x;
    current_y += step_y;
    if(!visited[current_x][current_y] || current_x == 0 || current_x == cntheight - 1 ||
       current_y == 0 || current_y == cntwidth - 1) current_x -= step_x, current_y -= step_y;
}
