#ifndef CLATLNG_H
#define CLATLNG_H

#ifndef GPS_H
#include "gps.h"
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <FL/Fl_Box.H>

using namespace std;

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

struct UtmLatLng {
  double lat;
  double lng;
  UtmLatLng() {
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
  string distanceFromLastMark();

  // void writeMark(const string &s);
  void writeClub(const string &s);
  void writeAll();

  // Variables
  vector<string> vGGA;  // the complete round of nmea GPGGA sentences
  // vector<LatLng> vLL;
  // vector<DDLatLng> vDD;
  vector<UtmLatLng> vUTM;

 private:
  int currentHole;
  UtmLatLng lastMark;

  UtmLatLng getMark(size_t avg);
  double NMEA2DecimalDegrees(const double nmea);
  DDLatLng NMEA2DecimalDegrees(const LatLng &LL);
  UtmLatLng NMEA2UTM(const LatLng &LL);
};

extern ostream &operator<<(ostream &strm, const LatLng &ll);
extern ostream &operator<<(ostream &strm, const DDLatLng &dll);
extern ostream &operator<<(ostream &strm, const UtmLatLng &ull);
extern GPS myGPS;

extern CLatLng cll;
// extern UtmLatLng nowMark;
// extern ofstream fileMark;
extern ofstream fileClub;
extern ofstream fileAll;

#endif  // CLATLNG_H
