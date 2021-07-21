#ifndef POINT_UTIL_CPP_
#define POINT_UTIL_CPP_

//#include <cmath>

class Point{            //consider adding template to subtract one point from another
    public: double x, y;
};

class UnitVector{
    public: double x, y;
};

//float calcDistance(Point p1, Point p2){
//    return sqrt(pow((p1.x-p2.x),2.0) + pow((p1.y-p2.y), 2.0));
//}

#endif