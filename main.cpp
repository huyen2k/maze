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
        {
            ifstream file("tutorial.txt");
            string s;
            getline(file, s);
//            cout << s << '\n';
            int color[4] = {116, 206, 236, 1};
            int color3[4] = {0, 0, 0, 1};

            Text tutorial(s, color, 26);

            Button start_button(BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
            int color2[4] = {0, 0, 0, 1};
            Text start_text("START", color, 26);

            SDL_Event e;
            int quit = 0;
            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT) quit = 1, out = 1;
                    start_button.hand_input(&e);
                }

                tutorial.render(0, 0);
                start_text.render(BUTTON_X, BUTTON_Y);

                SDL_RenderPresent(g_render);
                if(game_start) quit = 1;
            }

        }
        if(!game_start) continue;

        bool round = 0;
        SDL_Event e;
        while(!round){

            bool quit = 0;
            change_size(round_in);

            characer main_character;
            main_character.init_data();

            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT) quit = 1, out = 1, round = 1;
                    main_character.handinput(e);
                }

                {
                    SDL_SetRenderDrawColor(g_render, color_road[0], color_road[1], color_road[2], color_road[3] );
                    SDL_RenderClear(g_render);
                    maze(g_render);
                    main_character.runAnimation(g_render, e);
                }

                SDL_RenderPresent(g_render);

                if(main_character.check_win()) quit = 1;
            }
            SDL_RenderClear(g_render);
            round_in ++;
            if(round_in == 3) round = 1;
            //cout << round_in << '\n';
        }
        quitSDL();
    }
    return 0;
}
