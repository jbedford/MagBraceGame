#include "charon.h"
#include <cmath>
#include <iostream>

void Charon::Update() {
    
    UpdateRotAngle();

    UpdateBody();

    UpdateCharonPoints();

    UpdateMagBraces();

}


void Charon::UpdateRotAngle() {
    switch (direction) {
        case Direction::kLeft:
            angle = angle - ang_vel*_cycleTime;
            direction = Direction::kUp;             //idle direction, stopping turn
            break;

        case Direction::kRight:
            angle = angle + ang_vel*_cycleTime;
            direction = Direction::kUp;             //idle direction, stopping turn
            break;
    }
}

void Charon::UpdateBody(){
    if(magBraceR){
        if( magBraceR->getState() == MagBrace::MagBraceState::Anchored){
            if(magBraceR->isActive()){
                UnitVector temp = magBraceR->calculateOriginTrigForce();
                vel_x = (((temp.x*magBraceR->getMagForce()) * _cycleTime) / _mass) + vel_x;
                vel_y = (((temp.y*magBraceR->getMagForce()) * _cycleTime) / _mass) + vel_y;
            }
        }
    }


    //Translate Body
    c_x = vel_x * _cycleTime + c_x;
    c_y = vel_y * _cycleTime + c_y;

    c_x = fmod(c_x + grid_width, grid_width);
    c_y = fmod(c_y + grid_height, grid_height);

}

void Charon::UpdateCharonPoints(){
    //Rotation Matrix 
    //rotMat =    [[cos(angle), -sin(angle)], 
    //             [sin(angle), cos(angle)]];
    for(int i = 0; i < vertexCount; i++){
        bodyPoints[i].x = static_cast<int>((static_cast<float>(CharonVertexPoints[i][0]) * cos(angle)) + (static_cast<float>(CharonVertexPoints[i][1]) * -sin(angle))) + static_cast<int>(c_x);
        bodyPoints[i].y = static_cast<int>((static_cast<float>(CharonVertexPoints[i][0]) * sin(angle)) + (static_cast<float>(CharonVertexPoints[i][1]) * cos(angle))) + static_cast<int>(c_y);
        if(bodyPoints[i].x < 0){bodyPoints[i].x = 0;}
        if(bodyPoints[i].x > grid_width-1){bodyPoints[i].x = grid_width-1;}
        if(bodyPoints[i].y < 0){bodyPoints[i].y = 0;}
        if(bodyPoints[i].y > grid_height-1){bodyPoints[i].y = grid_height-1;}
    }
}

void Charon::UpdateMagBraces(){

    magBraceR->setHomedAngle(angle);
    Point tempPt;
    tempPt.x = c_x;
    tempPt.y = c_y;

    magBraceR->setOriginPoint(tempPt);
    if( magBraceR->getState() == MagBrace::MagBraceState::Homed){
        magBraceR->setCurrentPoint(tempPt);
    }
}
