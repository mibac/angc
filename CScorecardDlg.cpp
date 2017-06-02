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

Scores sc;

void incrScoreTypes(int par, int score) {
  int n = score - par;     // order important
  if (score == 0) n = 99;  // bad case
  string s;
  switch (ScoreType(n)) {
    case ScoreType::albatross:
      sc.albatross++;
      break;
    case ScoreType::eagle:
      sc.eagles++;
      break;
    case ScoreType::birdie:
      sc.birdies++;
      break;
    case ScoreType::par:
      sc.pars++;
      break;
    case ScoreType::bogey:
      sc.bogies++;
      break;
    case ScoreType::dbogey:
      sc.doubles++;
      break;
    case ScoreType::tbogey:
      sc.triples++;
      break;
    case ScoreType::x:
      sc.x++;
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

  sc.initScores();
  for (int ix = 0; ix < k18; ++ix) {
    int par = stoi(vNGCHoles[ix].par);
    int score = stoi(vNGCHoles[ix].score);
    incrScoreTypes(par, score);
  }

  ostringstream oss;
  oss << "Score \t" << fscore << "\t" << bscore << "\t" << fscore + bscore
      << endl;
  oss << "Putts \t" << fputts << "\t" << bputts << "\t" << fputts + bputts
      << endl;
  oss << "Updown\t" << fuds << "\t" << buds << "\t" << fuds + buds << endl;
  oss << "GIR\t" << fGIR << "\t" << bGIR << "\t" << fGIR + bGIR << endl;

  if (sc.eagles > 0) oss << "Eagles\t" << sc.eagles << endl;
  if (sc.birdies > 0) oss << "Birdies\t" << sc.birdies << endl;
  if (sc.pars > 0) oss << "Pars\t" << sc.pars << endl;
  if (sc.bogies > 0) oss << "Bogies\t" << sc.bogies << endl;
  if (sc.doubles > 0) oss << "Doubles\t" << sc.doubles << endl;
  if (sc.triples > 0) oss << "Triples\t" << sc.triples << endl;
  if (sc.x > 0) oss << "Xs\t" << sc.x << endl;
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
