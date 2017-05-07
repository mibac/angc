#ifndef COURSE_H_
#define COURSE_H_

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include "C2UTM.h"

struct Vector {
    double v[2];
};

struct Polygon {
    int vertNum;
    Vector  UTM[100],rot[100],XY[100];
};

struct Feature {
    int polyNum,featureType;
    Polygon poly[30];
};

struct greenData {
    Vector currentP,Pin,Front,Back,Center;
    Vector PinRot,FrontRot,BackRot;
    double pinYardage,frontYardage,backYardage;
    Feature *green;
};

class Hole {
  public:
    Hole();
    int featureNum,viewType;
    Feature feature[30];
    Vector startOrient[2],currentOrient[2],currentPoint,rotCurrentPoint;
    Vector startUnit,currentUnit,currentGreenUnit;
    Vector markPoint;
    bool showMarkPoint,zoomPointSelected;
    Vector xminmax,yminmax,xgreenminmax,ygreenminmax;
    double walk,scale,xtran,ytran,greenscale,greenxtran,greenytran;
    double zoomScale;
    void findMinMax();
    void findGreenMinMax();
    Vector  rotatePoint(Vector x, Vector u);
    Vector  unrotatePoint(Vector x, Vector u);
    void rotateHoleToOrientation();
    void rotateToGreenOrientation() ;
    void setCurrentPoint(double east,double north);
    void computeYardageToHole();
    void computeYardageFromTee();
    int yardageToHole,yardageFromTee;
    double yardDistance(Vector p1,Vector p2); 
    void findGreenYardage();
    greenData gd;
    string currentYardageToHoleStr;
    string currentYardageFromTeeStr;
    Vector pathPoint[1000];
    int pathPointNum,currentPathIndex;
};

class Course  {
  public:
    Course(int mh);
    int maxHole;
    Hole hole[19];
    void readCourse();
};
#endif
