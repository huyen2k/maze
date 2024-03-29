#include "common.h"

SDL_Window* g_window = nullptr;
SDL_Renderer* g_render = nullptr;
vector<vector<int> > visited;
vector<vector<SDL_Rect> > wall;
int cntheight, cntwidth;
int dir[4] = {0, 1, 2, 3};
int rannum;
ii endgame;
int round_in = 0;

void change_size(){
    cntheight = SCREEN_HEIGHT / rect_height[round_in];
    cntwidth = SCREEN_WIDTH / rect_width[round_in];
    visited.clear();
    visited.resize(cntheight, vector<int> (cntwidth));
    for(int i = 0; i < cntheight; i ++)
        for(int j = 0; j < cntwidth; j ++)
        visited[i][j] = 0;
    wall.clear();
    wall.resize(cntheight, vector<SDL_Rect> (cntwidth));
    int xx = 0, yy = 0;
    for(int i = 0; i < cntheight; i ++){
        xx = 0;
        for(int j = 0; j < cntwidth; j ++){
            wall[i][j].x = xx;
            wall[i][j].y = yy;
            wall[i][j].h = rect_height[round_in];
            wall[i][j].w = rect_width[round_in];
            xx += rect_width[round_in];
            //std::cout << i << " " << j << " " << wall[i][j].x << " " << wall[i][j].y << '\n';
        }
        yy += rect_height[round_in];
    }
}

void quitSDL(){
    SDL_DestroyRenderer(g_render);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    g_render = nullptr;
    g_window = nullptr;
}

bool initdata(){
    srand(time(0));
    rannum = rand() % 30;
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

bool inmaze(int x, int y){
    if(x < 0 || x >= cntwidth) return 0;
    if(y < 0 || y >= cntheight) return 0;
    return 1;
}

void fillscreen(SDL_Renderer* screen){
    for(int i = 1; i < cntheight - 1; i ++)
       for(int j = 1; j < cntwidth - 1; j ++){
            if(visited[i][j]) continue;
            SDL_SetRenderDrawColor( screen, color_wall[0], color_wall[1], color_wall[2], color_wall[3]);
            SDL_RenderFillRect(g_render, &wall[i][j]);
       }
    for(int i = 0; i < cntheight; i ++){
        SDL_SetRenderDrawColor( screen, color_border[0], color_border[1], color_border[2], color_border[3]);
        SDL_RenderFillRect(screen, &wall[i][0]);
        SDL_RenderFillRect(screen, &wall[i][cntwidth - 1]);
    }

    for(int i = 0; i < cntwidth; i ++){
        SDL_SetRenderDrawColor( screen, color_border[0], color_border[1], color_border[2], color_border[3]);
        SDL_RenderFillRect(screen, &wall[0][i]);
        SDL_RenderFillRect(screen, &wall[cntheight - 1][i]);
    }
}

void maze(SDL_Renderer* screen){
    endgame = {0, 0};
    vector<ii> st;

    st.push_back({1, 1});
    srand(rannum);
    int cnt = rand()% 100;

    // visited[x][y] = 1 -> road
    // visited[x][y] = 0 -> wall

    fillscreen(screen);

    while(st.size()){
        srand(cnt ++);
        ii current = st.back();
        st.pop_back();

        SDL_SetRenderDrawColor( screen, color_road[0], color_road[1], color_road[2], color_road[3]);
        SDL_RenderFillRect(screen, &wall[current.first][current.second]);
        //printf("Get SDL error %s\n%d %d\n", SDL_GetError(), current.first, current.second);
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

            SDL_SetRenderDrawColor( screen, color_road[0], color_road[1], color_road[2], color_road[3]);
            SDL_RenderFillRect(screen, &wall[x2 - dx][y2 - dy]);

            visited[x2 - dx][y2 - dy] = 1;
            st.push_back({x2, y2});
        }
    }

    if(endgame == ii(0, 0)){
        vector<ii> tmp;
        for(int i = cntheight / 2; i < cntheight - 1; i ++)
           for(int j = 1; j < cntwidth - 1; j ++){
                if(!visited[i][j]) continue;
                tmp.push_back({i, j});
           }
        int k = rand() % (tmp.size());

        SDL_SetRenderDrawColor(screen, color_des[0], color_des[1], color_des[2], color_des[3]);
        SDL_RenderFillRect(screen, &wall[tmp[k].first][tmp[k].second]);

        endgame = {tmp[k].first, tmp[k].second};
    }
}

