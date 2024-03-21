#include "common.h"

SDL_Window* g_window = nullptr;
SDL_Renderer* g_render = nullptr;
SDL_Renderer* background = nullptr;
SDL_Rect wall[SCREEN_HEIGHT / rect_height][SCREEN_WIDTH / rect_width];
int visited[cntheight][cntwidth];
int dir[4] = {0, 1, 2, 3};

void quitSDL(){
    SDL_DestroyRenderer(g_render);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
}

bool initdata(){
    bool success = 1;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        g_window = SDL_CreateWindow("newhello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(g_window != nullptr){
            g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
        }
    }
    return success;
}

void basic_wall(){
    int xx = 0, yy = 0;
    for(int i = 0; i < cntheight; i ++){
        xx = 0;
        for(int j = 0; j < cntwidth; j ++){
            wall[i][j].x = xx;
            wall[i][j].y = yy;
            wall[i][j].h = rect_height;
            wall[i][j].w = rect_width;
            xx += rect_width;
            //std::cout << i << " " << j << " " << wall[i][j].x << " " << wall[i][j].y << '\n';
        }
        yy += rect_height;
    }
    memset(visited, 0, sizeof(visited));
    for(int i = 0; i < cntheight; i ++){
        visited[i][0] = visited[i][cntwidth - 1] = 1;
    }

    for(int i = 0; i < cntwidth; i ++){
        visited[0][i] = visited[cntheight - 1][i] = 1;
    }
}

bool inmaze(int x, int y){
    if(x < 0 || x >= cntwidth) return 0;
    if(y < 0 || y >= cntheight) return 0;
    return 1;
}

void fillscreen(SDL_Renderer* screen){
    for(int i = 1; i < cntheight - 1; i ++)
       for(int j = 1; j < cntwidth - 1; j ++){
            if(visited[i][j]) continue;
            SDL_SetRenderDrawColor( screen, 0, 0, 0, 0xFF );
            SDL_RenderFillRect(g_render, &wall[i][j]);
            //SDL_RenderPresent( g_render );
       }
    for(int i = 0; i < cntheight; i ++){
        //visited[i][0] = visited[i][cntwidth - 1] = 1;
        SDL_SetRenderDrawColor( screen, 0, 0xFF, 0, 0xFF );
        SDL_RenderFillRect(screen, &wall[i][0]);
        SDL_RenderFillRect(screen, &wall[i][cntwidth - 1]);
    }

    for(int i = 0; i < cntwidth; i ++){
        //visited[0][i] = visited[cntheight - 1][i] = 1;
        SDL_SetRenderDrawColor( screen, 0, 0xFF, 0, 0xFF );
        SDL_RenderFillRect(screen, &wall[0][i]);
        SDL_RenderFillRect(screen, &wall[cntheight - 1][i]);
    }
}

void maze(SDL_Renderer* screen){
    ii endd = {0, 0};
    vector<ii> st;
    st.push_back({1, 1});
    srand(time(0));
    int cnt = rand()% 100;
    fillscreen(screen);
    while(st.size()){
        srand(cnt ++);
        ii current = st.back();
        st.pop_back();

        SDL_SetRenderDrawColor( screen, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderFillRect(screen, &wall[current.first][current.second]);

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

            SDL_SetRenderDrawColor( screen, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderFillRect(screen, &wall[x2 - dx][y2 - dy]);
            visited[x2 - dx][y2 - dy] = 1;
            st.push_back({x2, y2});
        }
    }

    if(endd == ii(0, 0)){
        vector<int> tmpx;
        vector<int> tmpy;
        for(int i = cntheight / 2; i < cntheight - 1; i ++)
           for(int j = 1; j < cntwidth - 1; j ++){
                if(!visited[i][j]) continue;
                tmpx.push_back(i);
                tmpy.push_back(j);
           }
        int kx = rand() % (tmpx.size());
        kx = tmpx[kx];
        int ky = rand() % (tmpy.size());
        ky = tmpy[ky];
        SDL_SetRenderDrawColor( screen, 0, 0, 255, 0xFF );
        SDL_RenderFillRect(screen, &wall[kx][ky]);
        endd = {kx, ky};
    }
    for(int i = 0; i < cntheight; i ++){
        visited[i][0] = visited[i][cntwidth - 1] = 1;
    }

    for(int i = 0; i < cntwidth; i ++){
        visited[0][i] = visited[cntheight - 1][i] = 1;
    }
}

