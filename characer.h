#ifndef CHARACER_H
#define CHARACER_H
#include "common.h"

#define frame_up "img/up.png"
#define frame_left "img/left.png"
#define frame_down "img/down.png"
#define frame_right "img/right.png"

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
                    running_clip[type][i].w = rect_width;
                    running_clip[type][i].h = rect_height;
                    cnt += rect_width;
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

        int type;

    private:
        SDL_Texture* Texture_;
};

#endif // CHARACER_H
