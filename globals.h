#ifndef CGLOBALS_H
#define CGLOBALS_H

#include <array>
#include <ctime>
#include <fstream>
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

class CHoleDescription {
 public:
  string hole;
  string yards;
  string hdcp;
  string par;
  CHoleDescription() : hole(""), yards(""), hdcp(""), par("") {}
  void setHoleDesc(const string h, const string y, const string c,
                   const string p) {
    hole = h;
    yards = y;
    hdcp = c;
    par = p;
  }
};
extern vector<CHoleDescription> vHoleDesc;

class CHoleScore {
public:
  int score;
  int putts;
  int uds;
  CHoleScore() : score(0), putts(0), uds(0) {}
  void setHoleScore(const int s, const int p, const int u) {
      score = s;
      putts = p;
      uds = u;
  }
};
extern vector<CHoleScore> vHoleScore;

extern vector<string> vGPS;  // the complete round of nmea GPGGA sentences
extern vector<UtmLatLng> vUTM;
extern vector<string> vClubsUsed;
extern array<bool, k18> bPlayedHole;

extern ofstream gFileStats;
extern ofstream gFileClub;
extern ofstream gFileGPS;

extern void initGlobals();

#endif  // CGLOBALS_H
