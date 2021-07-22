#include "renderer.h"
#include <iostream>
#include <string>
#include <cmath>
#include <thread>


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
        :   screen_width(screen_width),
            screen_height(screen_height),
            grid_width(grid_width),
            grid_height(grid_height) {

    //initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize. \n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("MagBrace", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);
    
    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created. \n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    //create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if ( nullptr == sdl_renderer) {
        std::cerr << "Rnederer could not be created. \n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    roidPoints = new SDL_Point[8];
}

Renderer::~Renderer() {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Charon const charon, RoidBelt const roidBelt, MagBrace const &magBraceR, SDL_Point const &survivor) {

    //Clear Screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    //Renders Survivor
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xC, 0x00, 0xFF);
    SDL_Rect block;
    block.w = 10;
    block.h = 10;
    block.x = survivor.x + block.w;
    block.y = survivor.y + block.h;
    SDL_RenderFillRect(sdl_renderer, &block);


    //Render Charon
    if (charon.alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderDrawLines(sdl_renderer, charon.bodyPoints, charon.vertexCount);
    

    //Render Charon's Aim Lines
    DrawMagBraceAimLines(charon.angle, charon.c_x, charon.c_y);


    //Render Roids in Roid Belt
    for(int i = 0; i < roidBelt.roids.size(); i++){
        DrawRoid(roidBelt.roids[i]->c_x, roidBelt.roids[i]->c_y);
    }

    //Render MagBraces in various states
    MagBrace::MagBraceState checkState = magBraceR.getState();
    switch(checkState){
        case MagBrace::MagBraceState::Homed:
            SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
            break;
        
        case MagBrace::MagBraceState::Launched:
            SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderDrawLine(sdl_renderer, static_cast<int>(charon.c_x), static_cast<int>(charon.c_y), 
                                static_cast<int>(magBraceR.c_x), static_cast<int>(magBraceR.c_y));
            break;
        
        case MagBrace::MagBraceState::Anchored:
            SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xD7, 0x00, 0xFF);
            SDL_RenderDrawLines(sdl_renderer, magBraceR.magBraceBodyPoints, magBraceR.vertexCount);
            SDL_RenderDrawPoint(sdl_renderer, static_cast<int>(magBraceR.c_x), static_cast<int>(magBraceR.c_y));
            break;

        case MagBrace::MagBraceState::Released:
            break;
    }

    //Updates Screen
    SDL_RenderPresent(sdl_renderer);
}

//Draws 
void Renderer::DrawMagBraceAimLines(float charAngle, float charX, float charY){
    float baseAngle = -charAngle + 1.5709;
    float offset1 = 0.34f;                                              //Desired offset vector - 0.524f = 90 degrees
    float offset2 = 1.00f;
    float launchRange = 200.0f;                                         //rough 120feet = 36.576 meter = 144 grid pixs
    //This is the Primary Aim Launch Line
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x60, 0x00, 0xFF);
    float mR1_x = cos(baseAngle-offset1)*launchRange + charX;
    float mR1_y = -(sin(baseAngle-offset1)*launchRange) + charY;
    SDL_RenderDrawLine(sdl_renderer, static_cast<int>(charX), static_cast<int>(charY), static_cast<int>(mR1_x), static_cast<int>(mR1_y));
    //The remaining lines are secondary and unused.
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x40, 0x00, 0xFF);
    float mL1_x = cos(baseAngle+offset1)*launchRange + charX;
    float mL1_y = -(sin(baseAngle+offset1)*launchRange) + charY;
    SDL_RenderDrawLine(sdl_renderer, static_cast<int>(charX), static_cast<int>(charY), static_cast<int>(mL1_x), static_cast<int>(mL1_y));

    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x30, 0x10, 0xFF);
    float mR2_x = cos(baseAngle-offset2)*launchRange + charX;
    float mR2_y = -(sin(baseAngle-offset2)*launchRange) + charY;
    SDL_RenderDrawLine(sdl_renderer, static_cast<int>(charX), static_cast<int>(charY), static_cast<int>(mR2_x), static_cast<int>(mR2_y));
    float mL2_x = cos(baseAngle+offset2)*launchRange + charX;
    float mL2_y = -(sin(baseAngle+offset2)*launchRange) + charY;
    SDL_RenderDrawLine(sdl_renderer, static_cast<int>(charX), static_cast<int>(charY), static_cast<int>(mL2_x), static_cast<int>(mL2_y));


}

//Draws Standard Roid with Predefined verticies for Render draw lines function
void Renderer::DrawRoid(float cx, float cy){
    for(int i = 0; i < _roidVertexCount; i++){
                    roidPoints[i].x = static_cast<int>(cx) + roidVertexPoints[i][0];
                    roidPoints[i].y = static_cast<int>(cy) + roidVertexPoints[i][1];
                    if(roidPoints[i].x < 0){roidPoints[i].x = 0;}
                    if(roidPoints[i].x > screen_width-1){roidPoints[i].x = screen_width-1;}
                    if(roidPoints[i].y < 0){roidPoints[i].y = 0;}
                    if(roidPoints[i].y > screen_height-1){roidPoints[i].y = screen_height-1;}
                }
    SDL_SetRenderDrawColor(sdl_renderer, 0x99, 0x77, 0x91, 0xFF); //Purple
    SDL_RenderDrawLines(sdl_renderer, roidPoints, 8);
}


void Renderer::UpdateWindowTitle(int score, int fps) {
    std::string title{"Survivor Saved Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}

