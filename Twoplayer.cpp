#include "Twoplayer.h"

int score2;

Twoplayer::Twoplayer()
{
    //ctor
}

Twoplayer::~Twoplayer()
{
    //dtor
}

void Twoplayer::gameplay(SDL_Renderer* g_render, bool &round, bool &out){
    SDL_Event e;
    score2 = 0;
    score = 0;
    while(!round){

        bool quit = 0;
        change_size(round_in);

        Score scr(rect_width[round_in]);
        Score scr2(rect_width[round_in]);
        characer character1;
        Character2 character2;
        character1.init_data();
        character2.init_data();
        maze(g_render);

        while(!quit){
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT){
                    round = 1;
                    break;
                }
                character1.handinput(e, g_render);
                character2.handinput(e, g_render);
            }

            if(round) break;
            {
                SDL_SetRenderDrawColor(g_render, color_road[0], color_road[1], color_road[2], color_road[3] );
                SDL_RenderClear(g_render);
                fillscreen(g_render);

                scr.render(g_render, 0, 0);
                scr.render_number(g_render, rect_width[round_in] * 3, 0, score);
                int cnt = std::to_string(score2).size();
                scr2.render(g_render, SCREEN_WIDTH - rect_width[round_in] * (cnt + 3), 0);
                scr2.render_number(g_render, SCREEN_WIDTH - rect_width[round_in] * cnt, 0, score2);

                character1.runAnimation(g_render, e);
                character2.runAnimation(g_render, e);
            }

            SDL_RenderPresent(g_render);

            if(character1.check_win()){
                quit = 1;
                score += 50;
            }
            else if(character2.check_win()){
                quit = 1;
                score2 += 50;
            }
        }
        round_in ++;
        if(round_in == 3) round = 1;
        if(round) break;
    }

    if(!update_gameover(g_render, 2, score, score2)) out = 1;
    else {
        round_in = 0;
        round = 0;
        game_start = 0;
    }
}
