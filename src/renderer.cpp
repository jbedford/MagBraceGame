#include "renderer.h"
#include <iostream>
#include <string>
#include <cmath>
#include <thread>
//#include <SDL_ttf.h>

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
    SDL_Rect block;
    //block.w = screen_width / grid_width;
    //block.h = screen_height / grid_height;
    

    //Clear Screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);                             //Clears Screen

    //Rendersurvior
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xC, 0x00, 0xFF);
    block.w = 10;
    block.h = 10;
    block.x = survivor.x + block.w;
    block.y = survivor.y + block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    //Render Snakes Body
    /*SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : charon.body){  //draw vector of SDL points   ... or rect object / lines objects/ roids 
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }*/
    //Use if decide pixelated charion


    //Render Charon
    //block.x = static_cast<int>(charon.head_x) * block.w;            //need to cast floats as ints
    //block.y = static_cast<int>(charon.head_y) * block.h;
    if (charon.alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    //SDL_RenderFillRect(sdl_renderer, &block);                   //update screen
    SDL_RenderDrawLines(sdl_renderer, charon.bodyPoints, charon.vertexCount);

    DrawMagBraceAimLines(charon.angle, charon.c_x, charon.c_y);


    //DRAWROIDBELT
    //std::cout << "Rendering Roids in Roid Belt" << std::endl;
    for(int i = 0; i < roidBelt.roids.size(); i++){
        //std::cout << "Drawing Roid" << std::endl;
        DrawRoid(roidBelt.roids[i]->c_x, roidBelt.roids[i]->c_y);
    }


    //Testing SDL Functions
    /*SDL_RenderDrawPoint(sdl_renderer, 54, 54);

    int count = 40;
    SDL_Point * points = new SDL_Point[count];
    for(int i=0; i<count; i++){
        points[i].x = i * 3;
        points[i].y = i * 4 + i;
    }
    SDL_SetRenderDrawColor(sdl_renderer, 0xF6, 0x2E, 0xF5, 0xFF);
    SDL_RenderDrawPoints(sdl_renderer, points, count);

    delete[] points;

    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x7E, 0xA8, 0xFF);
    SDL_RenderDrawLine(sdl_renderer, 200, 300, 400, 400);*/
    //Testing END



    //Render MagBraces
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
            SDL_Rect quickAnchor;
            quickAnchor.w = 4;
            quickAnchor.h = 6;
            quickAnchor.x = static_cast<int>(magBraceR.c_x) - 2;
            quickAnchor.w = static_cast<int>(magBraceR.c_y) - 6;
            //std::cout << "c_x: " << quickAnchor.x << "  c_y: " << quickAnchor.w << std::endl;
            //SDL_RenderFillRect(sdl_renderer, &quickAnchor);
            SDL_RenderDrawLines(sdl_renderer, magBraceR.magBraceBodyPoints, magBraceR.vertexCount);     //FIX THIS LATER

            //for(int i = 0; i < 4; i++){
            //    std::cout << "point " << i << " : " << magBraceR.magBraceBodyPoints[i].x << ":" << magBraceR.magBraceBodyPoints[i].y << " - ";
            //}
            //std::cout << std::endl; 
            SDL_RenderDrawPoint(sdl_renderer, static_cast<int>(magBraceR.c_x), static_cast<int>(magBraceR.c_y));
            
            break;

        case MagBrace::MagBraceState::Released:
            break;
    }
    
    


    //Store matrix of all gamespaceobjects, only render what is in the screen window screen width and height. move centroid to move screen. 
        //ie game space 3x screen space ie 2400w by 3000h; 
        //scolling later on
    

    //Update Screen
    SDL_RenderPresent(sdl_renderer);
}


void Renderer::DrawMagBraceAimLines(float charAngle, float charX, float charY){
    float baseAngle = -charAngle + 1.5709;
    float offset1 = 0.34f;//0.524f;                                          //Change this later according to desired vector
    float offset2 = 1.00f;
    float launchRange = 200.0f;                             //rough 120feet = 36.576 meter = 144 grid pixs
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x40, 0x00, 0xFF);
    float mR1_x = cos(baseAngle-offset1)*launchRange + charX;
    float mR1_y = -(sin(baseAngle-offset1)*launchRange) + charY;
    SDL_RenderDrawLine(sdl_renderer, static_cast<int>(charX), static_cast<int>(charY), static_cast<int>(mR1_x), static_cast<int>(mR1_y));
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

void Renderer::DrawRoid(float cx, float cy){
    //SDL_Point * roidPoints = new roidPoints[8];
    for(int i = 0; i < _roidVertexCount; i++){
                    roidPoints[i].x = static_cast<int>(cx) + roidVertexPoints[i][0]; //SDL_Points[i].x;
                    roidPoints[i].y = static_cast<int>(cy) + roidVertexPoints[i][1]; //SDL_Points[i].y;
                    if(roidPoints[i].x < 0){roidPoints[i].x = 0;}
                    if(roidPoints[i].x > screen_width-1){roidPoints[i].x = screen_width-1;}
                    if(roidPoints[i].y < 0){roidPoints[i].y = 0;}
                    if(roidPoints[i].y > screen_height-1){roidPoints[i].y = screen_height-1;}
                }
    SDL_SetRenderDrawColor(sdl_renderer, 0x99, 0x77, 0x91, 0xFF); //Purple
    SDL_RenderDrawLines(sdl_renderer, roidPoints, 8);
}



void Renderer::UpdateWindowTitle(int score, int fps) {
    std::string title{"Distance Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}

