#ifndef MAGBRACE_H
#define MAGBRACE_H

#include <vector>
#include "SDL.h"
#include "point_util.cpp"

class MagBrace {
    public:
        enum class MagBraceState { Homed, Launched, Anchored, Released};
        //MagBrace();
        MagBrace() : c_x(0.0f), c_y(0.0f), 
                        currentState(MagBraceState::Homed) {
                            magBraceBodyPoints = new SDL_Point[vertexCount];
                        }
        
        ~MagBrace(){
            for(int i; i< vertexCount; i++){
                delete &magBraceBodyPoints[i];
            }
            //delete[] magBraceBodyPoints; //not a straight forward vector
        }
        /*
        MagBrace(const MagBrace &source)                // copy constructor
        {
            magBraceBodyPoints = new SDL_Point[vertexCount];
            *magBraceBodyPoints = *source.magBraceBodyPoints;
        }

        MagBrace(MagBrace &&source)                     // move constructor
        {
            magBraceBodyPoints = source.magBraceBodyPoints;
            source.magBraceBodyPoints = nullptr;
        }

        MagBrace &operator=(const MagBrace &source)     // copy assignment operator
        {
            if (this == &source){
                return *this;}
            //delete[] magBraceBodyPoints;
            magBraceBodyPoints = new SDL_Point [source.vertexCount];
            *magBraceBodyPoints = *source.magBraceBodyPoints;
            return *this;
        }

        MagBrace &operator=(MagBrace &&source)          // move assignment operator
        {
            if(this == &source){
                return *this;}
            
            //delete[] magBraceBodyPoints;

            magBraceBodyPoints = source.magBraceBodyPoints;
            source.magBraceBodyPoints = nullptr;

            return *this;
        }
        */

        /*SDL_Point getCurrentPoint();
        SDL_Point getOriginPoint();
        SDL_Point getAnchorPoint();
        SDL_Point getLaunchPoint();*/
        Point getCurrentPoint();
        Point getOriginPoint();
        Point getAnchorPoint();
        Point getLaunchPoint();

        /*void setCurrentPoint(SDL_Point point);
        void setOriginPoint(SDL_Point point);
        void seAnchorPoint(SDL_Point point);
        void setLaunchPoint(SDL_Point point);
        void setLaunchAngle(SDL_Point point);*/
        void setCurrentPoint(Point point);
        void setOriginPoint(Point point);
        void setAnchorPoint(Point point);
        void setLaunchPoint(Point point);
        void setLaunchAngle(UnitVector angle);
        void setHomedAngle(float angle);

        bool isActive();
        void setActive();
        bool isAnchored();
        void setAnchored(bool val);

        UnitVector calculateOriginTrigForce();
        UnitVector calculateAnchorTrigForce();


        void launch();
        void activatePull();
        void activatePush();
        void release();

        float getMagForce();


        //MagBraceState currentState;
        MagBraceState getState() const { return currentState;}
        void setState(MagBraceState stateN) { currentState = stateN;}


        float c_x;
        float c_y;
        float c_angle;

        int vertexCount {6};

        float calcDistance(Point p1, Point p2);

        void Update();

        SDL_Point * magBraceBodyPoints;

    private:
        float homedAngle;
        Point currentPoint;
        Point originPoint;         //float or int
        Point anchorPoint;         //float or int
        Point launchPoint;         //float or int
        
        float launchSpeed {150.0f};             //meters/second //45? 75
        float launchRange {300.0f};         //200 meters
        UnitVector launchAngle;             //unit vector
        float pullForce = 16000.0f;      //newtons
        float pushForce = 12000.0f;     //newtons        //200?
        bool pullOrPush = false;

        bool activeForce = false;
        bool anchored = false;              //consider making this public
        bool launched = false;
        bool homed = false;

        MagBraceState currentState;

        int BraceVertexPoints [6][2] = {{-5,6}, 
                                        {-3, -4},
                                        {-2, 6},
                                        {2, 6},
                                        {3, -4}, 
                                        {5, 6}};

        //void UpdateRotAngle();
        void UpdateBracePoints();

        float _cycleTime    {.016f};    //in ms,  16 ms
        int grid_width {800};             //REMOVE HARDCODE LATER
        int grid_height {1000};


};



#endif