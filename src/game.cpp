#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    :   charon(grid_width, grid_height),
        engine(dev()),
        random_w(0, static_cast<int>(grid_width - 1)),
        random_h(0, static_cast<int>(grid_height - 1)) {


    magBraceR = new MagBrace(grid_width, grid_height);
    charon.magBraceR = magBraceR;

    roidBelt = new RoidBelt(grid_width, grid_height);

    PlaceSurvivor();
}

void Game::Run(Controller const &controller, Renderer &renderer,
                std::size_t target_frame_duration) {

    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true; 

    while(running)  {
        frame_start = SDL_GetTicks();

        //Input, update, Render - The main game loop.
        controller.HandleInput(running, charon, *magBraceR);
        Update();
        renderer.Render(charon, *roidBelt, *magBraceR, survivor);

        frame_end = SDL_GetTicks();

        //Keeps track of how long each lop through the input/update/render cycle takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        //After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0; 
            title_timestamp = frame_end;
        }

        //If the time for this frame is too small (i.e. frame_duration is 
        //smaller than the target ms_per_frame), delay the loop to 
        //achieve the correct frame rate.
        if(frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }

        if(winGame){
            std::cout << std::endl;
            std::cout << "GAME OVER!" << std::endl;
            std::cout << "ALL SURVIVORS RESCUED!" << std::endl;
            if (charon.alive){
                std::cout << "CHARON SURVIVED! YOU WIN!" << std::endl;
            }
            else{
                std::cout << "BUT UNFORTUNATLY CHARON (PLAYER) DIED! YOU LOSE!" << std::endl << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));  //Consider making this a simple thread.
            return;
        }
    }
}

void Game::PlaceSurvivor() {
    int x, y;
    if(survivorCount < 4){
        std::cout << "Survivor Count: " << survivorCount << std::endl;
        x = survivorLocations[survivorCount][0];
        y = survivorLocations[survivorCount][1];
        survivor.x = x;
        survivor.y = y;
    }
    return;
}

void Game::Update() {

    charon.Update();

    roidBelt->Update();

    magBraceR->Update();

    int new_x = static_cast<int>(charon.c_x);
    int new_y = static_cast<int>(charon.c_y);

    // check if Charon rescued current Survivor
    if (abs((survivor.x+5)-new_x) < 25 &&  abs((survivor.y+5) - new_y) < 25) {
        score++;
        survivorCount++;
        
        if(survivorCount >= 4){
            winGame = true;
        }
        else{
            PlaceSurvivor();
        }
    }
    
    //Check Collisions with Roids
    checkCharCollisions();
    checkMagBraceRightCollisions();

}

void Game::checkCharCollisions(){
    for(int i = 0; i < charon.vertexCount-1; i++){
        if (roidBelt->CheckCollision(static_cast<float>(charon.bodyPoints[i].x) , static_cast<float>(charon.bodyPoints[i].y))){
            charon.alive = false;
        }
    }

}

void Game::checkMagBraceRightCollisions(){
    if(magBraceR->getState() == MagBrace::MagBraceState::Launched){
        
        if (roidBelt->CheckCollision(magBraceR->c_x, magBraceR->c_y)){     
            //Magbrace has collided with a roid
            roidBelt->getCollidedRoid()->anchoredRight = true;
            magBraceR->setAnchored(true);
            magBraceR->setState(MagBrace::MagBraceState::Anchored);

            if(!roidBelt->getCollidedRoid()->magBraceR){  
                roidBelt->getCollidedRoid()->magBraceR = magBraceR;   //Passes the Collided Roid a pointer to MagBrace 
            }
            
            else{ std::cout << "Error: Issue with unassigning pointer" << std::endl;}

            roidBelt->getCollidedRoid()->setRAnchorPointOffset(magBraceR->getCurrentPoint());
        }
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return charon.distance; }