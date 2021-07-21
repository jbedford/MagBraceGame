#ifndef _ROIDBELT_H_
#define _ROIDBELT_H_


#include <iostream>
#include "roid.h"


class RoidBelt {
    public:
        RoidBelt(int grid_width, int grid_height) : _grid_width(grid_width), _grid_height(grid_height)
            {
                
                SetUpRoidBelt();
                //for(int i = 0; i < totalRoids; i++){};
                //roid* roid1 = new roid(int initX, int initY, float vector, float velocity, int type, int id);
                //roids.push_back(roid1);


        };
        ~RoidBelt(){};

        std::vector<Roid*> roids;
        void Update();

        int getTotalRoids(){ return totalRoids; }

        bool CheckCollision(float x, float y);

        Roid* getCollidedRoid();

        //std::vector<Point> getRoidPoses();

        Roid* magAnchorLRoid = NULL;
        Roid* magAnchorRRoid = NULL;




    private:
        void UpdateRoids();

        int totalRoids = 8;

        void SetUpRoidBelt();            //compose a bunch of roids with starting pos and velocities
        //void addNewRoid(roid *newRoid);
        //void removeRoid(roid *roidId);

        Roid* collidedRoid = NULL;

        //std::vector<roid*> roids;

        //std::vector<float> startingpoints and velocities, use a regular file to import this.);

        int _grid_width;
        int _grid_height;

};

#endif