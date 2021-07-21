#include <iostream>
#include <controller.h>
#include <game.h>
#include <renderer.h>



int main() {
    constexpr std::size_t kFramesPerSecond(60);
    constexpr std::size_t kMsPerFrame(1000 / kFramesPerSecond);
    constexpr std::size_t kScreenWidth(800); //1280
    constexpr std::size_t kScreenHeight(1000);
    constexpr std::size_t kGridWidth(800);//320);
    constexpr std::size_t kGridHeight(1000);//160);
    
    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    Game game(kGridWidth, kGridHeight);
    game.Run(controller, renderer, kMsPerFrame);

    std::cout << "Game has been complete\n";
    std::cout << "Time: " << "\n";
    std::cout << "Distance: " << "\n";
}



