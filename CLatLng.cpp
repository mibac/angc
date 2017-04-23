#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

#ifndef C2UTM_hpp
#include "C2UTM.hpp"
#endif

#include <cmath>
#include <iomanip>
#include <iostream>

const int kPrecision = 9;

GPS myGPS;

ostream& operator<< (ostream& strm, const LatLng& ll ) {
    strm << ll.lat << ", " << ll.lng << endl;
    return strm;
}

ostream& operator<< (ostream& strm, const DDLatLng& dll ) {
    strm << dll.lat << ", " << dll.lng << endl;
    return strm;
}

ostream& operator<< (ostream& strm, const UtmLatLng& ull ) {
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
CLatLng::CLatLng(const char *cstr) {}
CLatLng::CLatLng(const LatLng) {}

double CLatLng::NMEA2DecimalDegrees(const double nmea) {
  double deg = double(int(nmea / 100));
  double min = nmea - (deg * 100);
  double minOver60 = min / 60.0;
  double dec_deg = deg + minOver60;
  cout << fixed << setprecision(9);
  return dec_deg;
}

DDLatLng CLatLng::NMEA2DecimalDegrees(const LatLng &LL) {
  DDLatLng dll;
  dll.lat = NMEA2DecimalDegrees(LL.lat);
  dll.lng = NMEA2DecimalDegrees(LL.lng);
  return dll;
}

UtmLatLng CLatLng::NMEA2UTM(const LatLng &LL) {
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

void CLatLng::updateLatLng(const string &s) {
  LatLng ll;
  DDLatLng dll;
  UtmLatLng ull;

  if (myGPS.isValidGGA(s)) {
    vGGA.push_back(s);
    myGPS.setValuesGGA(s);

    ll.lat = myGPS.latitude;
    ll.lng = myGPS.longitude;
    vLL.push_back(ll);

    dll = NMEA2DecimalDegrees(ll);
    vDD.push_back(dll);

    ull = NMEA2UTM(ll);
    vUTM.push_back(ull);
  }
}

double CLatLng::updateYardage() {
  nowUtmMark = getNowMarkUTM();

  double lat = nowUtmMark.lat - refUtmMark.lat;
  double lng = nowUtmMark.lng - refUtmMark.lng;
  double d = sqrt(lat * lat + lng * lng);


  return d *= 1.0936139;  // meters to yards
}

void CLatLng::setRefMark(Fl_Input *input) {
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

  refLLMark.setMark(ll);
  refUtmMark.setMark(NMEA2UTM(ll));

  ostringstream oss;
  oss << ll.lat << ", " << ll.lng << "G M " << vGGA.size() << ", " << v.size();
  input->value(oss.str().c_str());
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

void CLatLng::writeMark(const string &fname, Fl_Input *input) {
  if (fname.empty()) return;

  ofstream file(fname.c_str());

  file << setprecision(kPrecision);

  for (auto itr : vLastNmarks) {
    file << itr;
  }

  int n = vLastNmarks.size();

  file << "---- NMEA (lat, lon) ----\t" << vLL.size() << endl;
  for (size_t i = vLL.size() - n; i < vLL.size(); ++i)
    file << vLL[i];

  file << "---- Decimal Degrees (lat, lon) ----\t" << vDD.size() << endl;
  for (size_t i = vDD.size() - n; i < vDD.size(); ++i)
    file << vDD[i];

  file << "---- UTM (lat, lon) ----\t" << vUTM.size() << endl;
  for (size_t i = vUTM.size() - n; i < vUTM.size(); ++i)
    file << vUTM[i];

  file.close();

  vLastNmarks.clear();

  string s = fname + " written";
  input->value(s.c_str());
}

void CLatLng::writeAll(Fl_Input *input) {
  string fname = "WalkTheCourse.txt";

  ofstream file(fname.c_str());

  file << setprecision(kPrecision);

  for (auto itr : vGGA) file << itr;

  file << "---- nmeaLat (lat, lon) ----" << endl;
  for (size_t i = 0; i < vLL.size(); ++i)
    file << vLL[i];

  file << "---- Decimal Degrees (lat, lon) ----" << endl;
  for (size_t i = 0; i < vDD.size(); ++i)
    file << vDD[i];

  file << "---- UTM (lat, lon, sz) ----" << endl;
  for (size_t i = 0; i < vUTM.size(); ++i)
    file << vUTM[i];

  file.close();

  string s = fname + " written";
  input->value(s.c_str());
}
