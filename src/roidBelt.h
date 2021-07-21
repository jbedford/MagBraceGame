#ifndef _ROIDBELT_H_
#define _ROIDBELT_H_


#include <iostream>
#include "roid.h"


class RoidBelt {
    public:
        RoidBelt(int grid_width, int grid_height) : _grid_width(grid_width), _grid_height(grid_height)
        {       
            SetUpRoidBelt();
        };

        ~RoidBelt(){};

        std::vector<Roid*> roids;
        void Update();

        int getTotalRoids(){ return totalRoids; }

        bool CheckCollision(float x, float y);

        Roid* getCollidedRoid();

        Roid* magAnchorLRoid = NULL;
        Roid* magAnchorRRoid = NULL;




    private:
        void UpdateRoids();

        int totalRoids;

        void SetUpRoidBelt();               //Composes roids with starting positions and velocities


        Roid* collidedRoid = NULL;


        int _grid_width;
        int _grid_height;

};

#endif