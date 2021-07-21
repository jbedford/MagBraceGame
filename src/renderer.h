#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "charon.h"
#include "roid.h"
#include "roidBelt.h"
#include "magbrace.h"

class Renderer {
    public:
        Renderer(const std::size_t screen_width, const std::size_t screen_height,
                 const std::size_t grid_width, const std::size_t grid_height);
        ~Renderer();

        void Render(Charon const charon, Roid const roid, RoidBelt const roidBelt, MagBrace const magBraceR, SDL_Point const &survivor);
        void UpdateWindowTitle(int score, int fps);
        void roidType1(int cx, int cy);
        void DrawMagBraceAimLines(float charAngle, float charX, float charY);
        void DrawRoid(float cx, float cy);
        void DrawBackground();
        //void threadDrawCharrismasNose();//SDL_Renderer* sdl_renderer1);
        //void DrawVictoryScreen();

    private:
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;

        const std::size_t screen_width;
        const std::size_t screen_height;
        const std::size_t grid_width;
        const std::size_t grid_height;
        SDL_Point * roidPoints;

        int bkgd_Mod = 1;
        int _roidVertexCount {8};
        int roidVertexPoints [8][2] = {{-30,-8}, 
                            {-10,-30},
                            {15,-40},
                            {40,-32},
                            {55,-10},
                            {30,20},
                            {-15,12},
                            {-30,-8} };


};

#endif