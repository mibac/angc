//
//  C2UTM.cpp
//  GLDisplayCourse
//
//  Created by Jack on 4/8/17.
//  Copyright © 2017 Jack Goldfeather. All rights reserved.
//

#include "C2UTM.h"

#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

// clang-format OFF
LL2UTM::LL2UTM()
{
    equatorialRadius = 6378137.0;
    polarRadius = 6356752.314;
    flattening = 0.00335281066474748;// (equatorialRadius-polarRadius)/equatorialRadius;
    inverseFlattening = 298.257223563;// 1/flattening;
    rm = pow(equatorialRadius * polarRadius, 1 / 2.0);
    k0 = 0.9996;
    e = sqrt(1 - pow(polarRadius / equatorialRadius, 2));
    e1sq = e * e / (1 - e * e);
    n = (equatorialRadius - polarRadius)/(equatorialRadius + polarRadius);
    rho = 6368573.744;
    nu = 6389236.914;
    S = 5103266.421;
    A0 = 6367449.146;
    B0 = 16038.42955;
    C0 = 16.83261333;
    D0 = 0.021984404;
    E0 = 0.000312705;
    p = -0.483084;
    sin1 = 4.84814E-06;
    // Coefficients for UTM Coordinates
    K1 = 5101225.115;
    K2 = 3750.291596;
    K3 = 1.397608151;
    K4 = 214839.3105;
    K5 = -2.995382942;
    A6 = -1.00541E-07;
}

void LL2UTM::setLatLon(double lat, double lon)
{
    latitudeDegree = lat;
    longitude = lon;

}

void LL2UTM::setVariables()
{
    latitude = latitudeDegree*M_PI/180.0;
    rho = equatorialRadius*(1-e*e)/pow(1-pow(e*sin(latitude),2),3/2.0);
    nu = equatorialRadius/pow(1-pow(e*sin(latitude),2),(1/2.0));

    double var1;
    if (longitude < 0.0)
    {
        var1 = ((int) ((180 + longitude) / 6.0)) + 1;
    }
    else
    {
        var1 = ((int) (longitude / 6)) + 31;
    }
    double var2 = (6 * var1) - 183;
    double var3 = longitude - var2;
    p = var3 * 3600 / 10000;

    S = A0*latitude-B0*sin(2*latitude)+C0*sin(4*latitude)-D0*sin(6*latitude)+E0*sin(8*latitude);

    K1 = S * k0;
    K2 = nu * sin(latitude) * cos(latitude) * pow(sin1, 2) * k0 * (100000000) / 2;
    K3 = ((pow(sin1,4)*nu*sin(latitude)*pow(cos(latitude),3))/24)*(5-pow(tan(latitude),2)+9*e1sq*pow(cos(latitude),2)+4*pow(e1sq,2)*pow(cos(latitude),4))*k0*(10000000000000000L);

    // JE to prevent bad initialization of CLatLng if here is no valid GPS reading
    if ((latitude == 0) || (longitude == 0)) {
        K4 = 0;
        K5 = 0;
    } else {
        K4 = nu * cos(latitude) * sin1 * k0 * 10000;
        K5 = pow(sin1*cos(latitude),3)*(nu/6)*(1-pow(tan(latitude),2)+e1sq*pow(cos(latitude),2))*k0*1000000000000L;
    }
    // end JE

   A6 = (pow(p*sin1,6)*nu*sin(latitude)*pow(cos(latitude),5)/720)*(61-58*pow(tan(latitude),2)+pow(tan(latitude),4)+270*e1sq*pow(cos(latitude),2)-330*e1sq*pow(sin(latitude),2))*k0*(1E+24);

}

string LL2UTM::getLongZone() {
    double longZone = 0;
    if (longitude < 0.0)
    {
        longZone = ((180.0 + longitude) / 6) + 1;
    }
    else
    {
        longZone = (longitude / 6) + 31;
    }
    string val = to_string((int) longZone);

    if (val.length() == 1)
    {
        val = "0" + val;
    }
    return val;
}

double LL2UTM::getEast() {
    if ((latitude == 0) || (longitude == 0))
        return 0;
    else
        return 500000 + (K4 * p + K5 * pow(p, 3));
}

double LL2UTM::getNorth() {
    double nn = K1 + K2 * p * p + K3 * pow(p, 4);
    if (latitude < 0.0)
    {
        nn = 10000000 + nn;
    }
    return nn;

}

void LL2UTM::convert2UTM() {
    setVariables();
    longZone = getLongZone();
    UTMEast = getEast();
    UTMNorth = getNorth();

}

void LL2UTM::print() {
    cout << setprecision(10) << latitudeDegree << " " << longitude << endl;
    cout << setprecision(10) << UTMEast << " " << UTMNorth << endl;
}
// clang-format ON
