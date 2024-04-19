#ifndef CHARACTER2_H
#define CHARACTER2_H
#include "common.h"
#include "Twoplayer.h"

const std::string frame_img2[total] = {"img/character2/up.png", "img/character2/left.png", "img/character2/down.png", "img/character2/right.png"};

const int step_x2[] = {-1, 0, 1, 0};
const int step_y2[] = {0, -1, 0, 1};
extern SDL_Rect running_clip[total][cnt_frame];

class Character2
{
    public:
        Character2();
        ~Character2();

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

        void handinput(SDL_Event e, SDL_Renderer* screen);

        void handrun(int type);

        bool check_win(){
            return (current_x == endgame.first && current_y == endgame.second);
        };

        void check_food(){
            if(has_food[current_x][current_y].first){
                has_postion2[current_x][current_y] = 0;
                srand(time(0));
                int k = rand() % int(list_road.size() - 1);
                has_food[current_x][current_y].first = 0;
                has_food[current_x][current_y].second = -1;
                current_x = list_road[k].first;
                current_y = list_road[k].second;
                has_postion2[current_x][current_y] = 1;
            }
        }

        int type;
        int current_x, current_y;
        int dir;

    private:
        SDL_Texture* Texture_;

};

#endif // CHARACTER2_H
