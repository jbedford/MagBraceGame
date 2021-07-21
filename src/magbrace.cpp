#include "magbrace.h"
#include <cmath>
#include <iostream>

//MagBrace::MagBrace() : c_x(0.0f), c_y(0.0f), 
//                        currentState(MagBraceState::Homed) {}

//copy constructor
//MagBrace::MagBrace(const MagBrace &){}

//copy assignment operator
//MagBrace &operator=(const MagBrace &){}

/*SDL_Point MagBrace::getCurrentPoint()   { return currentPoint; }
SDL_Point MagBrace::getOriginPoint()    { return originPoint; }
SDL_Point MagBrace::getAnchorPoint()    { return anchorPoint; }
SDL_Point MagBrace::getLaunchPoint()    { return launchPoint; }*/
Point MagBrace::getCurrentPoint()   { return currentPoint; }
Point MagBrace::getOriginPoint()    { return originPoint; }
Point MagBrace::getAnchorPoint()    { return anchorPoint; }
Point MagBrace::getLaunchPoint()    { return launchPoint; }

void MagBrace::setCurrentPoint(Point point)     { 
    currentPoint = point; 
    c_x = point.x;
    c_y = point.y;}
void MagBrace::setOriginPoint(Point point)      { originPoint = point; }
void MagBrace::setAnchorPoint(Point point)       { anchorPoint = point; }
void MagBrace::setLaunchPoint(Point point)      { launchPoint = point; }
void MagBrace::setLaunchAngle(UnitVector nAngle) { launchAngle = nAngle; }
void MagBrace::setHomedAngle(float nAngle)       { homedAngle = nAngle; }

bool MagBrace::isActive()           { return activeForce; }

void MagBrace::setActive(){
    if(currentState == MagBraceState::Anchored){
        activeForce = true;
    }
}


bool MagBrace::isAnchored()         { return anchored; }

void MagBrace::setAnchored(bool val){ anchored = val; }

void MagBrace::launch(){                                //varies base on Controller input high mid or low
    if(currentState == MagBraceState::Homed){
        std::cout << "MagBrace Right is Launching\n" << std::endl;
        currentPoint = originPoint;             //remove later
        launchPoint = currentPoint;
        
        float offset1 = 0.34f;
        float offset2 = 1.00f;

        //angle is either set before hand by the charon class (with each update) or calculated on spot by magbrace class
        //launchAngle.x = angle;      //30 degree offset from char angle
        launchAngle.x = cos((-homedAngle + 1.5709)-offset1);
        launchAngle.y = -sin((-homedAngle + 1.5709)-offset1);

        c_angle = (-homedAngle + 1.5709)-offset1;           //setting generic angle

        launched = true;
        currentState = MagBraceState::Launched;
    }
}

void MagBrace::activatePull(){
    if(currentState == MagBraceState::Anchored){
        activeForce = true;
        pullOrPush = false;
    }
}

void MagBrace::activatePush(){
    if(currentState == MagBraceState::Anchored){
        activeForce = true;
        pullOrPush = true;
    }
}

void MagBrace::release(){
    if(currentState == MagBraceState::Anchored  || currentState == MagBraceState::Launched){

        //currentState = MagBraceState::Released;           //ADD Functionaility LATER
        anchored = false;
        activeForce = false;
        currentState = MagBraceState::Homed;
    }
}

float MagBrace::getMagForce(){
    if(pullOrPush){ return pushForce*-1.0;}
    else{ return pullForce;}
}


void MagBrace::Update()
{
    switch(currentState){
        case MagBraceState::Homed:
            //update with character, ensure anchored = false, activeForce = false
            activeForce = false;
            break;

        case MagBraceState::Launched:
            //update pos via speed and direction
            currentPoint.x = launchAngle.x * launchSpeed * _cycleTime + currentPoint.x;
            currentPoint.y = launchAngle.y * launchSpeed * _cycleTime + currentPoint.y;
            c_x = currentPoint.x;
            c_y = currentPoint.y;
            //std::cout << "c_x: " << int(c_x) << "c_y: " << int(c_y) << std::endl;

            if(calcDistance(launchPoint, currentPoint) > launchRange){
                currentState = MagBraceState::Homed;
            }
            break;

        case MagBraceState::Anchored:
            //update/check anchor point 
            setCurrentPoint(anchorPoint);
            //calc Distance from origin

            if(activeForce){
                activeForce = false;        //deactivate force unless holding button.
            }
            break;

        case MagBraceState::Released:
            //count to retract back to homed pos on magbrace hold
            //time based on distance fromlast anchor point.
            //after time is out, set State to homed so current pos updated by char   
            //homed = true;
            //returnSpeed is quicker
            break; 
    }

    //also update angle and pos...
    UpdateBracePoints();
}

void MagBrace::UpdateBracePoints(){
    //Print angle to make sure updating
    //std::cout << "Brace Angle: " << c_angle << std::endl;
    for(int i = 0; i < vertexCount; i++){
        magBraceBodyPoints[i].x = static_cast<int>((static_cast<float>(BraceVertexPoints[i][0]) * cos(c_angle)) + (static_cast<float>(BraceVertexPoints[i][1]) * -sin(c_angle))) + static_cast<int>(c_x);
        magBraceBodyPoints[i].y = static_cast<int>((static_cast<float>(BraceVertexPoints[i][0]) * sin(c_angle)) + (static_cast<float>(BraceVertexPoints[i][1]) * cos(c_angle))) + static_cast<int>(c_y);
        /*if(magBraceBodyPoints[i].x < 0){magBraceBodyPoints[i].x = 0;}
        if(magBraceBodyPoints[i].x > grid_width-1){magBraceBodyPoints[i].x = grid_width-1;}
        if(magBraceBodyPoints[i].y < 0){magBraceBodyPoints[i].y = 0;}
        if(magBraceBodyPoints[i].y > grid_height-1){magBraceBodyPoints[i].y = grid_height-1;}*/
    }
    /*for(int i = 0; i < 4; i++){
                std::cout << "point " << i << " : " << magBraceBodyPoints[i].x << ":" << magBraceBodyPoints[i].y << " - ";
            }
            std::cout << std::endl; */
}

UnitVector MagBrace::calculateOriginTrigForce(){
    UnitVector result;
    //Calculate unit vecotr base on OriginPoint to anchorPoint and pullForce
    float hype = calcDistance(anchorPoint, originPoint);

    result.x = (anchorPoint.x - originPoint.x)/hype;
    result.y = (anchorPoint.y - originPoint.y)/hype;
    return result;
}

UnitVector MagBrace::calculateAnchorTrigForce(){
    UnitVector result;
    //Calculate unit vector based on anchorPoint to originPoint and pullForce
    float hype = calcDistance(anchorPoint, originPoint);

    result.x = (originPoint.x - anchorPoint.x)/hype;
    result.y = (originPoint.y - anchorPoint.y)/hype;
    return result;
}

float MagBrace::calcDistance(Point p1, Point p2){
    return sqrt(pow((p1.x-p2.x),2.0) + pow((p1.y-p2.y), 2.0));
}