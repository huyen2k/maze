#ifndef ONEPLAYER_H
#define ONEPLAYER_H
#include "common.h"
#include "characer.h"
#include "Button.h"
#include "menu.h"
#include "Score.h"

class Oneplayer
{
    public:
        Oneplayer();
        virtual ~Oneplayer();

        void gameplay(SDL_Renderer* g_render, bool &round, bool &out);

    private:
};

#endif // ONEPLAYER_H
