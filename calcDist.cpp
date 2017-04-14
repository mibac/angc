// http://adamchukpa.mcgill.ca/web_ssm/web_GPS.html
// http://adamchukpa.mcgill.ca/web_ssm/web_GPS_ex.html

#ifndef CALC_DISTANCE_H
#include "calcDist.h"
#endif

#include <cerrno>
#include <cfenv>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

const double A = 6378137.;        // semi-major axis WGS-84 specification
const double INVF = 298.2572236;  // inverse flattening WGS-84 specification
const double F = 1.0 / INVF;
const double B = A * (1 - F);
const double E2 = 2 * F - F * F;  // First Eccentricity
const double PHI = 44;            // Northfield degrees
const double H = 0;               // height above ellipsoid

const double x = pow(sinf(PHI * M_PI / 180.0), 2);
const double W = sqrt(1 - E2 * x);

const double N = A / W;
const double M = A * (1 - E2) / pow(W, 3);

const double F_LNG = (N + H) * cosf(PHI * M_PI / 180) * M_PI / 180;
const double F_LAT = (M + H) * M_PI / 180;

double convert_longitude(double lng) {
  //=-(INT(B8/100)+(B8-INT(B8/100)*100)/60)
  int a = static_cast<int>(lng / 100);
  return -(a + (lng - a * 100) / 60);
}

double convert_latitude(double lat) {
  // =INT(C8/100)+(C8-INT(C8/100)*100)/60
  int a = static_cast<int>(lat / 100);
  return a + (lat - a * 100) / 60;
}


double distance_meters(double lat1, double lng1, double lat2, double lng2, bool print) {
  lat1 = convert_latitude(lat1);
  lng1 = convert_longitude(lng1);
  lat2 = convert_latitude(lat2);
  lng2 = convert_longitude(lng2);

  double lngx2 = pow(F_LNG * (lng2 - lng1), 2);
  double latx2 = pow(F_LAT * (lat2 - lat1), 2);
  double m = sqrt(lngx2 + latx2);
  if (print) cout << m << " meters" << endl;
  return m;
}

double distance_yards(double lat1, double lng1, double lat2, double lng2,
                      bool print) {
  double d = distance_meters(lat1, lng1, lat2, lng2);
  d /= 0.9144;
  if (print) cout << d << " yards" << endl;
  return d;
}

double distance_feet(double lat1, double lng1, double lat2, double lng2,
                     bool print) {
  double d = distance_meters(lat1, lng1, lat2, lng2);
  d /= 0.3048;
  if (print) cout << d << " feet" << endl;

  return d;
}

void print_distance(double lat1, double lng1, double lat2, double lng2) {
  double m = distance_meters(lat1, lng1, lat2, lng2);
  double y = distance_yards(lat1, lng1, lat2, lng2);
  double f = distance_feet(lat1, lng1, lat2, lng2);
  cout << m << "m, " << y << "yds, " << f << "ft" << endl;
}

void print_variables() {
  cout << "A : " << A << endl;
  cout << "INVF : " << INVF << endl;
  cout << "F : " << F << endl;
  cout << "B : " << B << endl;
  cout << "E2 : " << E2 << endl;
  cout << "PHI : " << PHI << endl;
  cout << "H : " << H << endl;
  cout << "x : " << x << endl;
  cout << "W : " << W << endl;
  cout << "N : " << N << endl;
  cout << "M : " << M << endl;
  cout << "F_LNG : " << F_LNG << endl;
  cout << "F_LAT : " << F_LAT << endl;

  cout << "-----------------------" << endl;
}
