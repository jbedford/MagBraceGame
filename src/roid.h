#ifndef ROID_H
#define ROID_H

#include <vector>
#include "SDL.h"
#include "magbrace.h"

class Roid {
    public:
        Roid(int init_x, int init_y, int screen_width, int screen_height, float iVel_x, float iVel_y, int id)
            :   _init_x(init_x), _init_y(init_y),
                _screen_width(screen_width), _screen_height(screen_height),
                c_x(init_x), c_y(init_y),
                vel_x(iVel_x), vel_y(iVel_y), 
                roidID(id){

                roidPoints = new SDL_Point [8];

                for(int i = 0; i < _roidVertexCount; i++){
                    roidPoints[i].x = init_x + roidVertexPoints[i][0];
                    roidPoints[i].y = init_y + roidVertexPoints[i][1]; 
                }

            }
        ~Roid(){
            for(int i; i< 8; i++){
                delete &roidPoints[i];
            }
            //delete roidPoints;
        }
        
        void Update();

        bool RoidCell(float x, float y);//IsCollision           remembering anchor location.
        int GetRoidID() { return roidID; }

        bool isAnchoredRight();  //maybe public
        bool isAnchoredLeft();

        void setRAnchorPointOffset(Point anchorR);
        void setLAnchorPointOffset(Point anchorL);
        
        bool anchoredRight  {false};
        bool anchoredLeft   {false};
        bool alive{true};


        //float force_x;

        //float theta{-0.5f};
        float vel_x {150.0f};             //in m/s
        float vel_y {-15.0f};             //in m/s

        float c_x {0.0f};
        float c_y {0.0f};

        int vertexCount {8};
        //std::vector<SDL_Point> roidPointsBody;
        SDL_Point * roidPoints;         //Make a Smart pointer 

        MagBrace *magBraceR = NULL;
        MagBrace *magBraceL = NULL;

    private:
        //void UpdateAnchorPos();
        //void UpdateDynamics();
        void UpdateRoidPoints();
        void UpdateMagBraceR();
        void UpdateMagBraceL();
        void CheckIfMagBraceRReleased();

        int roidID; 

        float _mass         {1800.0f}; //2 tons = 1800 kgs  1200
        float _cycleTime    {.016f};    //in ms,  16 ms

        Point AnchorRightOffset;
        Point AnchorLeftOffset;

        int _init_x;
        int _init_y;
        int _screen_width;              //what is a point in meters
        int _screen_height;             //let's say 1/4 meters.
        int _roidVertexCount {8};
        int roidVertexPoints [8][2] = {{-30,-8}, 
                            {-10,-30},
                            {15,-40},
                            {40,-32},
                            {55,-10},
                            {30,20},
                            {-15,12},
                            {-30,-8} };
        
        float collisionBounds [4] = { -30.0f, 45.0f, 20.0f, -40.0f};         //{left, right, Ceiling, floor}  
        float collisionRadius = 30.0f;                             //radius of collision;


};

#endif