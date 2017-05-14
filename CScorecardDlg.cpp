// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef CSCORECARDDLG_H
#include "CScorecardDlg.h"
#endif

#ifndef CSCORECARD_H
#include "CScorecard.h"
#endif

CScorecardDlg *scorecardDlg = nullptr;
Fl_Button *okB = nullptr;
Fl_Button *frontBtn = nullptr;
Fl_Button *backBtn = nullptr;
CScorecard *card = nullptr;

void okB_cb(Fl_Widget *w, void *data) {
  scorecardDlg->hide();
}

void frontBtn_cb(Fl_Widget *w, void *data) {
  front9 = true;
  scorecardDlg->redraw();
}

void backBtn_cb(Fl_Widget *w, void *data) {
  front9 = false;
  scorecardDlg->redraw();
}

CScorecardDlg::CScorecardDlg(int X, int Y, int W, int H, const char *L)
    : Fl_Window(X, Y, W, H, L) {
  {
    okB = new Fl_Button(174, 675, 140, 42, "OK");
    okB->color(FL_BACKGROUND2_COLOR);
    okB->labelsize(32);
    okB->callback(okB_cb, this);
  }  // Fl_Button* bntOK
  {
    card = new CScorecard(2, 20, 476, 260);
  }  // Fl_Table* o
  {
    frontBtn = new Fl_Button(150, 300, 100, 42, "Front 9");
    frontBtn->color((Fl_Color)159);
    frontBtn->labelsize(24);
    frontBtn->callback(frontBtn_cb, this);
  }  // Fl_Button* bntOK
  {
    backBtn = new Fl_Button(300, 300, 100, 42, "Back 9");
    backBtn->color((Fl_Color)159);
    backBtn->labelsize(24);
    backBtn->callback(backBtn_cb, this);
  }  // Fl_Button* bntOK

  color((Fl_Color)159);
  set_modal();
  size_range(480, 800, 480, 800);
  end();
  show();
}

void createScorecardDlg() { scorecardDlg = new CScorecardDlg(0, 0, 480, 800); }
