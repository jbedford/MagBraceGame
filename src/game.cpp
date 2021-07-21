#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    :   charon(grid_width, grid_height),
        roid(450, 400, grid_width, grid_height, -8.0f, -3.0f, 1), //Encapsulate into a larger class of roids.  500, 250,0, -10; -38.0f , 120.0f
        //magBraceL(),
        engine(dev()),
        random_w(0, static_cast<int>(grid_width - 1)),
        random_h(0, static_cast<int>(grid_height - 1)) {

    //magBraceR.reset(new MagBrace());
    //charon.magRight = magBraceR;

    //charon.magBraceL = &magBraceL;
    magBraceR = new MagBrace();
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
        controller.HandleInput(running, charon, *magBraceR);   //magbraces maybe
        //controller.HandleInput(running, charon, *magBraceR.get());
        Update();
        renderer.Render(charon, roid, *roidBelt, *magBraceR, survivor);  //roid, magachors
        //*(magBraceR.get())

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
            std::cout << "GAME OVER! ALL SURVIVORS RESCUED! YOU WIN!" << std::endl;
            //usleep(3000000);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            return;
        }
    }
}

void Game::PlaceSurvivor() {
    int x, y;
    /*while (true) {
        x = random_w(engine);
        y = random_h(engine);
        //check that the location is not near Charon before placing Survivor.
        if (!charon.CharonCell(x,y)) { 
            survivor.x = x;
            survivor.y = y;
            return;
        }
    }*/
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
    ///////////if (!charon.alive) return;                      //ToDo Do Something more professional than this. 
    if(winGame){

    }

    charon.Update();

    roid.Update();      //should be roids update.

    roidBelt->Update();


    //magBraces.Update();
    //magBraceR->Update();
    magBraceR->Update();

    //evacShip.Update();

    int new_x = static_cast<int>(charon.c_x);
    int new_y = static_cast<int>(charon.c_y);

    // check if Charon rescued Survivor
    //if (survivor.x == new_x &&  survivor.y == new_y) {
    if (abs(survivor.x-new_x) < 25 &&  abs(survivor.y - new_y) < 25) {
        score++;
        survivorCount++;
        
        if(survivorCount >= 1){
            winGame = true;
        }
        else{
            PlaceSurvivor();
            //consider stopping velocity
        }
    }
    
    checkCharCollisions();
    checkMagBraceRightCollisions();
    //Dynamics of the game here. Mag forces and speed, NO, just the Games objects

}

void Game::checkCharCollisions(){
    for(int i = 0; i < charon.vertexCount-1; i++){
        if (roid.RoidCell(static_cast<float>(charon.bodyPoints[i].x) , static_cast<float>(charon.bodyPoints[i].y))){
            charon.alive = false;
        }
        if (roidBelt->CheckCollision(static_cast<float>(charon.bodyPoints[i].x) , static_cast<float>(charon.bodyPoints[i].y))){
            charon.alive = false;
        }
    }

}

void Game::checkMagBraceRightCollisions(){
    if(magBraceR->currentState == MagBrace::MagBraceState::Launched){
        //Check Roid Belt //multiple roids object for possible collisions with roid.
        if (roid.RoidCell(magBraceR->c_x, magBraceR->c_y)){     //Later: change to specified collision Points
            //Magbrace has collided with a roid
            roid.anchoredRight = true;
            magBraceR->setAnchored(true);
            magBraceR->currentState = MagBrace::MagBraceState::Anchored;

            if(!roid.magBraceR){  roid.magBraceR = magBraceR;   }      
            
            else{ std::cout << "Error: Issue with unassigning pointer" << std::endl;}

            roid.setRAnchorPointOffset(magBraceR->getCurrentPoint());

            //Roid.calculate offset and update anchor point on updates.
            
            //if released, set roid pointer to point to null.
            //    set roid.anchored to false.

        }
        
        if (roidBelt->CheckCollision(magBraceR->c_x, magBraceR->c_y)){     //Later: change to specified collision Points
            //Magbrace has collided with a roid
            roidBelt->getCollidedRoid()->anchoredRight = true;
            magBraceR->setAnchored(true);
            magBraceR->currentState = MagBrace::MagBraceState::Anchored;

            if(!roidBelt->getCollidedRoid()->magBraceR){  
                roidBelt->getCollidedRoid()->magBraceR = magBraceR;   //should maybe be a private functions
            }
            
            else{ std::cout << "Error: Issue with unassigning pointer" << std::endl;}

            roidBelt->getCollidedRoid()->setRAnchorPointOffset(magBraceR->getCurrentPoint());
        }
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return charon.distance; }