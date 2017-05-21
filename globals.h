#ifndef CGLOBALS_H
#define CGLOBALS_H

#include <FL/Fl_Button.H>

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
const int kBtnH = 48;
const int kBtnW = 140;

extern int gGpsAvgNum;  // number of UTM points to average

extern int gCurrentHole;
extern time_t gToday;

extern string gNowTimeStr;
extern string gStartHoleTimeStr;
extern string gStartRoundTimeStr;

extern bool bRoundStarted;
extern bool gFront9;

struct UtmLatLng {
  double lat;
  double lng;
  UtmLatLng() {
    lat = 0.0;
    lng = 0.0;
  }
  UtmLatLng(const double latitude, const double longitude) {
    lat = latitude;
    lng = longitude;
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
    score = s;
    putts = p;
    uds = u;
  }
  friend ostream& operator<<(ostream& strm, const CNGCHoles& h);
};

const int kDr = 0;
const int k3w = 1;
const int k5w = 2;
const int k7w = 3;
const int kHy = 4;
const int k2 = 5;
const int k3 = 6;
const int k4 = 7;
const int k5 = 8;
const int k6 = 9;
const int k7 = 10;
const int k8 = 11;
const int k9 = 12;
const int kPW = 13;
const int kGW = 14;
const int kSW = 15;
const int kLW = 16;
const int kx = 17;

extern array<string, k18> clubNamesRA;

const string path = "/home/pi/golf/angc/stats/";

struct ShotStats {
  string club;
  int yards;
  UtmLatLng utm;
  friend ostream& operator<<(ostream& strm, const ShotStats& sra);
};

const int kMAX_SHOTS = 7;
extern int gShotCount;
extern array<array<ShotStats, kMAX_SHOTS>, k18> roundShotsRA;
extern void initShotStats();

extern vector<CNGCHoles> vNGCHoles;

extern vector<string> vGPS;  // the complete round of nmea GPGGA sentences
extern vector<UtmLatLng> vUTM;
// extern vector<string> vClubsUsed;

extern array<bool, k18> bPlayedHole;

extern ofstream gFileScoreStats;
extern ofstream gFileShotStats;
extern ofstream gFileGPS;

extern void initGlobals();
extern int getValidDistancesCount(int hole);
extern int calcUTMdistance(const UtmLatLng& now, const UtmLatLng& prev);
extern void setButtonStyle(Fl_Button * b);
extern string getFileSuffix();

#endif  // CGLOBALS_H
