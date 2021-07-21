#ifndef CHARON_H
#define CHARON_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "magbrace.h"

class Charon {
    public:
        enum class Direction { kUp, kDown, kLeft, kRight };         //START HERE 7_4 add rotation system, correct controller, add lines to show launching and return
        enum class RotDirection { kCCW, kCW};

        Charon(int grid_width, int grid_height)
            :   grid_width(grid_width),
                grid_height(grid_height),
                c_x(grid_width / 2),
                c_y(grid_height / 2) {

                    bodyPoints = new SDL_Point [5];
                }
        
        ~Charon(){
            //delete bodyPoints;
        }

        void Update();

        //void shootRightMagBrace(angle);
        //void shootLeftMagBrace(angle);


        bool CharonCell(int x, int y);

        Direction direction = Direction::kUp;                       //START HERE 7_4 corre

        //void setLeftMagBrace(std::shared_ptr<Magbrace()> magbrace);
        //void setRightMagBrace(MagBrace* magbrace);


        //void setCharLeftMagActive();                                //START HERE add functionality
        //void setCharRightMagActive();

        //void setCharLeftMagVector(float x, float y, float mag);
        //void setCharRightMagVector(float x, float y, float mag);


        float speed{0.0f}; //0.1f
        bool alive{true};
        float distance {0.0f};

        float angle {0.0f};

        float ang_vel {2.00f};      //1.0f
        //float ang_vel {0.5f};
        //std::vector<float> angleDir = {0, 30, 60, 90, 120};
        float degreeIncrement {0.524f};                         //30 degrees


        float vel_x {0.0f};
        float vel_y {0.0f};

        float c_x;
        float c_y;

        int vertexCount {5};

        //std::vector<SDL_Point> bodyPoints;
        SDL_Point * bodyPoints;

        //std::shared_ptr<MagBrace> magRight;
        MagBrace *magBraceR;
        MagBrace *magBraceL;

    private:
        void UpdateRotAngle();
        void UpdateBody(); //SDL_Point &current_call, SDL_Point &prev_cell);
        void UpdateCharonPoints();
        void UpdateMagBraces();


        int CharonVertexPoints [5][2] = {{-8,-4}, 
                                        {8, -4},
                                        {5, 4},
                                        {-5, 4}, 
                                        {-8, -4}};

        float _mass {300.0f}; //{100.0f};           //220lbs - roughly weight of hero plus equipment. 
        float _cycleTime    {.016f};    //in ms,  16 ms

        int grid_width;
        int grid_height;
};

#endif