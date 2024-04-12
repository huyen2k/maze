#ifndef MENU_H
#define MENU_H
#include "common.h"
#define start_img "img/menu.png"
#define gameover_img "img/gameover.png"
#define gamewin_img "img/gamewin.png"

class menu
{
    public:
        menu(std::string path_){
            Tex = NULL;
            path = path_;
            I_w = I_h = 0;
        };
        ~menu();

    bool LoadImage(SDL_Renderer* screen);

    void render(SDL_Renderer* screen, int x, int y);

    std::string path;

    private:
        SDL_Texture* Tex;
        int I_w, I_h;
};

bool update_start(SDL_Renderer* screen);
bool update_gameover(SDL_Renderer* screen);

#endif // MENU_H
