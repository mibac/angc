#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int gCurrentHole;
time_t gToday;

ofstream gFileStats;
ofstream gFileClub;
ofstream gFileGPS;

void initGlobals() {
  gCurrentHole = 1;
  gToday = time(nullptr);

  ostringstream oss;
  oss << gToday;

  string suffix = oss.str() + ".txt";

  string s1 = "aClubs_" + suffix;
  string s2 = "aStats_" + suffix;
  string s3 = "aGPS_" + suffix;
  gFileClub.open(s1.c_str());
  gFileStats.open(s2);
  gFileGPS.open(s3);
}
