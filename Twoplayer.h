#ifndef TWOPLAYER_H
#define TWOPLAYER_H
#include "common.h"
#include "Button.h"
#include "characer.h"
#include "Character2.h"
#include "Score.h"
#include "menu.h"

extern int score2;

class Twoplayer
{
    public:
        Twoplayer();
        virtual ~Twoplayer();

    void gameplay(SDL_Renderer* g_render, bool &round, bool &out);

    private:
};

#endif // TWOPLAYER_H
