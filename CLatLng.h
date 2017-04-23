#ifndef CLATLNG_H
#define CLATLNG_H

#ifndef GPS_H
#include "gps.h"
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <FL/Fl_Input.H>

using namespace std;

struct LatLng {
  double lat;
  double lng;
  LatLng() {
    lat = 0.0;
    lng = 0.0;
  }
  void setMark( const LatLng& ll) {
      lat = ll.lat;
      lng = ll.lng;
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
  void setMark( const UtmLatLng& ll) {
      lat = ll.lat;
      lng = ll.lng;
  }
};

extern ostream& operator<< (ostream& strm, const LatLng& ll );
extern ostream& operator<< (ostream& strm, const DDLatLng& dll );
extern ostream& operator<< (ostream& strm, const UtmLatLng& ull );
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

  UtmLatLng getNowMarkUTM();

  void setRefMark(Fl_Input *input);

  // Utility functions
  void updateLatLng(const string &s);
  double updateYardage();

  void writeMark(const string &fname, Fl_Input *input);
  void writeAll(Fl_Input *input);

  // Variables
  vector<string> vGGA;         // the complete round of nmea GPGGA sentences
  vector<string> vLastNmarks;  // the last 10 vGGA sentences
  vector<LatLng> vLL;
  vector<DDLatLng> vDD;
  vector<UtmLatLng> vUTM;

 private:
 const size_t kDataPts = 10; // number of data points to average

  LatLng refLLMark;
  LatLng nowLLMark;
  UtmLatLng refUtmMark;
  UtmLatLng nowUtmMark;

  double NMEA2DecimalDegrees(const double nmea);
  DDLatLng NMEA2DecimalDegrees(const LatLng &LL);
  UtmLatLng NMEA2UTM(const LatLng &LL);
};

#endif  // CLATLNG_H
