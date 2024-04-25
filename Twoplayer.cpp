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
    bool game_win = 0;
    while(!round){

        int _time = 0;
        int time_out = max_time[round_in];
        bool quit = 0;
        change_size(round_in);

        Score time(rect_width[round_in]);
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

            _time ++;
            if(time_out == 0){
                round = 1;
                break;
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

                int time_now = (_time) % 100;
                if(!time_now) time_out --;
                time.render_number(g_render, rect_width[round_in] * (cntwidth / 2), 0, time_out);
            }

            SDL_RenderPresent(g_render);

            if(character1.check_win()){
                quit = 1;
                score += 50;
                game_win = 1;
            }
            else if(character2.check_win()){
                quit = 1;
                score2 += 50;
                game_win = 1;
            }
            else game_win = 0;
        }
        round_in ++;
        if(round_in == 3) round = 1;
        if(round) break;
    }

    if(!update_gameover(g_render, 2, score, score2, game_win)) out = 1;
    else {
        round_in = 0;
        round = 0;
        game_start = 0;
    }
}
