#include "characer.h"
#include "common.h"

SDL_Rect running_clip[total][cnt_frame];
int step_x = 0, step_y = 0;
int current_x = 1, current_y = 1;

void init_data(){
    for(int type = 0; type < total; type ++){
        int cnt = 0;
        for(int i = 0; i < 6; i ++){
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
        //printf("checking renderer %s\n", screen);
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        //printf("checking renderer %s\n", screen);
        //printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        if(new_texture != nullptr){
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    Texture_ = new_texture;
    return Texture_ != nullptr;
}

void characer::Render(SDL_Renderer* screen, int x, int y, SDL_Rect* clip){
    //Set rendering space and render to screen
    switch (type){
        case 0:
            LoadImage(frame_up, screen);
            break;
        case 1:
            LoadImage(frame_left, screen);
            break;
        case 2:
            LoadImage(frame_down, screen);
            break;
        case 3:
            LoadImage(frame_right, screen);
            break;
    }
    SDL_Rect renderQuad = wall[x][y];
    //cout << renderQuad.x << " " << renderQuad.y << '\n';

    //Render to screen
    SDL_RenderCopy(screen, Texture_, clip, &renderQuad);
    printf("checking renderer %s\n", screen);
}

void characer::runAnimation(SDL_Renderer* screen, SDL_Event event){
    if(event.type == SDL_QUIT) return ;
    static int frame = 0;
    SDL_SetRenderDrawColor(g_render, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, 0xFF );
    SDL_RenderClear(screen);

    SDL_Rect* currentClip = &running_clip[type][ frame / 4 ];
    Render(screen, current_x, current_x, currentClip);
    //printf("%d %d\n", current_x, current_y);

    SDL_RenderPresent(g_render);
    //Go to next frame
    ++frame;
    //printf("frame is %d\n", frame);
    //Cycle animation
    if(frame / 4 >= cnt_frame)
    {
        frame = 0;
    }
}

void characer::handinput(SDL_Event e){
    if(e.type == SDL_KEYDOWN){
        switch (e.key.keysym.sym){
            case SDLK_w:
                step_y -= 1;
                type = 0;
                break;
            case SDLK_s:
                step_y += 1;
                type = 2;
                break;
            case SDLK_a:
                step_x -= 1;
                type = 3;
                break;
            case SDLK_d:
                step_x += 1;
                type = 1;
                break;
        }
    }
    else if(e.type == SDL_KEYUP){
        switch (e.key.keysym.sym){
            case SDLK_w:
                step_y += 1;
                break;
            case SDLK_s:
                step_y -= 1;
                break;
            case SDLK_a:
                step_x += 1;
                break;
            case SDLK_d:
                step_x -= 1;
                break;
        }
    }
}

void characer::handrun(SDL_Renderer* screen){
    current_x += step_x;
    current_y += step_y;
    if(!visited[current_x][current_y]) current_x -= step_x, current_y -= step_y;
}
