#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int gCurrentHole;
time_t gToday;
int gLastUTC;
int gNowUTC;
int gStartHoleUTC;
int gStartRoundUTC;
int gRunningUTC;

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
  gLastUTC = 0;
  gNowUTC = 0;
  gStartHoleUTC = 0;
  gStartRoundUTC = 0;
  gRunningUTC = 0;
  bRoundStartFlag = false;
  gToday = time(nullptr);

  for( int ii = 0; ii < k18; ++ii) bPlayedHole[ii] = false;

}
