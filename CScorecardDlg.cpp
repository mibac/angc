// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef CSCORECARDDLG_H
#include "CScorecardDlg.h"
#endif

#ifndef CSCORECARD_H
#include "CScorecard.h"
#endif

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef CFRONTBACKBTN_H
#include "CFrontBackBtn.h"
#endif

#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

CScorecardDlg *scorecardDlg = nullptr;
Fl_Button *okB = nullptr;
CFrontBackBtn *fbBtn = nullptr;
CScorecard *card = nullptr;
Fl_Text_Display *stats = nullptr;
Fl_Text_Buffer *txtbuf = nullptr;

void okB_cb(Fl_Widget *w, void *data) { scorecardDlg->hide(); }

ScoreTypes st;

void incrScoreTypes(int par, int score) {
  int n = score - par;     // order important
  if (score == 0) n = 99;  // bad case
  string s;
  switch (ScorType(n)) {
    case ScorType::albatross:
      st.albatross++;
      break;
    case ScorType::eagle:
      st.eagles++;
      break;
    case ScorType::birdie:
      st.birdies++;
      break;
    case ScorType::par:
      st.pars++;
      break;
    case ScorType::bogey:
      st.bogies++;
      break;
    case ScorType::dbogey:
      st.doubles++;
      break;
    case ScorType::tbogey:
      st.triples++;
      break;
    case ScorType::x:
      st.x++;
      break;
    default:
      break;
  }
}

string statsStr;
string writeScoreStats() {
  int fscore = calcScore(true);
  int bscore = calcScore(false);
  int fputts = calcPutts(true);
  int bputts = calcPutts(false);
  int fuds = calcUDs(true);
  int buds = calcUDs(false);
  int fGIR = calcGIRs(true);
  int bGIR = calcGIRs(false);

  st.initScoreType();
  int score;
  for (int ix = 0; ix < k18; ++ix) {
    int par = stoi(aNGCHoles[ix].par);

    if (asd[ix].score == "")
        score = 0;
    else
      score = stoi(asd[ix].score);
    incrScoreTypes(par, score);
  }

  ostringstream oss;
  oss << "Score \t" << fscore << "\t" << bscore << "\t" << fscore + bscore
      << endl;
  oss << "Putts \t" << fputts << "\t" << bputts << "\t" << fputts + bputts
      << endl;
  oss << "Updown\t" << fuds << "\t" << buds << "\t" << fuds + buds << endl;
  oss << "GIR\t" << fGIR << "\t" << bGIR << "\t" << fGIR + bGIR << endl;

  if (st.eagles > 0) oss << "Eagles\t" << st.eagles << endl;
  if (st.birdies > 0) oss << "Birdies\t" << st.birdies << endl;
  if (st.pars > 0) oss << "Pars\t" << st.pars << endl;
  if (st.bogies > 0) oss << "Bogies\t" << st.bogies << endl;
  if (st.doubles > 0) oss << "Doubles\t" << st.doubles << endl;
  if (st.triples > 0) oss << "Triples\t" << st.triples << endl;
  if (st.x > 0) oss << "Xs\t" << st.x << endl;
  return oss.str();
}

CScorecardDlg::CScorecardDlg(int X, int Y, int W, int H, const char *L)
    : Fl_Window(X, Y, W, H, L) {
  { card = new CScorecard(2, 20, 472, 244); }
  {
    okB = new Fl_Button(174, kBtnWinBottomY, kBtnW, kBtnH, "OK");
    setButtonStyle(okB);
    okB->callback(okB_cb, this);
  }
  {
    fbBtn = new CFrontBackBtn(190, 300, 0, 0);
    setButtonStyle(fbBtn);
  }
  {
    stats = new Fl_Text_Display(2, 380, 472, 270);
    stats->textfont(1);
    stats->textsize(30);
    stats->textcolor(FL_BLACK);
    // stats->color(Fl_Color(159), Fl_Color(159));
    stats->box(FL_NO_BOX);
    txtbuf = new Fl_Text_Buffer();
    stats->buffer(txtbuf);
    stats->scrollbar_width(0);
    statsStr = writeScoreStats();
    txtbuf->text(statsStr.c_str());
    // boxHole->insert(s.c_str());
  }

  color((Fl_Color)159);
  label("NGC Scorecard");
  // set_modal();
  size_range(480, 800, 480, 800);
  end();
  // clear_border();
  show();
}

void createScorecardDlg() { scorecardDlg = new CScorecardDlg(0, 0, 480, 800); }
