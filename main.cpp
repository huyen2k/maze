#include "common.h"

using namespace std;
using ii = pair<int, int>;

int main(int argc, char ** argv)
{
    if(!initdata()) {
        cout << "ERROR\n";
        return 0;
    }
    basic_wall();
    bool quit = 0;
    SDL_Event e;
    vector<ii> st;
    st.push_back({1, 1});

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT) quit = 1;
        }
        srand(time(0));
        for(int i = 1; i < cntheight - 1; i ++)
           for(int j = 1; j < cntwidth - 1; j ++){
                if(visited[i][j]) continue;
                SDL_SetRenderDrawColor( g_render, 0, 0, 0, 0xFF );
                SDL_RenderFillRect(g_render, &wall[i][j]);
                //SDL_RenderPresent( g_render );
           }
        for(int i = 0; i < cntheight; i ++){
            SDL_SetRenderDrawColor( g_render, 0, 0xFF, 0, 0xFF );
            SDL_RenderFillRect(g_render, &wall[i][0]);
            SDL_RenderFillRect(g_render, &wall[i][cntwidth - 1]);
        }

        for(int i = 0; i < cntwidth; i ++){
            SDL_SetRenderDrawColor( g_render, 0, 0xFF, 0, 0xFF );
            SDL_RenderFillRect(g_render, &wall[0][i]);
            SDL_RenderFillRect(g_render, &wall[cntheight - 1][i]);
        }
        if(st.size()){

            ii current = st.back();
            st.pop_back();

            SDL_SetRenderDrawColor( g_render, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderFillRect(g_render, &wall[current.first][current.second]);
            SDL_RenderPresent( g_render );

            visited[current.first][current.second] = 1;
            for(int i = 0; i < 4; i ++){
                int r = rand() % 3;
                swap(dir[i], dir[r]);
            }
            for(int i = 0; i < 4; i ++){
                int dx = 0, dy = 0;
                switch (dir[i]){
                    case 0: dy -= 1; break;
                    case 1: dx += 1; break;
                    case 2: dy += 1; break;
                    case 3: dx -= 1; break;
                }
                int x2 = current.first + dx * 2;
                int y2 = current.second + dy * 2;
                if(!inmaze(x2, y2)) continue;
                if(visited[x2][y2]) continue;
                visited[x2][y2] = 1;
                //st.push_back({current.first, current.second});

                SDL_SetRenderDrawColor( g_render, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderFillRect(g_render, &wall[x2 - dx][y2 - dy]);
                visited[x2 - dx][y2 - dy] = 1;
                st.push_back({x2, y2});
            }
        }
        SDL_RenderPresent( g_render );
    }
    return 0;
}
