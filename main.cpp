#include "common.h"
#include "characer.h"
#include "Button.h"
#include "menu.h"
#include "Score.h"
#include "Oneplayer.h"

using namespace std;

int main(int argc, char ** argv)
{
    if(!initdata()) {
        cout << "ERROR\n";
        return 0;
    }
    bool out = 0;
    game_start = 0;
    bool round = 1;
    while(!out){

        if(!game_start){
            if(!update_start(g_render)) break;
        }

        score = 0;

        Oneplayer play1;
        play1.gameplay(g_render, round, out, score);

        bool ok = update_gameover(g_render);
        if(!ok)break;
        round_in = 0;
        round = 0;
    }
    quitSDL();
    return 0;
}
