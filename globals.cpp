#ifndef CGLOBALS_H
#include "globals.h"
#endif

using namespace std;

int gCurrentHole;
time_t gToday;

string gNowTimeStr;
string gStartHoleTimeStr;
string gStartRoundTimeStr;

bool bRoundStarted;

ofstream gFileStats;
ofstream gFileClub;
ofstream gFileGPS;

vector<string> vGPS;  // the complete round of nmea GPGGA sentences
vector<UtmLatLng> vUTM;
vector<string> vClubsUsed;
array<bool, k18> bPlayedHole;

vector<CNGCHoles> vNGCHoles;

// clang-format off
ostream& operator<<(ostream& strm, const CNGCHoles& h) {
  strm << h.hole << "\t"
        << h.yards << "\t"
        << h.hdcp << "\t"
        << h.par << "\t"
        << h.score << "\t"
        << h.putts << "\t"
        << h.uds << endl;
  return strm;
}
// clang-format on

void initNGCHolesVector() {
  for (int ix = 0; ix < k18; ++ix) {
    CNGCHoles h;
    vNGCHoles.push_back(h);
  }
  vNGCHoles[0].setHoleDesc("1", "492", "7", "5", "0", "0", "0");
  vNGCHoles[1].setHoleDesc("2", "185", "13", "3", "0", "0", "0");
  vNGCHoles[2].setHoleDesc("3", "421", "1", "4", "0", "0", "0");
  vNGCHoles[3].setHoleDesc("4", "510", "3", "5", "0", "0", "0");
  vNGCHoles[4].setHoleDesc("5", "395", "5", "4", "0", "0", "0");
  vNGCHoles[5].setHoleDesc("6", "383", "11", "4", "0", "0", "0");
  vNGCHoles[6].setHoleDesc("7", "135", "17", "3", "0", "0", "0");
  vNGCHoles[7].setHoleDesc("8", "368", "9", "4", "0", "0", "0");
  vNGCHoles[8].setHoleDesc("9", "312", "5", "4", "0", "0", "0");
  vNGCHoles[9].setHoleDesc("10", "342", "8", "4", "0", "0", "0");
  vNGCHoles[10].setHoleDesc("11", "145", "16", "3", "0", "0", "0");
  vNGCHoles[11].setHoleDesc("12", "471", "12", "5", "0", "0", "0");
  vNGCHoles[12].setHoleDesc("13", "380", "6", "4", "0", "0", "0");
  vNGCHoles[13].setHoleDesc("14", "365", "4", "4", "0", "0", "0");
  vNGCHoles[14].setHoleDesc("15", "331", "18", "4", "0", "0", "0");
  vNGCHoles[15].setHoleDesc("16", "521", "2", "5", "0", "0", "0");
  vNGCHoles[16].setHoleDesc("17", "168", "14", "3", "0", "0", "0");
  vNGCHoles[17].setHoleDesc("18", "337", "10", "4", "0", "0", "0");
}

void initGlobals() {
  gCurrentHole = 1;
  gToday = time(nullptr);
  gNowTimeStr = "";
  gStartHoleTimeStr = "";
  gStartRoundTimeStr = "";

  bRoundStarted = false;

  for (int ii = 0; ii < k18; ++ii) bPlayedHole[ii] = false;

  initNGCHolesVector();
}
