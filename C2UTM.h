//
//  C2UTM.hpp
//  GLDisplayCourse
//
//  Created by Jack on 4/8/17.
//  Copyright © 2017 Jack Goldfeather. All rights reserved.
//

#ifndef C2UTM_hpp
#define C2UTM_hpp

#include <stdio.h>

#include <string>


using namespace std;
class LL2UTM
{
public:
    LL2UTM();
    void setLatLon(double lat,double lon);
    double UTMEast,UTMNorth,latitude,longitude,latitudeDegree;
    double equatorialRadius,polarRadius,flattening,inverseFlattening;
    double rm,k0,e,e1sq,n,rho,nu;
    double S,A0,B0,C0,D0,E0;
    double p,sin1,K1,K2,K3,K4,K5,A6;
    string longZone, latZone;
    void setVariables();
    string getLongZone();
    //  string getLatZone(double latitude);
    
    double getEast();
    double getNorth();
    void convert2UTM();
    void print();
};

#endif /* C2UTM_hpp */
