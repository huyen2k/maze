#include "menu.h"
#include "Button.h"
#include "Score.h"

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

int update_start(SDL_Renderer* screen){

    SDL_Rect start_rect1 = {242, 463, 279, 108};
    Button start_1player("img/menu/player1", start_rect1);

    SDL_Rect start_rect2 = {242, 463 + 108 + 20, 279, 108};
    Button start_2player("img/menu/player2", start_rect2);

    SDL_Event e;
    int quit = 0;
    menu mm(main_img);
    if(!mm.LoadImage(screen)){
        printf("Have error with image in menu %s\n", SDL_GetError());
    }
    while(!quit && !game_start){
//        if(Mix_PlayMusic(gMusic, 0) == -1)
//            cout << "error\n";
//        Mix_PlayMusic(gMusic, -1);
        //Mix_PlayChannel(-1, g_music, -1);
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                Mix_HaltMusic();
                return 0;
            }
            start_1player.hand_input(&e, g_render);
            start_2player.hand_input(&e, g_render);
            if(start_1player.check_enter){
                game_start = 1;
                //Mix_HaltMusic();
                //Mix_PauseMusic();
                return 1;
            }
            if(start_2player.check_enter){
                game_start = 1;
                //Mix_HaltMusic();
                //Mix_PauseMusic();
                return 2;
            }
        }
        mm.render(g_render, 0, 0);
        start_1player.render(g_render, start_rect1);
        start_2player.render(g_render, start_rect2);
        SDL_RenderPresent(g_render);
    }
    return 0;
}

bool update_gameover(SDL_Renderer* screen, int game_mode, int score1, int score2, bool game_win){

    SDL_Rect playagain_rect = {195, 400, 200, 60};
    Button playagain_button("img/menu/playagain", playagain_rect);

    SDL_Rect quit_rect = {395, 400, 200, 60};
    Button quit_button("img/menu/quit", quit_rect);

    menu game2score("img/menu/game2score.png");
    game2score.I_h = 100, game2score.I_w = 390;

    SDL_Event e;
    int quit = 0;
    menu mm(gameover_img);
    menu mmm("img/menu/game_win.png");
    if(!mm.LoadImage(screen)){
        printf("Have error with image in menu %s\n", SDL_GetError());
    }
    if(!mmm.LoadImage(screen)){
        printf("Have error with image in menu %s\n", SDL_GetError());
    }
    if(!game2score.LoadImage(screen)){
        printf("Have error with image in menu %s\n", SDL_GetError());
    }
    Score srcdes(30);
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                return 0;
            }
            playagain_button.hand_input(&e, g_render);
            if(playagain_button.check_enter) return 1;

            quit_button.hand_input(&e, g_render);
            if(quit_button.check_enter) return 0;
        }

        if(!game_win) mm.render(g_render, -5, -3);
        else mmm.render(g_render, -5, -3);
        if(game_mode == 2){
            game2score.render(g_render, 200, 300);
            srcdes.render_number(g_render, 260, 354, score1);
            srcdes.render_number(g_render, 465, 354, score2);
        }
        else {
            srcdes.render_number(g_render, 430, 345, score);
        }
        playagain_button.render(g_render, playagain_rect);
        quit_button.render(g_render, quit_rect);
        SDL_RenderPresent(g_render);
    }
    return 1;
}

