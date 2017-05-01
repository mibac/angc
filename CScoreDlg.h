// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef CSCOREDLG_H
#define CSCOREDLG_H

#include <ctime>
#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Window.H>

#ifndef CSCORESTATS_H
#include "CScoreStats.h"
#endif

class CScoreDlg {
 public:
  CScoreDlg();
  CScoreDlg(int hole);
  Fl_Window *sd;
  Fl_Counter *holeCounter;
  Fl_Counter *upDownCounter;
  Fl_Counter *puttCounter;
  Fl_Counter *scoreCounter;

 private:
  inline void cb_total_i(Fl_Button *, void *);
  static void cb_total(Fl_Button *, void *);

  inline void cb_OK_i(Fl_Button *, void *);
  static void cb_OK(Fl_Button *, void *);

  CScores getCurrentScores();
};

extern void createScoreDlg();

extern CScoreDlg *scoreDlg;
#endif  // CSCOREDLG_H
