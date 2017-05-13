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

vector<CHoleDescription> vHoleDesc;
vector<CHoleScore> vHoleScore;

void initHoleDescVector() {
  for (int ix = 0; ix < k18; ++ix) {
    CHoleDescription chd;
    vHoleDesc.push_back(chd);
  }
  vHoleDesc[0].setHoleDesc("1", "492", "7", "5");
  vHoleDesc[1].setHoleDesc("2", "185", "13", "3");
  vHoleDesc[2].setHoleDesc("3", "421", "1", "4");
  vHoleDesc[3].setHoleDesc("4", "510", "3", "5");
  vHoleDesc[4].setHoleDesc("5", "395", "5", "4");
  vHoleDesc[5].setHoleDesc("6", "383", "11", "4");
  vHoleDesc[6].setHoleDesc("7", "135", "17", "3");
  vHoleDesc[7].setHoleDesc("8", "368", "9", "4");
  vHoleDesc[8].setHoleDesc("9", "312", "5", "4");
  vHoleDesc[9].setHoleDesc("10", "342", "8", "4");
  vHoleDesc[10].setHoleDesc("11", "145", "16", "3");
  vHoleDesc[11].setHoleDesc("12", "471", "12", "5");
  vHoleDesc[12].setHoleDesc("13", "380", "6", "4");
  vHoleDesc[13].setHoleDesc("14", "365", "4", "4");
  vHoleDesc[14].setHoleDesc("15", "331", "18", "4");
  vHoleDesc[15].setHoleDesc("16", "521", "2", "5");
  vHoleDesc[16].setHoleDesc("17", "168", "14", "3");
  vHoleDesc[17].setHoleDesc("18", "337", "10", "4");
}

void initHoleScoreVector() {
    for (int ix = 0; ix < k18; ++ix) {
      CHoleScore chs;
      vHoleScore.push_back(chs);
    }
}

void initGlobals() {
  gCurrentHole = 1;
  gToday = time(nullptr);
  gNowTimeStr = "";
  gStartHoleTimeStr = "";
  gStartRoundTimeStr = "";

  bRoundStarted = false;

  for (int ii = 0; ii < k18; ++ii) bPlayedHole[ii] = false;

  initHoleDescVector();
  initHoleScoreVector();
}
