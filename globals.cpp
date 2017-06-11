#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int gCurrentHole;
int gGpsAvgNum;
time_t gToday;

string gNowTimeStr;
string gStartHoleTimeStr;
string gStartRoundTimeStr;

bool bRoundStarted;
bool gFront9;

Fl_Button* markBtn = nullptr;
string markBtnLabel = "Mark\n1";

CTimeDisplay* gTmDisplay = nullptr;
Fl_Text_Buffer* gTmbuff = nullptr;
string timeStr = "Start";

ofstream gFileGPS;
ofstream gFileScore;
ofstream gFileShortScores;
ofstream gFileShots;
ofstream gTmpGPS;
ofstream gTmpScore;
ofstream gTmpShots;
ofstream gTmpTimes;

vector<string> vGPS;  // the complete round of nmea GPGGA sentences
vector<UtmLatLng> vUTM;
// vector<string> vClubsUsed;
array<bool, k18> bPlayedHole;

vector<CNGCScorecardData> vNGCHoles;
vector<ScoreData> vsd;

array<string, k18> clubNamesRA;

int gShotCount;
array<ShotStats, k18> gShotRA;

UtmLatLng gThisGreen;
UtmLatLng gNextTee;

ostream& operator<<(ostream& strm, const UtmLatLng& ull) {
  strm << setprecision(10) << ull.lng << "\t" << ull.lat;
  return strm;
}

int calcScore(bool front9) {
  int sum = 0;
  int tmp = 0;
  if (front9) {
    for (int ix = 0; ix < 9; ++ix) {
      if (vsd[ix].score == "")
        tmp = 0;
      else
        tmp = stoi(vsd[ix].score);
      sum += tmp;
    }
  } else {
    for (int ix = 9; ix < k18; ++ix) {
      if (vsd[ix].score == "")
        tmp = 0;
      else
        tmp = stoi(vsd[ix].score);
      sum += tmp;
    }
  }
  return sum;
}

int calcPutts(bool front9) {
  int sum = 0;
  int tmp = 0;
  if (front9) {
    for (int ix = 0; ix < 9; ++ix) {
      if (vsd[ix].putts == "")
        tmp = 0;
      else
        tmp = stoi(vsd[ix].putts);
      sum += tmp;
    }
  } else {
    for (int ix = 9; ix < k18; ++ix) {
      if (vsd[ix].putts == "")
        tmp = 0;
      else
        tmp = stoi(vsd[ix].putts);
      sum += tmp;
    }
  }
  return sum;
}

int calcUDs(bool front9) {
  int sum = 0;
  int tmp = 0;
  if (front9) {
    for (int ix = 0; ix < 9; ++ix) {
      if (vsd[ix].uds == "")
        tmp = 0;
      else
        tmp = stoi(vsd[ix].uds);
      sum += tmp;
    }
  } else {
    for (int ix = 9; ix < k18; ++ix) {
      if (vsd[ix].uds == "")
        tmp = 0;
      else
        tmp = stoi(vsd[ix].uds);
      sum += tmp;
    }
  }
  return sum;
}

bool isGIR(int par, int score, int putts) {
  if ((score == par) && (putts == 2))
    return true;
  else if ((score + 1 == par) && (putts == 1))
    return true;
  else
    return false;
}

int calcGIRs(bool front9) {
  int sum = 0;
  int p = 0;
  int s = 0;
  int t = 0;
  if (front9) {
    for (int ix = 0; ix < 9; ++ix) {
      if (vNGCHoles[ix].par == "")
        p = 0;
      else
        p = stoi(vNGCHoles[ix].par);

      if (vsd[ix].score == "")
        s = 0;
      else
        s = stoi(vsd[ix].score);

      if (vsd[ix].putts == "")
        t = 0;
      else
        t = stoi(vsd[ix].putts);
      if (isGIR(p, s, t)) sum++;
    }
  } else {
    for (int ix = 0; ix < 9; ++ix) {
      if (vNGCHoles[ix].par == "")
        p = 0;
      else
        p = stoi(vNGCHoles[ix].par);

      if (vsd[ix].score == "")
        s = 0;
      else
        s = stoi(vsd[ix].score);

      if (vsd[ix].putts == "")
        t = 0;
      else
        t = stoi(vsd[ix].putts);
      if (isGIR(p, s, t)) sum++;
    }
  }
  return sum;
}

ScoreTypes scoretype;

string getScoreType(int par, int score) {
  int n = score - par;     // order important
  if (score == 0) n = 99;  // bad case
  string s;
  switch (ScorType(n)) {
    case ScorType::albatross:
      s = "albatross";
      scoretype.albatross++;
      break;
    case ScorType::eagle:
      s = "eagle";
      scoretype.eagles++;
      break;
    case ScorType::birdie:
      s = "birdie";
      scoretype.birdies++;
      break;
    case ScorType::par:
      s = "par";
      scoretype.pars++;
      break;
    case ScorType::bogey:
      s = "bogey";
      scoretype.bogies++;
      break;
    case ScorType::dbogey:
      s = "double";
      scoretype.doubles++;
      break;
    case ScorType::tbogey:
      s = "triple";
      scoretype.triples++;
      break;
    case ScorType::x:
      s = "X";
      scoretype.x++;
      break;
    default:
      s = "";
      break;
  }
  if (score == 1) s = "ACE";
  return s;
}

// clang-format off
// ostream& operator<<(ostream& strm, const CNGCScorecardData& h) {
//   strm << h.hole << "\t";
//   strm << h.yards << "\t";
//   strm << h.hdcp << "\t";
//   strm << h.par << "\t";
//   strm << h.score << "\t";
//   strm << h.putts << "\t";
//   strm << h.uds << "\t";
//   int par = stoi(h.par);
//   int score;
//   int putts;
//   if (h.score == "")
//     score = 0;
//   else
//     score = stoi(h.score);
//   if (h.putts == "")
//     putts = 99;
//   else
//     putts = stoi(h.putts);
//
//   strm << getScoreType(par, score) << "\t";
//   if (isGIR (par, score, putts))
//     strm << "GIR" << endl;
//   else
//     strm << "\t" << endl;
//   return strm;
// }
// clang-format on

void ScoreData::setHoleScore(string s, string p, string u) {
  score = s;
  putts = p;
  uds = u;
}

// clang-format off
ostream& operator<<(ostream& strm, const ScoreData& sd) {
    strm << sd.score << sd.putts << sd.uds;
  return strm;
}
// clang-format on

// clang-format off
ostream& operator<<(ostream& strm, const holeStats& h) {
    strm << h.club << "\t"
         << h.yards
         << "\t" << setprecision(10)
         << h.utm.lat << "\t"
         << h.utm.lng << endl;
  return strm;
}
// clang-format on

// clang-format off
ostream& operator<<(ostream& strm, const ShotStats& sra) {
  for (int ix = 0; ix < sra.nmarks - 1; ++ix) {
    strm << sra.shot[ix];
  }
  return strm;
}
// clang-format on

void initNGCHolesVector() {
  for (int ix = 0; ix < k18; ++ix) {
    CNGCScorecardData h;
    vNGCHoles.push_back(h);
  }
  vNGCHoles[0].setHoleDesc("1", "492", "7", "5");
  vNGCHoles[1].setHoleDesc("2", "185", "13", "3");
  vNGCHoles[2].setHoleDesc("3", "421", "1", "4");
  vNGCHoles[3].setHoleDesc("4", "510", "3", "5");
  vNGCHoles[4].setHoleDesc("5", "395", "5", "4");
  vNGCHoles[5].setHoleDesc("6", "383", "11", "4");
  vNGCHoles[6].setHoleDesc("7", "135", "17", "3");
  vNGCHoles[7].setHoleDesc("8", "368", "9", "4");
  vNGCHoles[8].setHoleDesc("9", "312", "15", "4");
  vNGCHoles[9].setHoleDesc("10", "342", "8", "4");
  vNGCHoles[10].setHoleDesc("11", "145", "16", "3");
  vNGCHoles[11].setHoleDesc("12", "471", "12", "5");
  vNGCHoles[12].setHoleDesc("13", "380", "6", "4");
  vNGCHoles[13].setHoleDesc("14", "365", "4", "4");
  vNGCHoles[14].setHoleDesc("15", "331", "18", "4");
  vNGCHoles[15].setHoleDesc("16", "521", "2", "5");
  vNGCHoles[16].setHoleDesc("17", "168", "14", "3");
  vNGCHoles[17].setHoleDesc("18", "337", "10", "4");
}

void initHoleScores() {
  ScoreData sd;
  for (int ix = 0; ix < k18; ++ix) vsd.push_back(sd);
}

void initTestScores() {
  vsd[0].setHoleScore("7", "3", "4");
  vsd[1].setHoleScore("4", "2", "3");
  vsd[2].setHoleScore("5", "2", "2");
  vsd[3].setHoleScore("5", "1", "2");
  vsd[4].setHoleScore("5", "5", "3");
  vsd[5].setHoleScore("5", "2", "2");
  vsd[6].setHoleScore("3", "1", "2");
  vsd[7].setHoleScore("6", "2", "3");
  vsd[8].setHoleScore("7", "3", "4");
  vsd[9].setHoleScore("4", "1", "2");
  vsd[10].setHoleScore("5", "3", "3");
  vsd[11].setHoleScore("5", "2", "2");
  vsd[12].setHoleScore("6", "2", "4");
  vsd[13].setHoleScore("6", "2", "3");
  vsd[14].setHoleScore("6", "3", "3");
  vsd[15].setHoleScore("5", "2", "2");
  vsd[16].setHoleScore("3", "2", "2");
  vsd[17].setHoleScore("6", "2", "2");
}

void initClubNames() {
  clubNamesRA[kDr] = "Dr";
  clubNamesRA[k3w] = "3w";
  clubNamesRA[k5w] = "5w";
  clubNamesRA[k7w] = "7w";
  clubNamesRA[kHy] = "Hy";
  clubNamesRA[k2] = "2";
  clubNamesRA[k3] = "3";
  clubNamesRA[k4] = "4";
  clubNamesRA[k5] = "5";
  clubNamesRA[k6] = "6";
  clubNamesRA[k7] = "7";
  clubNamesRA[k8] = "8";
  clubNamesRA[k9] = "9";
  clubNamesRA[kPW] = "PW";
  clubNamesRA[kGW] = "GW";
  clubNamesRA[kSW] = "SW";
  clubNamesRA[kLW] = "LW";
  clubNamesRA[kx] = "x";
}

void initShotStats() {
  gShotCount = 0;
  for (int hole = 0; hole < k18; ++hole) {
    gShotRA[hole].nmarks = 0;
    for (int ix = 0; ix < kMAX_SHOTS; ++ix) {
      gShotRA[hole].shot[ix].yards = 0;
      gShotRA[hole].shot[ix].club = "";
      gShotRA[hole].shot[ix].utm.lat = 0.0;
      gShotRA[hole].shot[ix].utm.lng = 0.0;
    }
  }
}

void openTmpFiles() {
  string dir = "/home/pi/golf/stats/";
  string s1 = dir + "tmpGPS.txt";
  gTmpGPS.open(s1.c_str(), ios::app);
  gTmpGPS << setprecision(kPrecision);
  gTmpGPS << asctime(std::localtime(&gToday));

  string s2 = dir + "tmpScore.txt";
  gTmpScore.open(s2.c_str(), ios::app);
  // gTmpScore << setprecision(kPrecision);
  gTmpScore << asctime(std::localtime(&gToday));

  string s3 = dir + "tmpShots.txt";
  gTmpShots.open(s3.c_str(), ios::app);
  gTmpShots << setprecision(kPrecision);
  gTmpShots << asctime(std::localtime(&gToday));

  string s4 = dir + "tmpTimes.txt";
  gTmpTimes.open(s4.c_str(), ios::app);
  gTmpTimes << asctime(std::localtime(&gToday));
}

array<sHoleTimes, k18> gHoleTimeRA;
void initHoleTimes() {
  for (int ix = 0; ix < k18; ++ix) {
    gHoleTimeRA[ix].begstr = "0";
    gHoleTimeRA[ix].endstr = "0";
  }
}

void initGlobals() {
  gCurrentHole = 1;
  gGpsAvgNum = 3;
  gToday = time(nullptr);
  gNowTimeStr = "";
  gStartHoleTimeStr = "";
  gStartRoundTimeStr = "";

  bRoundStarted = false;
  gFront9 = true;

  for (int ii = 0; ii < k18; ++ii) bPlayedHole[ii] = false;

  initNGCHolesVector();
  initHoleScores();
  initTestScores();
  // initScoreResults();
  initClubNames();
  initShotStats();
  openTmpFiles();
  initHoleTimes();
}

int countValidDistances(int hole) {
  int n = gShotRA[hole].nmarks - 1;
  if (n < 0) n = 0;
  return n;
}

int calcUTMdistance(const UtmLatLng& now, const UtmLatLng& prev) {
  double x = now.lng - prev.lng;
  double y = now.lat - prev.lat;
  double d = sqrt(x * x + y * y);
  d *= 1.0936139;  // meters to yards
  // cout << "now " << now << endl;
  // cout << "prev " << prev << endl;
  // cout << "dist " << d << endl;
  return (int)round(d);
}

void setButtonStyle(Fl_Button* b) {
  b->resize(b->x(), b->y(), kBtnW, kBtnH);
  b->color(FL_WHITE);
  b->down_color(FL_DARK_BLUE);
  b->labelfont(1);
  b->labelsize(36);
}

string getFileSuffix() {
  string suffix;
  time_t result = time(nullptr);
  asctime(localtime(&result));
  suffix = to_string(result);

  struct tm* t;
  t = localtime(&gToday);
  string y = to_string(t->tm_year - 100);
  string m = to_string(t->tm_mon + 1);
  if (m.length() == 1) m = "0" + m;
  string d = to_string(t->tm_mday);
  if (d.length() == 1) d = "0" + d;
  suffix = suffix + "_" + y + m + d + ".txt";
  return suffix;
}

Fl_Color getBkgRGBcolor() {
  // Jack's decimal * 255
  // return fl_rgb_color(162, 255, 146);

  // experiments
  return fl_rgb_color(150, 255, 160);
}
