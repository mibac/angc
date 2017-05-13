#ifndef CGLOBALS_H
#define CGLOBALS_H

#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int k18 = 18;
const int kPrecision = 9;

extern int gCurrentHole;
extern time_t gToday;

extern string gNowTimeStr;
extern string gStartHoleTimeStr;
extern string gStartRoundTimeStr;

extern bool bRoundStarted;

struct UtmLatLng {
  double lat;
  double lng;
  UtmLatLng() {
    lat = 0.0;
    lng = 0.0;
  }
};

class CNGCHoles {
 public:
  string hole;
  string yards;
  string hdcp;
  string par;
  string score;
  string putts;
  string uds;

  CNGCHoles()
      : hole(""), yards(""), hdcp(""), par(""), score(""), putts(""), uds("") {}

  void setHoleDesc(const string h, const string y, const string c,
                   const string p, const string sc, const string pu,
                   const string ud) {
    hole = h;
    yards = y;
    hdcp = c;
    par = p;
    score = sc;
    putts = pu;
    uds = ud;
  }
  void setHoleScore(const string s, const string p, const string u) {
    score =s;
    putts = p;
    uds = u;
  }
  friend ostream& operator<<(ostream& strm, const CNGCHoles& h);
};
extern vector<CNGCHoles> vNGCHoles;

extern vector<string> vGPS;  // the complete round of nmea GPGGA sentences
extern vector<UtmLatLng> vUTM;
extern vector<string> vClubsUsed;
extern array<bool, k18> bPlayedHole;

extern ofstream gFileStats;
extern ofstream gFileClub;
extern ofstream gFileGPS;

extern void initGlobals();

#endif  // CGLOBALS_H
