#ifndef CHARON_H
#define CHARON_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "magbrace.h"

class Charon {
    public:
        enum class Direction { kUp, kDown, kLeft, kRight };
        enum class RotDirection { kCCW, kCW};

        Charon(int grid_width, int grid_height)
            :   grid_width(grid_width),
                grid_height(grid_height),
                c_x(grid_width / 2),
                c_y(grid_height / 2) {

                    bodyPoints = new SDL_Point [5];
                }
        
        ~Charon(){
            //delete[] bodyPoints;
        }

        void Update();

        Direction direction = Direction::kUp;

        float speed{0.0f};
        bool alive{true};
        float distance {0.0f};

        float angle {0.0f};

        float ang_vel {2.00f};
        float degreeIncrement {0.524f};                 //30 degrees


        float vel_x {0.0f};
        float vel_y {0.0f};

        float c_x;
        float c_y;

        int vertexCount {5};

        SDL_Point * bodyPoints;

        MagBrace *magBraceR;
        

    private:
        void UpdateRotAngle();
        void UpdateBody();
        void UpdateCharonPoints();
        void UpdateMagBraces();


        int CharonVertexPoints [5][2] = {{-8,-4}, 
                                        {8, -4},
                                        {5, 4},
                                        {-5, 4}, 
                                        {-8, -4}};

        float _mass         {300.0f};                   //100kg = 220lbs - roughly weight of hero plus equipment. 
        float _cycleTime    {.016f};                    //in ms,  16 ms

        int grid_width;
        int grid_height;
};

#endif