// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef CSCOREDLG_H
#include "CScoreDlg.h"
#endif

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef CSCORESTATS_H
#include "CScoreStats.h"
#endif

#include <iostream>

Fl_Counter* holeCounter;
Fl_Counter* upDownCounter;
Fl_Counter* puttCounter;
Fl_Counter* scoreCounter;

void CScoreDlg::cb_total_i(Fl_Button* b, void*) {
  // int h = holeCounter->value();
  // int u = upDownCounter->value();
  // int p = puttCounter->value();
  // int s = scoreCounter->value();
  // CScores cs(h, u, p, s);
  // cStats.statsRA[h] = cs;
  // b->parent()->hide();
  //
  // gFileStats << cStats.statsRA[h];
  int uds = 0;
  int putts = 0;
  int score = 0;
  for (auto itr : cStats.statsRA) {
    uds += itr.getUpdown();
    putts += itr.getPutts();
    score += itr.getScore();
  }

  b->parent()->hide();

  cout << "Score: " << score << endl;
  cout << "Putts: " << putts << endl;
  cout << "Up Downs: " << uds << endl;
}

void CScoreDlg::cb_total(Fl_Button* o, void* v) {
  ((CScoreDlg*)(o->parent()->user_data()))->cb_total_i(o, v);
}

void CScoreDlg::cb_OK_i(Fl_Button* b, void*) {
  int h = holeCounter->value();
  int u = upDownCounter->value();
  int p = puttCounter->value();
  int s = scoreCounter->value();
  CScores cs(h, u, p, s);
  cStats.statsRA[h] = cs;
  b->parent()->hide();

  gFileStats << cStats.statsRA[h];
}

void CScoreDlg::cb_OK(Fl_Button* o, void* v) {
  ((CScoreDlg*)(o->parent()->user_data()))->cb_OK_i(o, v);
}

CScoreDlg::CScoreDlg() {
  {
    const int kWindowW = 390;
    const int kCounterH = 60;
    const int kCounterW = 200;
    const int kCounterL = kWindowW / 2 - kCounterW / 2;
    const int kLabelSz = 36;
    const int kTextSz = 48;
    const int kDeltaY = 140;
    const int kHoleY = 10;
    const int kUpDownY = kHoleY + kDeltaY;
    const int kPuttY = kUpDownY + kDeltaY;
    const int kScoreY = kPuttY + kDeltaY;
    const int kOKBtnY = kScoreY + kDeltaY;

    sd = new Fl_Window(10, 0, kWindowW, 640);
    sd->color((Fl_Color)55);
    sd->labelfont(1);
    sd->labelsize(30);
    sd->user_data((void*)(this));
    {
      holeCounter =
          new Fl_Counter(kCounterL, kHoleY, kCounterW, kCounterH, "Hole");
      holeCounter->box(FL_UP_BOX);
      holeCounter->color(FL_BACKGROUND_COLOR);
      holeCounter->selection_color(FL_INACTIVE_COLOR);
      holeCounter->labeltype(FL_NORMAL_LABEL);
      holeCounter->labelfont(1);
      holeCounter->labelsize(kLabelSz);
      holeCounter->labelcolor(FL_FOREGROUND_COLOR);
      holeCounter->textsize(kTextSz);
      holeCounter->align(Fl_Align(FL_ALIGN_BOTTOM));
      holeCounter->when(FL_WHEN_CHANGED);
      holeCounter->minimum(1);
      holeCounter->maximum(18);
      holeCounter->value(int(gCurrentHole));
      holeCounter->step(int(1));
      holeCounter->type(1);
    }  // Fl_Counter* holeCounter
    {
      upDownCounter =
          new Fl_Counter(kCounterL, kUpDownY, kCounterW, kCounterH, "Up Down");
      upDownCounter->box(FL_UP_BOX);
      upDownCounter->color(FL_BACKGROUND_COLOR);
      upDownCounter->selection_color(FL_INACTIVE_COLOR);
      upDownCounter->labeltype(FL_NORMAL_LABEL);
      upDownCounter->labelfont(1);
      upDownCounter->labelsize(kLabelSz);
      upDownCounter->labelcolor(FL_FOREGROUND_COLOR);
      upDownCounter->textsize(kTextSz);
      upDownCounter->align(Fl_Align(FL_ALIGN_BOTTOM));
      upDownCounter->when(FL_WHEN_CHANGED);
      upDownCounter->minimum(1);
      upDownCounter->maximum(4);
      upDownCounter->value(int(2));
      upDownCounter->step(int(1));
      upDownCounter->type(1);
    }  // Fl_Counter* updownCounter
    {
      puttCounter =
          new Fl_Counter(kCounterL, kPuttY, kCounterW, kCounterH, "Putts   ");
      puttCounter->box(FL_UP_BOX);
      puttCounter->color(FL_BACKGROUND_COLOR);
      puttCounter->selection_color(FL_INACTIVE_COLOR);
      puttCounter->labeltype(FL_NORMAL_LABEL);
      puttCounter->labelfont(1);
      puttCounter->labelsize(kLabelSz);
      puttCounter->labelcolor(FL_FOREGROUND_COLOR);
      puttCounter->textsize(kTextSz);
      puttCounter->align(Fl_Align(FL_ALIGN_BOTTOM));
      puttCounter->when(FL_WHEN_CHANGED);
      puttCounter->minimum(0);
      puttCounter->maximum(4);
      puttCounter->value(int(2));
      puttCounter->step(int(1));
      puttCounter->type(1);
    }  // puttCounter
    {
      scoreCounter =
          new Fl_Counter(kCounterL, kScoreY, kCounterW, kCounterH, "Score   ");
      scoreCounter->box(FL_UP_BOX);
      scoreCounter->color(FL_BACKGROUND_COLOR);
      scoreCounter->selection_color(FL_INACTIVE_COLOR);
      scoreCounter->labeltype(FL_NORMAL_LABEL);
      scoreCounter->labelfont(1);
      scoreCounter->labelsize(kLabelSz);
      scoreCounter->labelcolor(FL_FOREGROUND_COLOR);
      scoreCounter->textsize(kTextSz);
      scoreCounter->align(Fl_Align(FL_ALIGN_BOTTOM));
      scoreCounter->when(FL_WHEN_CHANGED);
      scoreCounter->minimum(1);
      scoreCounter->maximum(8);
      scoreCounter->value(int(4));
      scoreCounter->step(int(1));
      scoreCounter->type(1);
    }  // scoreCounter
    {
      Fl_Button* totalsBtn =
          new Fl_Button(20, kOKBtnY, kCounterW - 50, kCounterH, "Total");
      totalsBtn->box(FL_UP_BOX);
      totalsBtn->color(FL_BACKGROUND_COLOR);
      totalsBtn->selection_color(FL_BACKGROUND_COLOR);
      totalsBtn->labeltype(FL_NORMAL_LABEL);
      totalsBtn->labelfont(1);
      totalsBtn->labelsize(kLabelSz);
      totalsBtn->labelcolor(FL_FOREGROUND_COLOR);
      totalsBtn->callback((Fl_Callback*)cb_total);
      totalsBtn->align(Fl_Align(FL_ALIGN_CENTER));
      totalsBtn->when(FL_WHEN_RELEASE);
    }  // Fl_Button* o
    {
      Fl_Button* okBtn =
          new Fl_Button(220, kOKBtnY, kCounterW - 50, kCounterH, "OK");
      okBtn->box(FL_UP_BOX);
      okBtn->color(FL_BACKGROUND_COLOR);
      okBtn->selection_color(FL_BACKGROUND_COLOR);
      okBtn->labeltype(FL_NORMAL_LABEL);
      okBtn->labelfont(1);
      okBtn->labelsize(kLabelSz);
      okBtn->labelcolor(FL_FOREGROUND_COLOR);
      okBtn->callback((Fl_Callback*)cb_OK);
      okBtn->align(Fl_Align(FL_ALIGN_CENTER));
      okBtn->when(FL_WHEN_RELEASE);
    }  // Fl_Button* o
    sd->set_modal();
    sd->clear_border();
    sd->end();
    sd->show();
  }  // Fl_Double_Window* scoredlg
}

void createScoreDlg() { scoreDlg = new CScoreDlg(); }
