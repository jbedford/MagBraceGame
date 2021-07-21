#include "roidBelt.h"
#include <cmath>
#include <iostream>


void RoidBelt::SetUpRoidBelt(){
    //set up starting 2D array to populate
    std::cout << "Populating Roids in Roid Belt" << std::endl;
    totalRoids = 0;
    Roid* roid1 = new Roid(450, 300, _grid_width, _grid_height, -1.0f, -3.0f, 1);
    roids.push_back(roid1);
    totalRoids++;
    Roid* roid2 = new Roid(200, 200, _grid_width, _grid_height, 13.0f, 50.0f, 2);
    roids.push_back(roid2);
    totalRoids++;
    Roid* roid3 = new Roid(700, 600, _grid_width, _grid_height, 1.0f, 1.0f, 3);
    roids.push_back(roid3);
    totalRoids++;
    Roid* roid4 = new Roid(300, 750, _grid_width, _grid_height, 1.0f, -5.0f, 4);
    roids.push_back(roid4);
    totalRoids++;
    Roid* roid5 = new Roid(200, 500, _grid_width, _grid_height, 0.0f, 0.0f, 5);
    roids.push_back(roid5);
    totalRoids++;
    Roid* roid6 = new Roid(400, 400, _grid_width, _grid_height, -8.0f, -3.0f, 6);
    roids.push_back(roid6);
    totalRoids++;
    //500, 250,0, -10; -38.0f , 120.0f
}

//void AddNewRoid(roid * newRoid){}


void RoidBelt::Update()
{   
    UpdateRoids();
}

bool RoidBelt::CheckCollision(float x, float y)
{
    for(int i = 0; i<roids.size(); i++){
        if(roids[i]->RoidCell(x, y)){
            collidedRoid = roids[i];   //setting a point to point to same location in memory.
            return true;
        }
    }
    return false;
}

Roid* RoidBelt::getCollidedRoid()
{
    return collidedRoid;
}

void RoidBelt::UpdateRoids()
{
    for(int i = 0; i < roids.size(); i++){
        roids[i]->Update();
    }
}

