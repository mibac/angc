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

using namespace std;

void CExitBtn::writeGPS() {
  string s = pathGPS + "aGPS_" + getFileSuffix();
  gFileGPS.open(s.c_str());
  gFileGPS << setprecision(kPrecision);
  gFileGPS << asctime(std::localtime(&gToday));
  for (auto itr : vGPS) gFileGPS << itr;
  gFileGPS.close();
}

void CExitBtn::writeScoreStats() {
  // initTestScore();
  writeScores();
}

void writeShotStats() {
  string s = pathShots + "aShots_" + getFileSuffix();
  gFileShotStats.open(s.c_str());
  gFileShotStats << asctime(std::localtime(&gToday));
  gFileShotStats << "Hole\tClub\tDist\tLng      \tLat" << endl;
  int valid = 0;
  gFileShotStats << setprecision(kPrecision);
  for (int ix = 0; ix < k18; ++ix)
    if (gShotRA[ix].nmarks > 1) {
      valid = countValidDistances(ix);
      for (int jx = 0; jx < valid; ++jx) {
        gFileShotStats << ix + 1 << "\t";
        gFileShotStats << gShotRA[ix].shot[jx].club << "\t";
        gFileShotStats << gShotRA[ix].shot[jx].yards << "\t";
        gFileShotStats << gShotRA[ix].shot[jx].utm.lng << "\t";
        gFileShotStats << gShotRA[ix].shot[jx].utm.lat << endl;
      }
    }
  gFileShotStats << endl;
  gFileShotStats.flush();
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
    gFileShotStats.close();
    gFileScore.close();
    gFileGPS.close();
    // if (myClubPopup != nullptr) myClubPopup->hide();
    if (myHolePopup != nullptr) myHolePopup->hide();
    if (gpsin != nullptr) pclose(gpsin);
    mainwin->hide();
  } else if (result == 1) {  // Save and close
    writeGPS();
    writeScoreStats();
    writeShotStats();
    gFileScore.close();
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
