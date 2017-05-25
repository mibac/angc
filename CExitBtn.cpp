#ifndef CEXITBTN_H
#include "CExitBtn.h"
#endif

#include <iomanip>

#include <FL/Fl.H>
#include <FL/Enumerations.H>
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

void initTestScore() {
    vNGCHoles[0].setHoleDesc("1", "492", "7", "5", "7", "3", "4");
    vNGCHoles[1].setHoleDesc("2", "185", "13", "3", "4", "2", "3");
    vNGCHoles[2].setHoleDesc("3", "421", "1", "4", "6", "2", "3");
    vNGCHoles[3].setHoleDesc("4", "510", "3", "5", "5", "2", "2");
    vNGCHoles[4].setHoleDesc("5", "395", "5", "4", "5", "2", "3");
    vNGCHoles[5].setHoleDesc("6", "383", "11", "4", "4", "2", "2");
    vNGCHoles[6].setHoleDesc("7", "135", "17", "3", "3", "1", "2");
    vNGCHoles[7].setHoleDesc("8", "368", "9", "4", "6", "3", "3");
    vNGCHoles[8].setHoleDesc("9", "312", "5", "4", "3", "1", "1");
    vNGCHoles[9].setHoleDesc("10", "342", "8", "4", "5", "2", "3");
    vNGCHoles[10].setHoleDesc("11", "145", "16", "3", "3", "2", "2");
    vNGCHoles[11].setHoleDesc("12", "471", "12", "5", "5", "2", "2");
    vNGCHoles[12].setHoleDesc("13", "380", "6", "4", "5", "2", "3");
    vNGCHoles[13].setHoleDesc("14", "365", "4", "4", "5", "2", "3");
    vNGCHoles[14].setHoleDesc("15", "331", "18", "4", "3", "1", "1");
    vNGCHoles[15].setHoleDesc("16", "521", "2", "5", "7", "2", "3");
    vNGCHoles[16].setHoleDesc("17", "168", "14", "3", "4", "2", "3");
    vNGCHoles[17].setHoleDesc("18", "337", "10", "4", "4", "2", "2");
}

void CExitBtn::writeScoreStats() {
    initTestScore();
    writeScores();
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
  //   cout << "FL_DARK_BLUE " << (int)r << " " << (int)g << " " << (int)b << endl;
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
