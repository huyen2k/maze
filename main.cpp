#include "common.h"
#include "characer.h"

using namespace std;

int main(int argc, char ** argv)
{
    bool out = 0;
    while(!out){
        if(round_in == 3) break;
        if(!initdata()) {
            cout << "ERROR\n";
            return 0;
        }
        bool quit = 0;
        SDL_Event e;

        change_size();
        //printf("round in %d\n", round_in);
        characer main_character;
        main_character.init_data();

        while(!quit){
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT) quit = 1, out = 1;
                main_character.handinput(e);
            }

            main_character.runAnimation(g_render, e);

            SDL_RenderPresent(g_render);

            if(main_character.check_win()) quit = 1;
        }
        SDL_RenderClear(g_render);
        round_in ++;
        quitSDL();
    }
    return 0;
}
