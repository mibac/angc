#ifndef CEXITBTN_H
#include "CExitBtn.h"
#endif

#include <iomanip>

#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/fl_ask.H>

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

#ifndef CHOLEBUTTON_H
#include "CHoleBtn.h"
#endif

#ifndef CGPSTIME_H
#include "CGPStime.h"
#endif

using namespace std;

void CExitBtn::writeGPS() {
  string s = pathGPS + "aGPS_" + getFileSuffix();
  gFileGPS.open(s.c_str());
  gFileGPS << setprecision(kPrecision);
  // gFileGPS << asctime(std::localtime(&gToday));
  gFileGPS << getShortDate() << endl;

  for (auto itr : vGPS) gFileGPS << itr;
  gFileGPS.flush();
  gFileGPS.close();
}

void writeScores() {
  int fscore = calcScore(true);
  int bscore = calcScore(false);
  int fputts = calcPutts(true);
  int bputts = calcPutts(false);
  int fuds = calcUDs(true);
  int buds = calcUDs(false);
  int fGIR = calcGIRs(true);
  int bGIR = calcGIRs(false);

  scoretype.initScoreType();

  string s = pathScores + "aScore_" + getFileSuffix();
  gFileScore.open(s.c_str());
  // gFileScore << asctime(std::localtime(&gToday));
  gFileScore << getShortDate() << endl;

  /// clang-format off
  gFileScore << "Score\tPutts\tUD\n";
  for (int ix = 0; ix < k18; ++ix) {
    gFileScore << gsd[ix].score << "\t";
    gFileScore << gsd[ix].putts << "\t";
    gFileScore << gsd[ix].uds << endl;
  }

  gFileScore << "Score \t" << fscore << "\t" << bscore << "\t"
             << fscore + bscore << endl;
  gFileScore << "Putts \t" << fputts << "\t" << bputts << "\t"
             << fputts + bputts << endl;
  gFileScore << "Updown\t" << fuds << "\t" << buds << "\t" << fuds + buds
             << endl;
  gFileScore << "GIR\t" << fGIR << "\t" << bGIR << "\t" << fGIR + bGIR << endl;
  gFileScore << "Birdies\t" << scoretype.birdies << endl;
  gFileScore << "Pars\t" << scoretype.pars << endl;
  gFileScore << "Bogies\t" << scoretype.bogies << endl;
  gFileScore << "Doubles\t" << scoretype.doubles << endl;
  gFileScore << "Triples\t" << scoretype.triples << endl;
  gFileScore.flush();
  gFileScore.close();
}

void writeShortScores() {
  // scoretype.initScoreType();
  string s = pathShortScores + "shortScores.text";
  gFileShortScores.open(s.c_str(), ios::app);
  gFileShortScores << getShortDate() << endl;
  for (int ix = 0; ix < k18; ++ix) {
    gFileShortScores << gsd[ix];
  }
  gFileShortScores << endl;
  gFileShortScores.flush();
  gFileShortScores.close();
}

void writeShotStats() {
  string s = pathShots + "aShots_" + getFileSuffix();
  gFileShots.open(s.c_str());
  // gFileShots << asctime(std::localtime(&gToday));
  gFileShots << getShortDate() << endl;

  gFileShots << "Hole\tClub\tDist\tLng      \tLat" << endl;
  int valid = 0;
  gFileShots << setprecision(kPrecision);
  for (int ix = 0; ix < k18; ++ix)
    if (gShotRA[ix].nmarks > 1) {
      valid = countValidDistances(ix);
      for (int jx = 0; jx < valid; ++jx) {
        gFileShots << ix + 1 << "\t";
        gFileShots << gShotRA[ix].shot[jx].club << "\t";
        gFileShots << gShotRA[ix].shot[jx].yards << "\t";
        gFileShots << gShotRA[ix].shot[jx].utm.lng << "\t";
        gFileShots << gShotRA[ix].shot[jx].utm.lat << endl;
      }
    }
  gFileShots << endl;
  gFileShots.flush();
  gFileShots.close();
}

void writeHoleTimes() {
  CGPStime tm;
  int sum = 0;
  int secdiff = 0;

  gTmpTimes << "Time per hole" << endl;
  for (int ix = 0; ix < k18; ++ix) {
    secdiff = tm.timeDifference(gHoleTimeRA[ix].endstr, gHoleTimeRA[ix].begstr);
    gTmpTimes << ix + 1 << "\t" << tm.sec2str(secdiff, "") << endl;
    sum += secdiff;
  }
  gTmpTimes << "Hole Time\t" << tm.sec2str(sum, "") << endl;
  secdiff = tm.timeDifference(gNowTimeStr, gStartRoundTimeStr);
  gTmpTimes << "Round Time\t" << tm.sec2str(secdiff, "") << endl;
  gTmpTimes << "Walking Time green to next tee\t"
            << tm.sec2str((secdiff - sum), "") << endl;
  gTmpTimes.flush();
  gTmpTimes.close();
}

void CExitBtn::Button_CB() {
  int result = fl_choice("Do you want to save before quitting?",
                         "Don't Save",  // 0
                         "Save",        // 1
                         "Cancel"       // 2
                         );
  // { // used to get RGB value of Fl_Color
  //   uchar r = 0;
  //   uchar g = 0;
  //   uchar b = 0;
  //   Fl::get_color(FL_DARK_BLUE, r, g, b);
  //   cout << "FL_DARK_BLUE " << (int)r << " " << (int)g << " " << (int)b <<
  //   endl;
  // }

  if (result == 0) {  // Close without saving
    gTmpShots << endl;
    gTmpScore << endl;
    gTmpGPS << endl;
    gTmpShots.close();
    gTmpScore.close();
    gTmpGPS.close();

    gHoleTimeRA[gCurrentHole - 1].endstr = gNowTimeStr;
    gTmpTimes << "CExitBtn::Button_CB: gHoleTimeRA[" << gCurrentHole - 1
              << "].endstr\t" << gHoleTimeRA[gCurrentHole - 1].endstr << endl;
    gTmpTimes.close();

    // if (myClubPopup != nullptr) myClubPopup->hide();
    if (myHolePopup != nullptr) myHolePopup->hide();
    if (gpsin != nullptr) pclose(gpsin);
    mainwin->hide();
  } else if (result == 1) {  // Save and close
    gTmpShots << endl;
    gTmpScore << endl;
    gTmpGPS << endl;
    gTmpShots.close();
    gTmpScore.close();
    gTmpGPS.close();
    gHoleTimeRA[gCurrentHole - 1].endstr = gNowTimeStr;
    gTmpTimes << "CExitBtn::Button_CB: gHoleTimeRA[" << gCurrentHole - 1
              << "].end\t" << gHoleTimeRA[gCurrentHole - 1].endstr << endl;
    writeHoleTimes();
    writeShortScores();

    writeGPS();
    writeScores();
    writeShotStats();

    gFileGPS.close();

    if (myHolePopup != nullptr) myHolePopup->hide();
    if (gpsin != nullptr) pclose(gpsin);
    mainwin->hide();
  } else if (result == 2) {  // Cancel / don't close
                             // don't do anything
  }
}

// Handle numeric keypad buttons pressed
void CExitBtn::staticButton_CB(Fl_Widget *, void *data) {
  CExitBtn *ceb = (CExitBtn *)data;
  ceb->Button_CB();
}

CExitBtn::CExitBtn(int X, int Y, int W, int H, const char *L)
    : Fl_Button(X, Y, W, H, L) {
  callback(staticButton_CB, (void *)this);
}
