#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int gCurrentHole;
time_t gToday;
time_t gLastClockTm;
time_t gNowClockTm;
time_t gStartHoleClockTm;
time_t gStartRoundClockTm;
// time_t gRunningUTC;

bool bRoundStartFlag;

ofstream gFileStats;
ofstream gFileClub;
ofstream gFileGPS;


vector<string> vGPS;  // the complete round of nmea GPGGA sentences
vector<UtmLatLng> vUTM;
vector<string> vClubsUsed;
array<bool, k18> bPlayedHole;

void initGlobals() {
  gCurrentHole = 1;
  gLastClockTm = 0;
  gNowClockTm = 0;
  gStartHoleClockTm = 0;
  gStartRoundClockTm = 0;
  //gRunningUTC = 0;
  bRoundStartFlag = false;
  gToday = time(nullptr);

  for( int ii = 0; ii < k18; ++ii) bPlayedHole[ii] = false;

}
