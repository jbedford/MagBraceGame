#include "roid.h"
#include <cmath>
#include <iostream>


void Roid::Update() {
    
    CheckIfMagBraceRReleased();

    if( isAnchoredRight() && magBraceR){
        //check if push or pull
        //Apply dynamics
        if(magBraceR->isActive()){
            //v' = F * delta_t / M + v     -      update force effect on Velocity
            UnitVector temp = magBraceR->calculateAnchorTrigForce();        //Calculates unit vector
            vel_x = (((temp.x*magBraceR->getMagForce()) * _cycleTime) / _mass) + vel_x;
            vel_y = (((temp.y*magBraceR->getMagForce()) * _cycleTime) / _mass) + vel_y;
        }

    }
    //p' = v*t + p   -    Update Velocity
    c_x = vel_x * _cycleTime + c_x;
    c_y = vel_y * _cycleTime + c_y;

    c_x = fmod(c_x + _screen_width, _screen_width);
    c_y = fmod(c_y + _screen_height, _screen_height);

    UpdateRoidPoints();
    
    if(isAnchoredRight() && magBraceR){
        UpdateMagBraceR();
    }

}

void Roid::UpdateRoidPoints(){
    for(int i = 0; i < _roidVertexCount; i++){
                    roidPoints[i].x = static_cast<int>(c_x) + roidVertexPoints[i][0];
                    roidPoints[i].y = static_cast<int>(c_y) + roidVertexPoints[i][1];
                    if(roidPoints[i].x < 0){roidPoints[i].x = 0;}
                    if(roidPoints[i].x > _screen_width-1){roidPoints[i].x = _screen_width-1;}
                    if(roidPoints[i].y < 0){roidPoints[i].y = 0;}
                    if(roidPoints[i].y > _screen_height-1){roidPoints[i].y = _screen_height-1;}
                }

}

//Collsion Detection - uses two methods to capture a rough roid perimeter
bool Roid::RoidCell(float x, float y) { 
    //Collision detected as a rectangle box
    if( (x > c_x+collisionBounds[0]) && (x < c_x+collisionBounds[1]) && (y < c_y+collisionBounds[2]) && (y > c_y+collisionBounds[3]) ){
        return true;
    }
    //Collision detected as a radius to centroid
    if( (pow((x-c_x), 2.0) + pow((y-c_y), 2.0)) < pow(collisionRadius,2.0) ){
        return true;
    }
    return false;
}

bool Roid::isAnchoredRight(){
    return anchoredRight;
}

bool Roid::isAnchoredLeft(){
    return anchoredLeft;
}

void Roid::setRAnchorPointOffset(Point anchorR){
    AnchorRightOffset.x = anchorR.x - c_x;
    AnchorRightOffset.y = anchorR.y - c_y;
}

void Roid::setLAnchorPointOffset(Point anchorL){
    AnchorLeftOffset.x = anchorL.x - c_x;
    AnchorLeftOffset.y = anchorL.y - c_y;
}

void Roid::UpdateMagBraceR(){
    Point anchorTemp;
    anchorTemp.x = c_x + AnchorRightOffset.x;
    anchorTemp.y = c_y + AnchorRightOffset.y;
    magBraceR->setAnchorPoint(anchorTemp);
}

void Roid::UpdateMagBraceL(){
    Point anchorTemp;
    anchorTemp.x = c_x + AnchorLeftOffset.x;
    anchorTemp.y = c_y + AnchorLeftOffset.y;
    magBraceR->setAnchorPoint(anchorTemp);
}

void Roid::CheckIfMagBraceRReleased(){
    if(magBraceR){
        if(magBraceR->getState() != MagBrace::MagBraceState::Anchored){
            magBraceR = NULL;
            anchoredRight = false;
        }
    }
}