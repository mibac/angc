#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <iostream>
#include <sstream>
#include <string>

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

void initGlobals() {
  gCurrentHole = 1;
  gToday = time(nullptr);
  gNowTimeStr = "";
  gStartHoleTimeStr = "";
  gStartRoundTimeStr = "";

  bRoundStarted = false;

  for (int ii = 0; ii < k18; ++ii) bPlayedHole[ii] = false;
}
