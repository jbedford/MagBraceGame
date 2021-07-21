#include "charon.h"
#include <cmath>
#include <iostream>

void Charon::Update() {
    /*SDL_Point prev_cell{
        static_cast<int>(head_x),
        static_cast<int>(head_y)};    //Capture before updating
    UpdateMagbrace();
    SDL_Point current_cell{
        static_cast<int>(head_x),
        static_cast<int>(head_y)};    //Capture after updating
    */

    //update dynamics
    //1. MagBrace.Loaded
    //2. MagBrace.Anchored
    //3. MagBrace.Launch(direction_vector) 
    //4. MagBrace.Pull() / Push();
    //5. MagBrace.SetHomePos(SDL_Point &home)
    //6. MagBrace.AnchorPoint(SDL_point &point), or anchorRoid;
    
    UpdateRotAngle();

    UpdateBody();

    UpdateCharonPoints();

    UpdateMagBraces();
}

//Should trigger at event call, and resetting of a flag
void Charon::UpdateRotAngle() {
    switch (direction) {
        /*case Direction::kUp:
            head_y -= speed;
            break;

        case Direction::kDown:
            head_y += speed;
            break;*/

        case Direction::kLeft:
            //head_x -= speed;
            //angle -= degreeIncrement;
            angle = angle - ang_vel*_cycleTime;
            direction = Direction::kUp;
            break;

        case Direction::kRight:
            //head_x += speed;
            //angle += degreeIncrement;
            angle = angle + ang_vel*_cycleTime;
            direction = Direction::kUp;
            break;

    }

    //head_x = fmod(head_x + grid_width, grid_width);
    //head_y = fmod(head_y + grid_height, grid_height);
}

void Charon::UpdateBody(){              //START HERE 7_4 - get to compile and rot Charon in place and move

    //Rotate Body

    //rotMat =    [[cos(angle), -sin(angle)], 
    //             [sin(angle), cos(angle)]];
    /*for(int i = 0; i < 4; i++){
        bodyPoints[i].x = static_cast<int>((static_cast<float>(CharonVertexPoints[i][0]) * cos(angle)) + (static_cast<float>(CharonVertexPoints[i][1]) * -sin(angle)));
        bodyPoints[i].y = static_cast<int>((static_cast<float>(CharonVertexPoints[i][0]) * sin(angle)) + (static_cast<float>(CharonVertexPoints[i][1]) * cos(angle)));
    }*/

    if(magBraceR){
        if( magBraceR->currentState == MagBrace::MagBraceState::Anchored)
        
        if(magBraceR->isActive()){
            UnitVector temp = magBraceR->calculateOriginTrigForce();
            vel_x = (((temp.x*magBraceR->getMagForce()) * _cycleTime) / _mass) + vel_x;
            vel_y = (((temp.y*magBraceR->getMagForce()) * _cycleTime) / _mass) + vel_y;
        }
    }


    //Translate Body
    c_x = vel_x * _cycleTime + c_x;
    c_y = vel_y * _cycleTime + c_y;

    c_x = fmod(c_x + grid_width, grid_width);
    c_y = fmod(c_y + grid_height, grid_height);

    //Update distance traveled/ distance to target (game todo);
}

void Charon::UpdateCharonPoints(){
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
    //magRight->setHomedAngle(angle);
    magBraceR->setHomedAngle(angle);
    Point tempPt;
    tempPt.x = c_x;
    tempPt.y = c_y;
    //magRight->setOriginPoint(tempPt);
    //if( magRight->currentState == MagBrace::MagBraceState::Homed){
    //    magRight->setCurrentPoint(tempPt);
    //}
    magBraceR->setOriginPoint(tempPt);
    if( magBraceR->currentState == MagBrace::MagBraceState::Homed){
        magBraceR->setCurrentPoint(tempPt);
    }
}

//inefficent method to check it cell is occupied by roid.
bool Charon::CharonCell(int x, int y) {                         //START HERE 7_4 Detect collision with roids (pass roids position)... or maybe using game.object?  
    /*if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)){
        return true;
    }
    for (auto const &item : body){
        if (x == item.x && y == item.y) {
            //alive = false;
            return true;
        }
    }*/
    return false;
}

//void Charon::setRightMagBrace(MagBrace* magbrace){
//    //magRight.reset(magbrace);
//}