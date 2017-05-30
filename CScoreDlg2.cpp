// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef CSCOREDLG2_H
#include "CScoreDlg2.h"
#endif

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef CSCORECARDDLG_H
#include "CScorecardDlg.h"
#endif

#ifndef CCLUBDLG_H
#include "CClubDlg.h"
#endif

#include <iostream>
#include <string>

using namespace std;

Fl_Box *holeBox = nullptr;
Fl_Box *holeValue = nullptr;
Fl_Box *yardsBox = nullptr;
Fl_Box *yardsValue = nullptr;
Fl_Box *hdcpBox = nullptr;
Fl_Box *hdcpValue = nullptr;
Fl_Box *parBox = nullptr;
Fl_Box *parValue = nullptr;
Fl_Box *scoreBox = nullptr;
Fl_Box *scoreValue = nullptr;
Fl_Box *puttBox = nullptr;
Fl_Box *puttValue = nullptr;
Fl_Box *udBox = nullptr;
Fl_Box *udValue = nullptr;
Fl_Box *box0 = nullptr;
Fl_Box *box1 = nullptr;
Fl_Box *box2 = nullptr;
Fl_Box *box3 = nullptr;
Fl_Box *box4 = nullptr;
Fl_Box *box5 = nullptr;
Fl_Box *box6 = nullptr;
Fl_Box *box7 = nullptr;
Fl_Box *box8 = nullptr;
Fl_Box *box9 = nullptr;
Fl_Box *prevBtn = nullptr;
Fl_Box *nextBtn = nullptr;
Fl_Button *okBtn = nullptr;
Fl_Button *cardBtn = nullptr;

Fl_Box *sel = scoreValue;

CClubDlg *clubDlg = nullptr;
Fl_Button *clubB = nullptr;
CScoreDlg2 *scoreDlg2 = nullptr;

int hole;

void btnOK_cb(Fl_Widget *w, void *data) {
  CScoreDlg2 *parent = (CScoreDlg2 *)data;
  parent->stuffData(hole);
  parent->hide();
}

void cardBtn_cb(Fl_Widget *w, void *data) {
  CScoreDlg2 *parent = (CScoreDlg2 *)data;
  parent->stuffData(hole);
  createScorecardDlg();
  parent->hide();
}

void clubB_cb(Fl_Widget *w, void *data) {
  CScoreDlg2 *parent = (CScoreDlg2 *)data;
  // parent->stuffData(hole);
  createCClubDlg();
  parent->hide();
}

void toggleNumbers(Fl_Box *box) {
  box0->color(FL_WHITE);
  box1->color(FL_WHITE);
  box2->color(FL_WHITE);
  box3->color(FL_WHITE);
  box4->color(FL_WHITE);
  box5->color(FL_WHITE);
  box6->color(FL_WHITE);
  box7->color(FL_WHITE);
  box8->color(FL_WHITE);
  box9->color(FL_WHITE);

  box0->labelcolor(FL_BLACK);
  box1->labelcolor(FL_BLACK);
  box2->labelcolor(FL_BLACK);
  box3->labelcolor(FL_BLACK);
  box4->labelcolor(FL_BLACK);
  box5->labelcolor(FL_BLACK);
  box6->labelcolor(FL_BLACK);
  box7->labelcolor(FL_BLACK);
  box8->labelcolor(FL_BLACK);
  box9->labelcolor(FL_BLACK);

  box->color(FL_DARK_BLUE);
  box->labelcolor(FL_WHITE);
}

void toggleSelection(Fl_Box *box) {
  if (box == scoreBox || box == scoreValue) {
    scoreBox->color(FL_DARK_BLUE);
    scoreBox->labelcolor(FL_WHITE);
    puttBox->color(FL_WHITE);
    puttBox->labelcolor(FL_BLACK);
    udBox->color(FL_WHITE);
    udBox->labelcolor(FL_BLACK);
    sel = scoreValue;
  } else if (box == puttBox || box == puttValue) {
    puttBox->color(FL_DARK_BLUE);
    puttBox->labelcolor(FL_WHITE);
    scoreBox->color(FL_WHITE);
    scoreBox->labelcolor(FL_BLACK);
    udBox->color(FL_WHITE);
    udBox->labelcolor(FL_BLACK);
    sel = puttValue;
  } else if (box == udBox || box == udValue) {
    udBox->color(FL_DARK_BLUE);
    udBox->labelcolor(FL_WHITE);
    scoreBox->color(FL_WHITE);
    scoreBox->labelcolor(FL_BLACK);
    puttBox->color(FL_WHITE);
    puttBox->labelcolor(FL_BLACK);
    sel = udValue;
  }
}

void incrementSelection() {
  Fl_Box *hdr;
  if (sel == scoreValue) {
    sel = puttValue;
    hdr = puttBox;
  } else if (sel == puttValue) {
    sel = udValue;
    hdr = udBox;
  } else if (sel == udValue) {
    sel = scoreValue;
    hdr = scoreBox;
  }

  scoreBox->color(FL_WHITE);
  puttBox->color(FL_WHITE);
  udBox->color(FL_WHITE);
  scoreBox->labelcolor(FL_BLACK);
  puttBox->labelcolor(FL_BLACK);
  udBox->labelcolor(FL_BLACK);
  hdr->color(FL_DARK_BLUE);
  hdr->labelcolor(FL_WHITE);
}

void CScoreDlg2::stuffData(int n) {
  vNGCHoles[n].hole = holeValue->label();
  vNGCHoles[n].yards = yardsValue->label();
  vNGCHoles[n].hdcp = hdcpValue->label();
  vNGCHoles[n].par = parValue->label();
  vNGCHoles[n].score = scoreValue->label();
  vNGCHoles[n].putts = puttValue->label();
  vNGCHoles[n].uds = udValue->label();
}

void CScoreDlg2::updateHoleDescription(int n) {
  holeValue->label(vNGCHoles[n].hole.c_str());
  yardsValue->label(vNGCHoles[n].yards.c_str());
  hdcpValue->label(vNGCHoles[n].hdcp.c_str());
  parValue->label(vNGCHoles[n].par.c_str());
  scoreValue->label(vNGCHoles[n].score.c_str());
  puttValue->label(vNGCHoles[n].putts.c_str());
  udValue->label(vNGCHoles[n].uds.c_str());
}

// Handle when user right clicks on our input widget
int CScoreDlg2::handle(int e) {
  int ret = 0;
  switch (e) {
    // Mouse click on input field? Open myHolePopup dialog..
    case FL_PUSH:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        ret = 1;
      }
      break;
    case FL_RELEASE:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        Fl_Widget *w = Fl::belowmouse();
        if (w == scoreBox || w == scoreValue) {
          toggleSelection(scoreBox);
        } else if (w == puttBox || w == puttValue) {
          toggleSelection(puttBox);
        } else if (w == udBox || w == udValue) {
          toggleSelection(udBox);
        } else if (w == box0) {
          toggleNumbers(box0);
          sel->label("0");
          incrementSelection();
        } else if (w == box1) {
          toggleNumbers(box1);
          sel->label("1");
          incrementSelection();
        } else if (w == box2) {
          toggleNumbers(box2);
          sel->label("2");
          incrementSelection();
        } else if (w == box3) {
          toggleNumbers(box3);
          sel->label("3");
          incrementSelection();
        } else if (w == box4) {
          toggleNumbers(box4);
          sel->label("4");
          incrementSelection();
        } else if (w == box5) {
          toggleNumbers(box5);
          sel->label("5");
          incrementSelection();
        } else if (w == box6) {
          toggleNumbers(box6);
          sel->label("6");
          incrementSelection();
        } else if (w == box7) {
          toggleNumbers(box7);
          sel->label("7");
          incrementSelection();
        } else if (w == box8) {
          toggleNumbers(box8);
          sel->label("8");
          incrementSelection();
        } else if (w == box9) {
          toggleNumbers(box9);
          sel->label("9");
          incrementSelection();
        } else if (w == prevBtn) {
          stuffData(hole);
          hole -= 1;
          if (hole < 0) hole = 0;
          updateHoleDescription(hole);
        } else if (w == nextBtn) {
          stuffData(hole);
          hole += 1;
          if (hole == 18) hole = 17;
          updateHoleDescription(hole);
        }
        redraw();
        ret = 1;
      }
      break;
  }
  return (Fl_Window::handle(e) ? 1 : ret);
}

CScoreDlg2::CScoreDlg2(int X, int Y, int W, int H, const char *L)
    : Fl_Window(X, Y, W, H, L) {
  const int kLeftX = 12;
  {
    holeBox = new Fl_Box(60, 101, 90, 56, "Hole");
    holeBox->box(FL_BORDER_BOX);
    holeBox->color(FL_BACKGROUND2_COLOR);
    holeBox->selection_color(FL_BACKGROUND_COLOR);
    holeBox->labeltype(FL_NORMAL_LABEL);
    holeBox->labelfont(1);
    holeBox->labelsize(28);
    holeBox->labelcolor(FL_FOREGROUND_COLOR);
    holeBox->align(Fl_Align(FL_ALIGN_CENTER));
    holeBox->when(FL_WHEN_RELEASE);
  }  // Fl_Box* holeBox
  {
    yardsBox = new Fl_Box(149, 101, 90, 56, "Yards");
    yardsBox->box(FL_BORDER_BOX);
    yardsBox->color(FL_BACKGROUND2_COLOR);
    yardsBox->selection_color(FL_BACKGROUND_COLOR);
    yardsBox->labeltype(FL_NORMAL_LABEL);
    yardsBox->labelfont(1);
    yardsBox->labelsize(28);
    yardsBox->labelcolor(FL_FOREGROUND_COLOR);
    yardsBox->align(Fl_Align(FL_ALIGN_CENTER));
    yardsBox->when(FL_WHEN_RELEASE);
  }  // Fl_Box* yardsBox
  {
    hdcpBox = new Fl_Box(238, 101, 90, 56, "Hdcp");
    hdcpBox->box(FL_BORDER_BOX);
    hdcpBox->color(FL_BACKGROUND2_COLOR);
    hdcpBox->selection_color(FL_BACKGROUND_COLOR);
    hdcpBox->labeltype(FL_NORMAL_LABEL);
    hdcpBox->labelfont(1);
    hdcpBox->labelsize(28);
    hdcpBox->labelcolor(FL_FOREGROUND_COLOR);
    hdcpBox->align(Fl_Align(FL_ALIGN_CENTER));
    hdcpBox->when(FL_WHEN_RELEASE);
  }  // Fl_Box* hdcpBox
  {
    parBox = new Fl_Box(327, 101, 90, 56, "Par");
    parBox->box(FL_BORDER_BOX);
    parBox->color(FL_BACKGROUND2_COLOR);
    parBox->selection_color(FL_BACKGROUND_COLOR);
    parBox->labeltype(FL_NORMAL_LABEL);
    parBox->labelfont(1);
    parBox->labelsize(28);
    parBox->labelcolor(FL_FOREGROUND_COLOR);
    parBox->align(Fl_Align(FL_ALIGN_CENTER));
    parBox->when(FL_WHEN_RELEASE);
  }  // Fl_Box* parBox
  {
    scoreBox = new Fl_Box(105, 240, 90, 56, "Score");
    scoreBox->box(FL_BORDER_BOX);
    scoreBox->color(FL_BACKGROUND2_COLOR);
    scoreBox->selection_color(FL_BACKGROUND_COLOR);
    scoreBox->labeltype(FL_NORMAL_LABEL);
    scoreBox->labelfont(1);
    scoreBox->labelsize(28);
    scoreBox->labelcolor(FL_FOREGROUND_COLOR);
    scoreBox->align(Fl_Align(FL_ALIGN_CENTER));
    scoreBox->when(FL_WHEN_RELEASE);
  }  // Fl_Box* scoreBox
  {
    puttBox = new Fl_Box(194, 240, 90, 56, "Putt");
    puttBox->box(FL_BORDER_BOX);
    puttBox->color(FL_BACKGROUND2_COLOR);
    puttBox->selection_color(FL_BACKGROUND_COLOR);
    puttBox->labeltype(FL_NORMAL_LABEL);
    puttBox->labelfont(1);
    puttBox->labelsize(28);
    puttBox->labelcolor(FL_FOREGROUND_COLOR);
    puttBox->align(Fl_Align(FL_ALIGN_CENTER));
    puttBox->when(FL_WHEN_RELEASE);
  }  // Fl_Box* puttBox
  {
    udBox = new Fl_Box(283, 240, 90, 56, "UD");
    udBox->box(FL_BORDER_BOX);
    udBox->color(FL_BACKGROUND2_COLOR);
    udBox->selection_color(FL_BACKGROUND_COLOR);
    udBox->labeltype(FL_NORMAL_LABEL);
    udBox->labelfont(1);
    udBox->labelsize(28);
    udBox->labelcolor(FL_FOREGROUND_COLOR);
    udBox->align(Fl_Align(FL_ALIGN_CENTER));
    udBox->when(FL_WHEN_RELEASE);
  }  // Fl_Box* udBox
  {
    box0 = new Fl_Box(kLeftX, 410, 84, 100, "0");
    box0->box(FL_BORDER_BOX);
    box0->color(FL_BACKGROUND2_COLOR);
    box0->selection_color(FL_BACKGROUND_COLOR);
    box0->labeltype(FL_NORMAL_LABEL);
    box0->labelfont(1);
    box0->labelsize(60);
    box0->labelcolor(FL_FOREGROUND_COLOR);
    box0->align(Fl_Align(FL_ALIGN_CENTER));
    box0->when(FL_WHEN_RELEASE);
  }  // Fl_Box* box0
  {
    box1 = new Fl_Box(105, 410, 84, 100, "1");
    box1->box(FL_BORDER_BOX);
    box1->color(FL_BACKGROUND2_COLOR);
    box1->selection_color(FL_BACKGROUND_COLOR);
    box1->labeltype(FL_NORMAL_LABEL);
    box1->labelfont(1);
    box1->labelsize(60);
    box1->labelcolor(FL_FOREGROUND_COLOR);
    box1->align(Fl_Align(FL_ALIGN_CENTER));
    box1->when(FL_WHEN_RELEASE);
  }  // Fl_Box* box1
  {
    box2 = new Fl_Box(198, 410, 84, 100, "2");
    box2->box(FL_BORDER_BOX);
    box2->color(FL_BACKGROUND2_COLOR);
    box2->selection_color(FL_BACKGROUND_COLOR);
    box2->labeltype(FL_NORMAL_LABEL);
    box2->labelfont(1);
    box2->labelsize(60);
    box2->labelcolor(FL_FOREGROUND_COLOR);
    box2->align(Fl_Align(FL_ALIGN_CENTER));
    box2->when(FL_WHEN_RELEASE);
  }  // Fl_Box* box2
  {
    box3 = new Fl_Box(291, 410, 84, 100, "3");
    box3->box(FL_BORDER_BOX);
    box3->color(FL_BACKGROUND2_COLOR);
    box3->selection_color(FL_BACKGROUND_COLOR);
    box3->labeltype(FL_NORMAL_LABEL);
    box3->labelfont(1);
    box3->labelsize(60);
    box3->labelcolor(FL_FOREGROUND_COLOR);
    box3->align(Fl_Align(FL_ALIGN_CENTER));
    box3->when(FL_WHEN_RELEASE);
  }  // Fl_Box* box3
  {
    box4 = new Fl_Box(384, 410, 84, 100, "4");
    box4->box(FL_BORDER_BOX);
    box4->color(FL_BACKGROUND2_COLOR);
    box4->selection_color(FL_BACKGROUND_COLOR);
    box4->labeltype(FL_NORMAL_LABEL);
    box4->labelfont(1);
    box4->labelsize(60);
    box4->labelcolor(FL_FOREGROUND_COLOR);
    box4->align(Fl_Align(FL_ALIGN_CENTER));
    box4->when(FL_WHEN_RELEASE);
  }  // Fl_Box* box4
  {
    box5 = new Fl_Box(kLeftX, 545, 84, 100, "5");
    box5->box(FL_BORDER_BOX);
    box5->color(FL_BACKGROUND2_COLOR);
    box5->selection_color(FL_BACKGROUND_COLOR);
    box5->labeltype(FL_NORMAL_LABEL);
    box5->labelfont(1);
    box5->labelsize(60);
    box5->labelcolor(FL_FOREGROUND_COLOR);
    box5->align(Fl_Align(FL_ALIGN_CENTER));
    box5->when(FL_WHEN_RELEASE);
  }  // Fl_Box* box5
  {
    box6 = new Fl_Box(105, 545, 84, 100, "6");
    box6->box(FL_BORDER_BOX);
    box6->color(FL_BACKGROUND2_COLOR);
    box6->selection_color(FL_BACKGROUND_COLOR);
    box6->labeltype(FL_NORMAL_LABEL);
    box6->labelfont(1);
    box6->labelsize(60);
    box6->labelcolor(FL_FOREGROUND_COLOR);
    box6->align(Fl_Align(FL_ALIGN_CENTER));
    box6->when(FL_WHEN_RELEASE);
  }  // Fl_Box* box6
  {
    box7 = new Fl_Box(198, 545, 84, 100, "7");
    box7->box(FL_BORDER_BOX);
    box7->color(FL_BACKGROUND2_COLOR);
    box7->selection_color(FL_BACKGROUND_COLOR);
    box7->labeltype(FL_NORMAL_LABEL);
    box7->labelfont(1);
    box7->labelsize(60);
    box7->labelcolor(FL_FOREGROUND_COLOR);
    box7->align(Fl_Align(FL_ALIGN_CENTER));
    box7->when(FL_WHEN_RELEASE);
  }  // Fl_Box* box7
  {
    box8 = new Fl_Box(291, 545, 84, 100, "8");
    box8->box(FL_BORDER_BOX);
    box8->color(FL_BACKGROUND2_COLOR);
    box8->selection_color(FL_BACKGROUND_COLOR);
    box8->labeltype(FL_NORMAL_LABEL);
    box8->labelfont(1);
    box8->labelsize(60);
    box8->labelcolor(FL_FOREGROUND_COLOR);
    box8->align(Fl_Align(FL_ALIGN_CENTER));
    box8->when(FL_WHEN_RELEASE);
  }  // Fl_Box* box8
  {
    box9 = new Fl_Box(384, 545, 84, 100, "9");
    box9->box(FL_BORDER_BOX);
    box9->color(FL_BACKGROUND2_COLOR);
    box9->selection_color(FL_BACKGROUND_COLOR);
    box9->labeltype(FL_NORMAL_LABEL);
    box9->labelfont(1);
    box9->labelsize(60);
    box9->labelcolor(FL_FOREGROUND_COLOR);
    box9->align(Fl_Align(FL_ALIGN_CENTER));
    box9->when(FL_WHEN_RELEASE);
  }  // Fl_Box* box9
  {
    holeValue = new Fl_Box(60, 156, 90, 56);
    holeValue->box(FL_BORDER_BOX);
    holeValue->color(FL_BACKGROUND2_COLOR);
    holeValue->selection_color(FL_BACKGROUND_COLOR);
    holeValue->labeltype(FL_NORMAL_LABEL);
    holeValue->labelfont(1);
    holeValue->labelsize(36);
    holeValue->labelcolor(FL_FOREGROUND_COLOR);
    holeValue->align(Fl_Align(FL_ALIGN_CENTER));
    holeValue->when(FL_WHEN_RELEASE);
  }  // Fl_Box* holeValue
  {
    yardsValue = new Fl_Box(149, 156, 90, 56);
    yardsValue->box(FL_BORDER_BOX);
    yardsValue->color(FL_BACKGROUND2_COLOR);
    yardsValue->selection_color(FL_BACKGROUND_COLOR);
    yardsValue->labeltype(FL_NORMAL_LABEL);
    yardsValue->labelfont(1);
    yardsValue->labelsize(36);
    yardsValue->labelcolor(FL_FOREGROUND_COLOR);
    yardsValue->align(Fl_Align(FL_ALIGN_CENTER));
    yardsValue->when(FL_WHEN_RELEASE);
  }  // Fl_Box* yardsValue
  {
    hdcpValue = new Fl_Box(238, 156, 90, 56);
    hdcpValue->box(FL_BORDER_BOX);
    hdcpValue->color(FL_BACKGROUND2_COLOR);
    hdcpValue->selection_color(FL_BACKGROUND_COLOR);
    hdcpValue->labeltype(FL_NORMAL_LABEL);
    hdcpValue->labelfont(1);
    hdcpValue->labelsize(36);
    hdcpValue->labelcolor(FL_FOREGROUND_COLOR);
    hdcpValue->align(Fl_Align(FL_ALIGN_CENTER));
    hdcpValue->when(FL_WHEN_RELEASE);
  }  // Fl_Box* hdcpValue
  {
    parValue = new Fl_Box(327, 156, 90, 56);
    parValue->box(FL_BORDER_BOX);
    parValue->color(FL_BACKGROUND2_COLOR);
    parValue->selection_color(FL_BACKGROUND_COLOR);
    parValue->labeltype(FL_NORMAL_LABEL);
    parValue->labelfont(1);
    parValue->labelsize(36);
    parValue->labelcolor(FL_FOREGROUND_COLOR);
    parValue->align(Fl_Align(FL_ALIGN_CENTER));
    parValue->when(FL_WHEN_RELEASE);
  }  // Fl_Box* parValue
  {
    scoreValue = new Fl_Box(105, 295, 90, 56);
    scoreValue->box(FL_BORDER_BOX);
    scoreValue->color(FL_BACKGROUND2_COLOR);
    scoreValue->selection_color(FL_BACKGROUND_COLOR);
    scoreValue->labeltype(FL_NORMAL_LABEL);
    scoreValue->labelfont(1);
    scoreValue->labelsize(36);
    scoreValue->labelcolor(FL_FOREGROUND_COLOR);
    scoreValue->align(Fl_Align(FL_ALIGN_CENTER));
    scoreValue->when(FL_WHEN_RELEASE);
  }  // Fl_Box* scoreValue
  {
    puttValue = new Fl_Box(194, 295, 90, 56);
    puttValue->box(FL_BORDER_BOX);
    puttValue->color(FL_BACKGROUND2_COLOR);
    puttValue->selection_color(FL_BACKGROUND_COLOR);
    puttValue->labeltype(FL_NORMAL_LABEL);
    puttValue->labelfont(1);
    puttValue->labelsize(36);
    puttValue->labelcolor(FL_FOREGROUND_COLOR);
    puttValue->align(Fl_Align(FL_ALIGN_CENTER));
    puttValue->when(FL_WHEN_RELEASE);
  }  // Fl_Box* puttValue
  {
    udValue = new Fl_Box(283, 295, 90, 56);
    udValue->box(FL_BORDER_BOX);
    udValue->color(FL_BACKGROUND2_COLOR);
    udValue->selection_color(FL_BACKGROUND_COLOR);
    udValue->labeltype(FL_NORMAL_LABEL);
    udValue->labelfont(1);
    udValue->labelsize(36);
    udValue->labelcolor(FL_FOREGROUND_COLOR);
    udValue->align(Fl_Align(FL_ALIGN_CENTER));
    udValue->when(FL_WHEN_RELEASE);
  }  // Fl_Box* udValue
  {
    prevBtn = new Fl_Box(60, 34, 90, 68, "Prev");
    prevBtn->labelfont(1);
    prevBtn->labelsize(28);
  }  // Fl_Box* o
  {
    nextBtn = new Fl_Box(327, 37, 90, 65, "Next");
    nextBtn->labelfont(1);
    nextBtn->labelsize(28);
  }  // Fl_Box* o

  const int kCardX = kLeftX;
  const int kdx = 17;
  const int kClubX = kCardX + kBtnW + kdx;
  const int kOkX = kClubX + kBtnW + kdx;
  {
    clubB = new Fl_Button(kClubX, kBtnWinBottomY, kBtnW, kBtnH, "Shots");
    setButtonStyle(clubB);
    clubB->callback(clubB_cb, this);
  }
  {
    cardBtn = new Fl_Button(kCardX, kBtnWinBottomY, kBtnW, kBtnH, "Card");
    setButtonStyle(cardBtn);
    cardBtn->callback(cardBtn_cb, this);
  }  // Fl_Button* bntOK
  {
    okBtn = new Fl_Button(kOkX, kBtnWinBottomY, kBtnW, kBtnH, "OK");
    setButtonStyle(okBtn);
    okBtn->callback(btnOK_cb, this);
  }  // Fl_Button* bntOK

  color((Fl_Color)159);
  // set_modal();
  label("Scores");
  size_range(480, 800, 480, 800);
  // clear_border();
  end();

  // initTestScores();
  toggleSelection(scoreValue);
  hole = gCurrentHole - 1;
  updateHoleDescription(hole);

  show();
}


void createScoreDlg2() { scoreDlg2 = new CScoreDlg2(0, 0, 480, 800); }
