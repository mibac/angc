#ifndef COURSE_H_
#define COURSE_H_

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include "C2UTM.hpp"

struct Vector {
    double v[2];
};

struct Polygon {
    int vertNum;
    Vector  UTM[100],rot[100],XY[100];;
};

struct Feature {
    int polyNum,featureType;
    Polygon poly[30];
};

class Hole {
  public:
    Hole();
    int featureNum;
    Feature feature[30];
    Vector startOrient[2],currentOrient[2],currentPoint;
    Vector startUnit,currentUnit;
    Vector xminmax,yminmax;
    void findMinMax();
    Vector  rotatePoint(Vector x, Vector u);
    void rotateHoleToOrientation();
};

class Course  {
  public:
    Course(int mh);
    int maxHole;
    Hole hole[19];
    void readCourse();
};

#endif
