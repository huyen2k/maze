#include "ghost.h"
#include "common.h"

SDL_Rect ghost_frame[3];

ghost::ghost(){

}

ghost::~ghost(){
    SDL_DestroyTexture(tex);
}

bool ghost::LoadImage(std::string path, SDL_Renderer* screen){
    SDL_Texture* new_texture = nullptr;

    SDL_Surface* load_surface = IMG_Load(path.c_str());

    if(load_surface != nullptr){
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        SDL_FreeSurface(load_surface);
    }
    tex = new_texture;
    return tex != nullptr;
}

void ghost::Render(SDL_Renderer* screen, int x, int y, SDL_Rect* clip){
    SDL_Rect renderQuad = wall[x][y];
    //printf("%d %d\n", x, y);
    //Render to screen

    SDL_RenderCopy(screen, tex, clip, &renderQuad);
//    printf("check render %s\n", screen);
}

ii ghost::find_path(int main_x, int main_y){
    int tx[] = {-1, 0, 1, 0};
    int ty[] = {0, 1, 0, -1};
    vector<vector<int> > vis(cntheight, vector<int> (cntwidth, 0));
    vector<vector<ii> > trace(cntheight, vector<ii> (cntwidth, ii(0, 0)));
    queue<ii> q;

    q.push({current_x, current_y});

    vis[current_x][current_y] = 1;
    while(q.size()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for(int i = 0; i < 4; i ++){
            int new_x = x + tx[i];
            int new_y = y + ty[i];

            if(new_x < 0 || new_x >= cntheight || new_y < 0 || new_y > cntwidth) continue;
            if(!visited[new_x][new_y]) continue;
            if(vis[new_x][new_y]) continue;

            trace[new_x][new_y] = ii(x, y);
            vis[new_x][new_y] = 1;

            q.push({new_x, new_y});
        }
    }
    vector<ii> ans;
    ii tmp = ii(main_x, main_y);
    do{
        ans.push_back(tmp);
        tmp = trace[tmp.first][tmp.second];
    }while(tmp != ii(current_x, current_y));
    vis.clear();
    trace.clear();

    reverse(ans.begin(), ans.end());

//    for(ii x: ans)
//        cout << x.first << " " << x.second << '\n';

    return ans[1];
}

void ghost::run(SDL_Renderer* screen, int main_x, int main_y){
    static int frame = 0;
    static int count_speed = 0;

    static ii new_pos = find_path(main_x, main_y);

    if(current_x == main_x && current_y == main_y) return;
    //printf("%d %d\n", main_x, main_y);
//    printf("%d %d\n", cnt, count_speed);

    SDL_Rect *currentclip = &ghost_frame[frame / 3];
    Render(screen, new_pos.first, new_pos.second, currentclip);
    current_x = new_pos.first;
    current_y = new_pos.second;
    //printf("%d %d\n", current_x, current_y);
    ++frame;
    ++count_speed;

    if(count_speed == 20){
        count_speed = 0;
        new_pos = find_path(main_x, main_y);
    }

    //Cycle animation
    if(frame / 2 >= speed){
        frame = 0;
    }
}
