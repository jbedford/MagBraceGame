#include "controller.h"
#include <iostream>
#include <SDL.h>
#include <charon.h>

void Controller::ChangeDirection(Charon &charon, Charon::Direction input) const {
    charon.direction = input;
    return;
}



void Controller::RightBraceLaunch(MagBrace &magbrace, int dir) const{
    magbrace.launch();
    return;
}

void Controller::RightBraceRelease(MagBrace &magbrace) const{
    magbrace.release();
    return;
}

void Controller::HandleInput(bool &running, Charon &charon, MagBrace &magbraceR) const{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } 
        else if (e.type == SDL_KEYDOWN) {
            
            switch (e.key.keysym.sym) {
                
                case SDLK_UP:
                    ChangeDirection(charon, Charon::Direction::kUp);
                    break;

                case SDLK_LEFT:
                    ChangeDirection(charon, Charon::Direction::kLeft);
                    
                    break;
                case SDLK_c:
                    ChangeDirection(charon, Charon::Direction::kLeft);
                    break;

                case SDLK_RIGHT:
                    ChangeDirection(charon, Charon::Direction::kRight);
                    
                    break; 
                case SDLK_n:
                    ChangeDirection(charon, Charon::Direction::kRight);
                    break;

                case SDLK_w://i:
                    RightBraceLaunch(magbraceR, 0);
                    break;

                case SDLK_s://j:
                    magbraceR.activatePull();
                    break;

                case SDLK_d://SDLK_k:
                    magbraceR.activatePush();
                    break;

                case SDLK_SPACE://h:
                    RightBraceRelease(magbraceR);
                    break;
                case SDLK_a://h:
                    RightBraceRelease(magbraceR);
                    break;
            }
            
        }

    }

}