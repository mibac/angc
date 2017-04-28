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

#ifndef UTILS_H
#include "utils.h"
#endif

const size_t kUTMpts = 3;  // number of UTM points to average
const int kPrecision = 9;
const int RETRY_TIME = 5;
const int ONE_SECOND = 1000000;

GPS myGPS;
CLatLng cll;
// UtmLatLng lastMark;
// UtmLatLng nowMark;
ofstream fileMark("aMarkers.txt");
ofstream fileClub("aClubs.txt");
ofstream fileAll("aWalkTheCourse.txt");

ostream& operator<<(ostream& strm, const LatLng& ll) {
  strm << ll.lat << ", " << ll.lng;
  return strm;
}

ostream& operator<<(ostream& strm, const DDLatLng& dll) {
  strm << dll.lat << ", " << dll.lng;
  return strm;
}

ostream& operator<<(ostream& strm, const UtmLatLng& ull) {
  strm << ull.lat << ", " << ull.lng;
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

// bool CLatLng::isgpsup() {
//   bool ok = false;
//   gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
//
//   for (int i = 0; i < 5; ++i) {
//     if (gps_rec.stream(WATCH_ENABLE | WATCH_NMEA) == NULL) {
//       cout << "No GPSD running. Retry to connect in " << RETRY_TIME
//            << " seconds." << endl;
//       usleep(RETRY_TIME * ONE_SECOND);
//       continue;  // It will try to connect to gpsd again
//     } else {
//       ok = true;
//     }
//   }
//   return ok;
// }

double CLatLng::NMEA2DecimalDegrees(const double nmea) {
  double deg = double(int(nmea / 100));
  double min = nmea - (deg * 100);
  double minOver60 = min / 60.0;
  double dec_deg = deg + minOver60;
  // cout << fixed << setprecision(9);
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
  if (myGPS.isValidGGA(s)) {
    // cout << s;
    vGGA.push_back(s);
    myGPS.setValuesGGA(s);
    LatLng ll(myGPS.latitude, myGPS.longitude);
    UtmLatLng ull = NMEA2UTM(ll);
    vUTM.push_back(ull);
  }
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

void CLatLng::setRefMark() { lastMark = getMark(kUTMpts); }

UtmLatLng CLatLng::getNowMark() { return getMark(kUTMpts); }

string CLatLng::distanceFromLastMark() {
  UtmLatLng u1 = getNowMark();
  UtmLatLng u2 = lastMark;
  double x = u1.lng - u2.lng;
  double y = u1.lat - u2.lat;

  double d = sqrt(x * x + y * y);
  d *= 1.0936139;  // meters to yards

  ostringstream oss;
  oss << (int)round(d);
  return oss.str();
}

void CLatLng::writeMark(const string& s) {
  fileMark << setprecision(kPrecision);
  fileMark << s << lastMark.lng << ", " << lastMark.lat << endl;
}

void CLatLng::writeClub(const string& s) {
  fileClub << currentHole << ":\t" << s << "\t" << distanceFromLastMark()
                    << "\t" << getNowMark() << "\t" << lastMark << endl;
}

void CLatLng::writeAll() {
  fileAll << setprecision(kPrecision);
  for (auto itr : vGGA) fileAll << itr;
}
