#ifndef CLATLNG_H
#define CLATLNG_H

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef GPS_H
#include "gps.h"
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <FL/Fl_Box.H>

using namespace std;

#define USEGPS 1

struct LatLng {
  double lat;
  double lng;
  LatLng() {
    lat = 0.0;
    lng = 0.0;
  }
  LatLng(const double latitude, const double longitude) {
    lat = latitude;
    lng = longitude;
  }
};

struct DDLatLng {
  double lat;
  double lng;
  DDLatLng() {
    lat = 0.0;
    lng = 0.0;
  }
};

class CLatLng {
 public:
  CLatLng();

  ~CLatLng() = default;
  CLatLng(const CLatLng &other) = default;
  CLatLng(CLatLng &&other) = default;
  CLatLng &operator=(const CLatLng &other) = default;
  CLatLng &operator=(CLatLng &&other) = default;

  CLatLng(const string s);
  CLatLng(const char *cstr);
  CLatLng(const LatLng);

  //  bool isgpsup();
  void setRefMark();
  UtmLatLng getNowMark();

  // Utility functions
  void updateLatLng(const string &s);
  string distance(const UtmLatLng &now, const UtmLatLng &prev);

  // void writeMark(const string &s);
  void updateClubVec(const string &s);

 private:
  UtmLatLng lastMark;

  UtmLatLng getMark(size_t avg);
  double NMEA2DecimalDegrees(const double nmea);
  DDLatLng NMEA2DecimalDegrees(const LatLng &LL);
  UtmLatLng NMEA2UTM(const LatLng &LL);
};

// extern ostream &operator<<(ostream &strm, const LatLng &ll);
// extern ostream &operator<<(ostream &strm, const DDLatLng &dll);
extern ostream &operator<<(ostream &strm, const UtmLatLng &ull);
extern GPS myGPS;

extern CLatLng cll;

#endif  // CLATLNG_H
