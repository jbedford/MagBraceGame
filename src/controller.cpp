#include "controller.h"
#include <iostream>
#include <SDL.h>
#include <charon.h>

void Controller::ChangeDirection(Charon &charon, Charon::Direction input,
                                Charon::Direction opposite) const {
    if (charon.direction != opposite) charon.direction = input;     //remove opposite distance
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
    while (SDL_PollEvent(&e)) {                 //Occurs at any event keypress, mouse click etc
        if (e.type == SDL_QUIT) {
            running = false;
        } 
        else if (e.type == SDL_KEYDOWN) {
            
            switch (e.key.keysym.sym) {
                
                case SDLK_UP:
                    ChangeDirection(charon, Charon::Direction::kUp,
                                    Charon::Direction::kDown);                          //pass reference to charon object
                    
                    break;

                case SDLK_DOWN:
                    ChangeDirection(charon, Charon::Direction::kDown,
                                    Charon::Direction::kUp);
                    
                    break;

                case SDLK_LEFT:
                    ChangeDirection(charon, Charon::Direction::kLeft,
                                    Charon::Direction::kRight);
                    
                    break;
                case SDLK_c:
                    ChangeDirection(charon, Charon::Direction::kLeft,
                                    Charon::Direction::kRight);
                    break;

                case SDLK_RIGHT:
                    ChangeDirection(charon, Charon::Direction::kRight,
                                    Charon::Direction::kLeft);
                    
                    break; 
                case SDLK_n:
                    ChangeDirection(charon, Charon::Direction::kRight,
                                    Charon::Direction::kLeft);
                    break;

                case SDLK_i:
                    RightBraceLaunch(magbraceR, 0);
                    break;

                case SDLK_j:
                    magbraceR.activatePull();
                    break;

                case SDLK_k:
                    magbraceR.activatePush();
                    break;

                case SDLK_h:
                    RightBraceRelease(magbraceR);
                    break;
            }
            
        }

    }

}