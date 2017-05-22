#ifndef CEXITBTN_H
#include "CExitBtn.h"
#endif

#include <iomanip>

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

// #ifndef CCLUBBTN_H
// #include "CClubBtn.h"
// #endif

using namespace std;

void CExitBtn::writeGPS() {
  string s = path + "aGPS_" + getFileSuffix();
  gFileGPS.open(s.c_str());
  gFileGPS << setprecision(kPrecision);
  gFileGPS << asctime(std::localtime(&gToday));
  for (auto itr : vGPS) gFileGPS << itr;
  gFileGPS.close();
}

void CExitBtn::writeScoreStats() {
  string s = path + "aScore_" + getFileSuffix();
  gFileScoreStats.open(s.c_str());
  gFileScoreStats << asctime(std::localtime(&gToday));
  for (auto itr : vNGCHoles) gFileScoreStats << itr;
  gFileScoreStats.close();
}

void CExitBtn::Button_CB() {
  int result = fl_choice("Do you want to save before quitting?",
                         "Don't Save",  // 0
                         "Save",        // 1
                         "Cancel"       // 2
                         );
  if (result == 0) {  // Close without saving
    gFileShotStats.close();
    gFileScoreStats.close();
    gFileGPS.close();
    // if (myClubPopup != nullptr) myClubPopup->hide();
    if (myHolePopup != nullptr) myHolePopup->hide();
    if (gpsin != nullptr) pclose(gpsin);
    mainwin->hide();
  } else if (result == 1) {  // Save and close
    writeGPS();
    writeScoreStats();
    gFileScoreStats.close();
    // if (myClubPopup != nullptr) myClubPopup->hide();
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
