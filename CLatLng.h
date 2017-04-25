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

extern ostream &operator<<(ostream &strm, const LatLng &ll);
extern ostream &operator<<(ostream &strm, const DDLatLng &dll);
extern ostream &operator<<(ostream &strm, const UtmLatLng &ull);
extern GPS myGPS;

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

  bool isgpsup();
  void setRefMark();

  // Utility functions
  void updateLatLng(const string &s);
  void updateDistanceFromMarkerUTM(Fl_Box *box);

  void writeMark(const string &s);
  void writeAll();

  // Variables
  vector<string> vGGA;         // the complete round of nmea GPGGA sentences
  vector<string> vLastNmarks;  // the last 10 vGGA sentences
  vector<LatLng> vLL;
  vector<DDLatLng> vDD;
  vector<UtmLatLng> vUTM;

 private:

  UtmLatLng getNowMarkUTM();

  double NMEA2DecimalDegrees(const double nmea);
  DDLatLng NMEA2DecimalDegrees(const LatLng &LL);
  UtmLatLng NMEA2UTM(const LatLng &LL);
};

extern CLatLng cll;
extern UtmLatLng lastMark;
extern UtmLatLng nowMark;
extern ofstream fileMark;
extern ofstream fileAll;

#endif  // CLATLNG_H
