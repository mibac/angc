#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

#include <unistd.h>
#include <cmath>
#include <iomanip>
#include <iostream>

#ifndef C2UTM_hpp
#include "C2UTM.h"
#endif

#ifndef _GPSD_GPSMM_H_
#include "libgpsmm.h"
#endif

const int RETRY_TIME = 5;
const int ONE_SECOND = 1000000;

GPS myGPS;
CLatLng cll;

#if USEGPS
CLatLng::CLatLng() {}

CLatLng::CLatLng(const string s) {}
CLatLng::CLatLng(const char* cstr) {}
CLatLng::CLatLng(const LatLng) {}

double CLatLng::NMEA2DecimalDegrees(const double nmea) {
  double deg = double(int(nmea / 100));
  double min = nmea - (deg * 100);
  double minOver60 = min / 60.0;
  double dec_deg = deg + minOver60;
  return dec_deg;
}

DDLatLng CLatLng::NMEA2DecimalDegrees(const LatLng& LL) {
  DDLatLng dll;
  dll.lat = NMEA2DecimalDegrees(LL.lat);
  dll.lng = NMEA2DecimalDegrees(LL.lng);
  return dll;
}

UtmLatLng CLatLng::NMEA2UTM(const LatLng& LL) {
  LL2UTM latlon;  //	JACK C2UTM
  DDLatLng dll;
  UtmLatLng ull;

  dll.lat = NMEA2DecimalDegrees(LL.lat);
  dll.lng = NMEA2DecimalDegrees(LL.lng);
  latlon.setLatLon(dll.lat, dll.lng);
  latlon.convert2UTM();
  ull.lat = latlon.UTMNorth;
  ull.lng = latlon.UTMEast;
  return ull;
}

void CLatLng::updateLatLng(const string& s) {
  vGPS.push_back(s);
  myGPS.setValuesGGA(s);
  LatLng ll(myGPS.latitude, myGPS.longitude);
  UtmLatLng ull = NMEA2UTM(ll);
  vUTM.push_back(ull);
  gNowTimeStr = to_string(myGPS.UTC);
}

UtmLatLng CLatLng::getMark(size_t avg) {
  UtmLatLng ull;
  int n = std::min(vUTM.size(), avg);
  vector<UtmLatLng> v(vUTM.end() - n, vUTM.end());

  for (auto itr : v) {
    ull.lat += itr.lat;
    ull.lng += itr.lng;
  }

  ull.lat /= n;
  ull.lng /= n;

  return ull;
}

UtmLatLng CLatLng::getNowMark() { return getMark(gGpsAvgNum); }

#else
CLatLng::CLatLng() {}

CLatLng::CLatLng(const string s) {}
CLatLng::CLatLng(const char* cstr) {}
CLatLng::CLatLng(const LatLng) {}

double CLatLng::NMEA2DecimalDegrees(const double nmea) { return 0; }

DDLatLng CLatLng::NMEA2DecimalDegrees(const LatLng& LL) {
  DDLatLng dll;
  return dll;
}

UtmLatLng CLatLng::NMEA2UTM(const LatLng& LL) {
  UtmLatLng ull;  //	JACK C2UTM
  return ull;
}

void CLatLng::updateLatLng(const string& s) {}

UtmLatLng CLatLng::getMark(size_t avg) {
  UtmLatLng ull;
  return ull;
}

UtmLatLng CLatLng::getNowMark() { return getMark(gGpsAvgNum); }

#endif
