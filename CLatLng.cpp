#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

#include <unistd.h>
#include <cmath>
#include <iomanip>
#include <iostream>

#ifndef C2UTM_hpp
#include "C2UTM.hpp"
#endif

#ifndef _GPSD_GPSMM_H_
#include "libgpsmm.h"
#endif

#ifndef UTILS_H
#include "utils.h"
#endif

#define TEST_SINGLE_UTM 1

const int kPrecision = 9;
const int RETRY_TIME = 5;
const int ONE_SECOND = 1000000;

GPS myGPS;
CLatLng cll;
UtmLatLng lastMark;
UtmLatLng nowMark;
ofstream fileMark("Markers.txt");
ofstream fileAll("WalkTheCourse.txt");

ostream& operator<<(ostream& strm, const LatLng& ll) {
  strm << ll.lat << ", " << ll.lng << endl;
  return strm;
}

ostream& operator<<(ostream& strm, const DDLatLng& dll) {
  strm << dll.lat << ", " << dll.lng << endl;
  return strm;
}

ostream& operator<<(ostream& strm, const UtmLatLng& ull) {
  strm << ull.lat << ", " << ull.lng << endl;
  return strm;
}

CLatLng::CLatLng() {
  // LatLng refLLMark;
  // LatLng nowLLMark;
  // DDLatLng refDDMark;
  // DDLatLng nowDDMark;
  // UtmLatLng refUtmMark;
  // UtmLatLng nowUtmMark;
}

CLatLng::CLatLng(const string s) {}
CLatLng::CLatLng(const char* cstr) {}
CLatLng::CLatLng(const LatLng) {}

bool CLatLng::isgpsup() {
  bool ok = false;
  gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

  for (int i = 0; i < 5; ++i) {
    if (gps_rec.stream(WATCH_ENABLE | WATCH_NMEA) == NULL) {
      cout << "No GPSD running. Retry to connect in " << RETRY_TIME
           << " seconds." << endl;
      usleep(RETRY_TIME * ONE_SECOND);
      continue;  // It will try to connect to gpsd again
    } else {
      ok = true;
    }
  }
  return ok;
}

double CLatLng::NMEA2DecimalDegrees(const double nmea) {
  double deg = double(int(nmea / 100));
  double min = nmea - (deg * 100);
  double minOver60 = min / 60.0;
  double dec_deg = deg + minOver60;
  cout << fixed << setprecision(9);
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
  UtmLatLng ull;

  ull.lat = NMEA2DecimalDegrees(LL.lat);
  ull.lng = NMEA2DecimalDegrees(LL.lng);
  latlon.setLatLon(ull.lat, ull.lng);
  latlon.convert2UTM();
  ull.lat = latlon.UTMNorth;
  ull.lng = latlon.UTMEast;
  return ull;
}

void CLatLng::updateLatLng(const string& s) {
  LatLng ll;
  DDLatLng dll;
  UtmLatLng ull;

  if (myGPS.isValidGGA(s)) {
      cout << s << endl;
    vGGA.push_back(s);
    myGPS.setValuesGGA(s);

    ll.lat = myGPS.latitude;
    ll.lng = myGPS.longitude;
    vLL.push_back(ll);

    dll = NMEA2DecimalDegrees(ll);
    vDD.push_back(dll);

    ull = NMEA2UTM(ll);
    vUTM.push_back(ull);
    nowMark = ull;
  }
}

#if TEST_SINGLE_UTM
void CLatLng::setRefMark() { lastMark = nowMark; }

UtmLatLng CLatLng::getNowMarkUTM() { return nowMark; }

#else
void CLatLng::setRefMark() {
  LatLng ll;
  int n = std::min(vGGA.size(), kDataPts);

  vector<string> v(vGGA.end() - n, vGGA.end());

  for (auto itr : v) {
    if (myGPS.isValidGGA(itr)) {
      myGPS.setValuesGGA(itr);
      ll.lat += myGPS.latitude;
      ll.lng += myGPS.longitude;
    }
  }

  ll.lat /= v.size();
  ll.lng /= v.size();
  vLastNmarks = v;
  lastMark.setMark(NMEA2UTM(ll));
}

UtmLatLng CLatLng::getNowMarkUTM() {
  UtmLatLng ull;
  int n = std::min(vUTM.size(), kDataPts);
  vector<UtmLatLng> v(vUTM.end() - n, vUTM.end());

  for (auto itr : v) {
    ull.lat += itr.lat;
    ull.lng += itr.lng;
  }

  ull.lat /= n;
  ull.lng /= n;

  return ull;
}
#endif

void CLatLng::updateDistanceFromMarkerUTM(Fl_Box* box) {
  UtmLatLng u1 = nowMark;
  UtmLatLng u2 = lastMark;

  double d = sqrt(pow(u1.lng - u2.lng, 2) + pow(u1.lat - u2.lat, 2));
  d *= 1.0936139;  // meters to yards

  ostringstream oss;
  oss << (int)round(d);
  box->label(oss.str().c_str());
}

void CLatLng::writeMark(const string &s) {
  fileMark << setprecision(kPrecision);
  fileMark << s << lastMark.lng << ", " << lastMark.lat << endl;
  vLastNmarks.clear();
}

void CLatLng::writeAll() {
  fileAll << setprecision(kPrecision);
  for (auto itr : vGGA) fileAll << itr;
}
