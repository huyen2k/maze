#include "common.h"
#include "characer.h"

using namespace std;

int main(int argc, char ** argv)
{
    if(!initdata()) {
        cout << "ERROR\n";
        return 0;
    }
    characer main_character;
    basic_wall();
    main_character.init_data();
    bool quit = 0;
    SDL_Event e;

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT) quit = 1;
            main_character.handinput(e);
        }
        main_character.runAnimation(g_render, e);
        SDL_RenderPresent(g_render);

    }
    return 0;
}
