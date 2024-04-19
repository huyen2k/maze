#include "Oneplayer.h"

Oneplayer::Oneplayer()
{
    //ctor
}

Oneplayer::~Oneplayer()
{
    //dtor
}

void Oneplayer::gameplay(SDL_Renderer* g_render, bool &round, bool &out, int &score){
    SDL_Event e;

    while(!round){

        bool quit = 0;
        change_size(round_in);

        Score scr(rect_width[round_in]);
        characer main_character;
        main_character.init_data();
        maze(g_render);

        while(!quit){
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT){
                    round = 1;
                    return;
                }
                main_character.handinput(e, g_render);

            }

            {
                SDL_SetRenderDrawColor(g_render, color_road[0], color_road[1], color_road[2], color_road[3] );
                SDL_RenderClear(g_render);
                fillscreen(g_render);
                scr.render(g_render, 0, 0);
                scr.render_number(g_render, rect_width[round_in] * 3, 0, score);
                main_character.runAnimation(g_render, e);
            }

            SDL_RenderPresent(g_render);

            if(main_character.check_win()) quit = 1;
            main_character.check_food();
        }
        round_in ++;
        if(round_in == 3) round = 1;
        if(round) break;
    }
}
