#include "menu.h"
#include "Button.h"

menu::~menu()
{
    SDL_DestroyTexture(Tex);
    Tex = NULL;
}

bool menu::LoadImage(SDL_Renderer* screen){
    SDL_Texture* new_texture = nullptr;

    SDL_Surface* load_surface = IMG_Load(path.c_str());

    if(load_surface != nullptr){
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if(load_surface != NULL){
            I_w = load_surface->w;
            I_h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    Tex = new_texture;
    return Tex != nullptr;
}

void menu::render(SDL_Renderer* screen, int x, int y){

    SDL_Rect renderQuad = {x, y, I_w, I_h};

    SDL_RenderCopy(screen, Tex, NULL, &renderQuad);
}

bool update_start(SDL_Renderer* screen){

    SDL_Rect start_rect = {242, 463, 279, 108};
    Button start_button("img/menu/start", start_rect);

    SDL_Event e;
    int quit = 0;
    menu mm(main_img);
    if(!mm.LoadImage(screen)){
        printf("Have error with image in menu %s\n", SDL_GetError());
    }
    while(!quit && !game_start){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                return 0;
            }
            start_button.hand_input(&e, g_render);
            if(start_button.check_enter) game_start = 1;
        }
        mm.render(g_render, 0, 0);
        start_button.render(g_render, start_rect);
        SDL_RenderPresent(g_render);
    }
    return 1;
}

//bool update_gameover(SDL_Renderer* screen){
//
//    menu mm(gameover_img);
//    Button playagain_button(185 + 52, 260 + 170, 129, 40);
//    Button quit_button(185 + 292, 260 + 170, 58, 40);
//
//    SDL_Event e;
//    int quit = 0;
//    while(!quit){
//        while(SDL_PollEvent(&e) != 0){
//            if(e.type == SDL_QUIT){
//                return 0;
//            }
//            playagain_button.hand_input(&e);
//            if(playagain_button.check_enter) return 1;
//            quit_button.hand_input(&e);
//            if(quit_button.check_enter) return 0;
//        }
//        mm.render(g_render, 185, 260);
//
//        SDL_RenderPresent(g_render);
//    }
//    return 1;
//}
//
//bool update_gamewin(SDL_Renderer* screen){
//
//    menu mm(gamewin_img);
//    Button playagain_button(185 + 52, 260 + 170, 129, 40);
//    Button quit_button(185 + 292, 260 + 170, 58, 40);
//
//    SDL_Event e;
//    int quit = 0;
//    while(!quit){
//        while(SDL_PollEvent(&e) != 0){
//            if(e.type == SDL_QUIT){
//                return 0;
//            }
//            playagain_button.hand_input(&e);
//            if(playagain_button.check_enter) return 1;
//            quit_button.hand_input(&e);
//            if(quit_button.check_enter) return 0;
//        }
//        mm.render(g_render, 185, 260);
//
//        SDL_RenderPresent(g_render);
//    }
//    return 1;
//}
//
