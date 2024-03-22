#ifndef CHARACER_H
#define CHARACER_H
#include "common.h"

#define frame_up36 "img/36px/up.png"
#define frame_left36 "img/36px/left.png"
#define frame_down36 "img/36px/down.png"
#define frame_right36 "img/36px/right.png"

const string frame_img[roundplay][total] = {{"img/36px/up.png", "img/36px/left.png", "img/36px/down.png", "img/36px/right.png"},
                            {"img/26px/up.png", "img/26px/left.png", "img/26px/down.png", "img/26px/right.png"},
                            {"img/16px/up.png", "img/16px/left.png", "img/16px/down.png", "img/16px/right.png"} };

class characer
{
    public:
        characer();
        ~characer();

        void init_data(){
            for(int type = 0; type < total; type ++){
                int cnt = 0;
                for(int i = 0; i < cnt_frame; i ++){
                    running_clip[round_in][type][i].x = cnt;
                    running_clip[round_in][type][i].y = 0;
                    running_clip[round_in][type][i].w = rect_width[round_in];
                    running_clip[round_in][type][i].h = rect_height[round_in];
                    cnt += rect_width[round_in];
                }
            }
        }

        SDL_Texture* Get_Texture() const {return Texture_;};

        bool LoadImage(std::string path, SDL_Renderer* screen);

        void Render(SDL_Renderer* des, const SDL_Rect* clip = nullptr);

        void Render(SDL_Renderer* screen, int x, int y, SDL_Rect* clip);

        void runAnimation(SDL_Renderer* screen, SDL_Event event);

        void handinput(SDL_Event e);

        void handrun(SDL_Renderer* screen);

        bool check_win(){
            return (current_x == endgame.first && current_y == endgame.second);
        };

        int type;
        int step_x, step_y;
        int current_x, current_y;

    private:
        SDL_Texture* Texture_;
};

#endif // CHARACER_H
