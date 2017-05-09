#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int gCurrentHole;
time_t gToday;

#if GPSTIME
int gNowGPStime;
int gStartHoleGPStime;
int gStartRoundGPStime;
#else
time_t gNowClockTm;
time_t gStartHoleClockTm;
time_t gStartRoundClockTm;
#endif

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
#if GPSTIME
  gNowGPStime = 0;
  gStartHoleGPStime = 0;
  gStartRoundGPStime = 0;
#else
  gNowGPStime = 0;
  gStartHoleGPStime = 0;
  gStartRoundGPStime = 0;
#endif

  bRoundStarted = false;

  for (int ii = 0; ii < k18; ++ii) bPlayedHole[ii] = false;
}
