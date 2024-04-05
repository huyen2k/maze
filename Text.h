#ifndef TEXT_H
#define TEXT_H
#include "common.h"

class Text{
    public:
        Text(std::string textureText_, const int color[], int sz_){
            textureText = textureText_;
            textColor = {color[0], color[1], color[2], color[3]};
            Tex = nullptr;
            sz = sz_;
        };
        ~Text();

        int getWidth(){return T_width;};
        int getHeight(){return T_height;};

        bool loadFromRenderedText();

        //bool loadmedia();

        void render( int x, int y, SDL_Rect* clip = NULL);

    private:
        std::string textureText;
        SDL_Color textColor;
        SDL_Texture* Tex;
        int T_width;
        int T_height;
        int sz;
};

#endif // TEXT_H
