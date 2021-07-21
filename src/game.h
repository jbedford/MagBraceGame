#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "charon.h"
#include "roid.h"
#include "roidBelt.h"
#include "point_util.cpp"

class Game {
    public:
        Game(std::size_t grid_width, std::size_t grid_height);
        void Run(Controller const &controller, Renderer &renderer,
                std::size_t target_frame_duration);
        int GetScore() const;
        int GetSize() const;
        //MagBrace *magBraceL;     
    
    private:
        Charon charon;
        //std::shared_ptr<MagBrace> magBraceR;
        MagBrace *magBraceR;     
        Roid roid;
        RoidBelt *roidBelt;
        SDL_Point survivor;   //struct to store x and y coordintates // ie Screen space

        std::random_device dev;
        std::mt19937 engine;
        std::uniform_int_distribution<int> random_w;
        std::uniform_int_distribution<int> random_h;

        int score{0};
        int survivorCount {0};
        int survivorLocations [4][2] = {{250,250}, 
                                        {640,750},
                                        {250,600},
                                        {550,400} };
        bool winGame {false};

        void PlaceSurvivor();
        void Update();
        void checkCharCollisions();
        void checkMagBraceRightCollisions();
        //void checkMagBraceLeftCollisions()
        
};

#endif