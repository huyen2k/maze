#include "common.h"
#include "characer.h"
#include "Text.h"
#include "Button.h"

using namespace std;

int main(int argc, char ** argv)
{

    bool out = 0;
    while(!out){
        if(!initdata()) {
            cout << "ERROR\n";
            return 0;
        }
        game_start = 0;
        if(!update_start(g_render)) break;

        if(!game_start) continue;

        bool round = 0;
        SDL_Event e;
        while(!round){

            bool quit = 0;
            change_size(round_in);

            characer main_character;
            main_character.init_data();
            maze(g_render);
//            int color[] = {0, 0, 0, 1};

//            Text scr("SCORE: ", color, rect_height[round_in]);

            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT) quit = 1, out = 1, round = 1;
                    main_character.handinput(e);
                }

                {
                    SDL_SetRenderDrawColor(g_render, color_road[0], color_road[1], color_road[2], color_road[3] );
                    SDL_RenderClear(g_render);
                    fillscreen(g_render);
                    main_character.runAnimation(g_render, e);
//                    scr.render(g_render, 0, 0);
                }

                SDL_RenderPresent(g_render);

                if(main_character.check_win()) quit = 1;
                main_character.check_food();
            }
            SDL_RenderClear(g_render);
            round_in ++;
            if(round_in == 3) round = 1;
            //cout << round_in << '\n';
        }

        if(!update_playagain(g_render))break;

        quitSDL();
    }
    return 0;
}
