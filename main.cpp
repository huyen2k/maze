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
    //maze();
    //main_character.init_data();
    bool quit = 0;
    SDL_Event e;
    int cnt = 0;

    while(!quit){
        //if(cnt ++ == 10) break;
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT) quit = 1;
            main_character.handinput(e);
        }
        //fillscreen();
        main_character.runAnimation(g_render, e);
        main_character.handrun(g_render);

        printf("%s\n", g_render);

        SDL_RenderPresent( g_render );
    }
    return 0;
}
