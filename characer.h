#ifndef CHARACER_H
#define CHARACER_H
#include "common.h"

#define frame_up36 "img/36px/up.png"
#define frame_left36 "img/36px/left.png"
#define frame_down36 "img/36px/down.png"
#define frame_right36 "img/36px/right.png"

const std::string frame_img[total] = {"img/16px/up.png", "img/16px/left.png", "img/16px/down.png", "img/16px/right.png"};

const int step_x[] = {-1, 0, 1, 0};
const int step_y[] = {0, -1, 0, 1};
extern SDL_Rect running_clip[total][cnt_frame];

class characer
{
    public:
        characer();
        ~characer();

        void init_data(){
            for(int type = 0; type < total; type ++){
                int cnt = 0;
                for(int i = 0; i < cnt_frame; i ++){
                    running_clip[type][i].x = cnt;
                    running_clip[type][i].y = 0;
                    running_clip[type][i].w = 16;
                    running_clip[type][i].h = 16;
                    cnt += 16;
                }
            }
        }

        SDL_Texture* Get_Texture() const {return Texture_;};

        bool LoadImage(std::string path, SDL_Renderer* screen);

        void Render(SDL_Renderer* screen, int x, int y, SDL_Rect* clip);

        void runAnimation(SDL_Renderer* screen, SDL_Event event);

        void handinput(SDL_Event e);

        void handrun(int type);

        bool check_win(){
            return (current_x == endgame.first && current_y == endgame.second);
        };

        void check_food(){
            if(has_food[current_x][current_y].first){
                srand(time(0));
                int k = rand() % int(list_road.size() - 1);
                has_food[current_x][current_y].first = 0;
                has_food[current_x][current_y].second = -1;
                current_x = list_road[k].first;
                current_y = list_road[k].second;
            }
        }

        int type;
        int current_x, current_y;
        int dir;

    private:
        SDL_Texture* Texture_;
};

#endif // CHARACER_H
