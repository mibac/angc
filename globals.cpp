#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <cmath>
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

ofstream gFileScore;
ofstream gFileShotStats;
ofstream gFileGPS;

vector<string> vGPS;  // the complete round of nmea GPGGA sentences
vector<UtmLatLng> vUTM;
// vector<string> vClubsUsed;
array<bool, k18> bPlayedHole;

vector<CNGCHoles> vNGCHoles;
array<string, k18> clubNamesRA;

int gShotCount;
array<ShotStats, k18> gShotRA;

ostream& operator<<(ostream& strm, const UtmLatLng& ull) {
  strm << setprecision(10) << ull.lng << "\t" << ull.lat;
  return strm;
}

int calcScore(bool front9) {
  int sum = 0;
  if (front9) {
    for (int ix = 0; ix < 9; ++ix) sum += stoi(vNGCHoles[ix].score);
  } else {
    for (int ix = 9; ix < k18; ++ix) sum += stoi(vNGCHoles[ix].score);
  }
  return sum;
}

int calcPutts(bool front9) {
  int sum = 0;
  if (front9) {
    for (int ix = 0; ix < 9; ++ix) sum += stoi(vNGCHoles[ix].putts);
  } else {
    for (int ix = 9; ix < k18; ++ix) sum += stoi(vNGCHoles[ix].putts);
  }
  return sum;
}

int calcUDs(bool front9) {
  int sum = 0;
  if (front9) {
    for (int ix = 0; ix < 9; ++ix) sum += stoi(vNGCHoles[ix].uds);
  } else {
    for (int ix = 9; ix < k18; ++ix) sum += stoi(vNGCHoles[ix].uds);
  }
  return sum;
}

int birdies = 0;
int pars = 0;
int bogies = 0;
int doubles = 0;
int triples = 0;

string getScoreType(int par, int score) {
    int n = score - par; // order important
    string s;
    switch (ScoreType(n)) {
    case ScoreType::albatross:
        s = "albatross";
        break;
    case ScoreType::eagle:
        s = "eagle";
        break;
    case ScoreType::birdie:
        s = "birdie";
        birdies++;
        break;
    case ScoreType::par:
        s = "par";
        pars++;
        break;
    case ScoreType::bogey:
        s = "bogey";
        bogies++;
        break;
    case ScoreType::dbogey:
        s = "double";
        doubles++;
        break;
    case ScoreType::tbogey:
        s = "triple";
        triples++;
        break;
    case ScoreType::x:
        s = "X";
        break;
    default:
        s = "unknown";
        break;
    }
    if (score == 1)
        s = "ACE";
    return s;
}

void writeScores() {
  int fscore = calcScore(true);
  int bscore = calcScore(false);
  int fputts = calcPutts(true);
  int bputts = calcPutts(false);
  int fuds = calcUDs(true);
  int buds = calcUDs(false);

  string s = pathScores + "aScore_" + getFileSuffix();
  gFileScore.open(s.c_str());
  gFileScore << asctime(std::localtime(&gToday));
  /// clang-format off
  gFileScore << "Hole\tYards\tHdcp\tPar\tScore\tPutts\tUD\n";
  for (int ix = 0; ix < k18; ++ix) {
      int par = stoi(vNGCHoles[ix].par);
      int score = stoi(vNGCHoles[ix].score);
    gFileScore << vNGCHoles[ix].hole << "\t";
    gFileScore << vNGCHoles[ix].yards << "\t";
    gFileScore << vNGCHoles[ix].hdcp << "\t";
    gFileScore << par << "\t";
    gFileScore << score << "\t";
    gFileScore << vNGCHoles[ix].putts << "\t";
    gFileScore << vNGCHoles[ix].uds << "\t";
    gFileScore << getScoreType(par, score) << endl;
  }
  gFileScore << "Score \t" << fscore << "\t" << bscore << "\t" << fscore + bscore
             << endl;
  gFileScore << "Putts \t" << fputts << "\t" << bputts << "\t" << fputts + bputts
             << endl;
  gFileScore << "Updown\t" << fuds << "\t" << buds << "\t" << fuds + buds << endl;
  gFileScore << "Birdies\t" << birdies << endl;
  gFileScore << "Pars\t" << pars << endl;
  gFileScore << "Doubles\t" << doubles << endl;
  gFileScore << "Triples\t" << triples << endl;
}

// clang-format off
ostream& operator<<(ostream& strm, const ShotStats& sra) {
  for (int ix = 0; ix < sra.nmarks - 1; ++ix) {
    strm << sra.holeStatsRA[ix].club << "\t"
         << sra.holeStatsRA[ix].yards
         << "\t" << setprecision(10)
         << sra.holeStatsRA[ix].utm.lat << "\t"
         << sra.holeStatsRA[ix].utm.lng << endl;
  }
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
      gShotRA[hole].holeStatsRA[ix].yards = 0;
      gShotRA[hole].holeStatsRA[ix].club = "";
      gShotRA[hole].holeStatsRA[ix].utm.lat = 0.0;
      gShotRA[hole].holeStatsRA[ix].utm.lng = 0.0;
    }
  }
}

void writeShotStatsFileHeader() {
  string s = pathShots + "aShots_" + getFileSuffix();
  gFileShotStats.open(s.c_str());
  gFileShotStats << asctime(std::localtime(&gToday));
  gFileShotStats << "Club\tDist\tLng\tLat" << endl;
  gFileShotStats.flush();
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
  // initScoreResults();
  initClubNames();
  initShotStats();
  writeShotStatsFileHeader();
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
  string m = to_string(t->tm_mon);
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
