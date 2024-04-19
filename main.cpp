#include "common.h"
#include "characer.h"
#include "Button.h"
#include "menu.h"
#include "Score.h"
#include "Oneplayer.h"
#include "Twoplayer.h"

using namespace std;

int main(int argc, char ** argv)
{
    if(!initdata()) {
        cout << "ERROR\n";
        return 0;
    }
    bool out = 0;
    bool round = 0;
    while(!out){

        int game_mode = update_start(g_render);
        if(game_mode == 0) break;
        else if(game_mode == 1) {
            Oneplayer play1;
            play1.gameplay(g_render, round, out);
        }
        else {
            Twoplayer play2;
            play2.gameplay(g_render, round, out);
        }
    }
    quitSDL();
    return 0;
}
