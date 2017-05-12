// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef CSCOREDLG2_H
#include "CScoreDlg2.h"
#endif

#ifndef CGLOBALS_H
#include "globals.h"
#endif

Fl_Box *holeBox = nullptr;
Fl_Box *yardsBox = nullptr;
Fl_Box *hdcpBox = nullptr;
Fl_Box *parBox = nullptr;
Fl_Box *scoreBox = nullptr;
Fl_Box *puttBox = nullptr;
Fl_Box *udBox = nullptr;
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
Fl_Box *holeValue = nullptr;
Fl_Box *yardsValue = nullptr;
Fl_Box *hdcpValue = nullptr;
Fl_Box *parValue = nullptr;
Fl_Box *scoreValue = nullptr;
Fl_Box *puttValue = nullptr;
Fl_Box *udValue = nullptr;
Fl_Box *prevBtn = nullptr;
Fl_Box *nextBtn = nullptr;
Fl_Button *okBtn = nullptr;

Fl_Box *sel = scoreValue;

int hole;

vector<CHoleDescription> vHoleDesc;

void initHoleDescVector() {
  for (int ix = 0; ix < k19; ++ix) {
    CHoleDescription chd;
    vHoleDesc.push_back(chd);
  }
  vHoleDesc[0].setHoleDesc("", "", "", "");
  vHoleDesc[1].setHoleDesc("1", "492", "7", "5");
  vHoleDesc[2].setHoleDesc("2", "185", "13", "3");
  vHoleDesc[3].setHoleDesc("3", "421", "1", "4");
  vHoleDesc[4].setHoleDesc("4", "510", "3", "5");
  vHoleDesc[5].setHoleDesc("5", "395", "5", "4");
  vHoleDesc[6].setHoleDesc("6", "383", "11", "4");
  vHoleDesc[7].setHoleDesc("7", "135", "17", "3");
  vHoleDesc[8].setHoleDesc("8", "368", "9", "4");
  vHoleDesc[9].setHoleDesc("9", "312", "5", "4");
  vHoleDesc[10].setHoleDesc("10", "342", "8", "4");
  vHoleDesc[11].setHoleDesc("11", "145", "16", "3");
  vHoleDesc[12].setHoleDesc("12", "471", "12", "5");
  vHoleDesc[13].setHoleDesc("13", "380", "6", "4");
  vHoleDesc[14].setHoleDesc("14", "365", "4", "4");
  vHoleDesc[15].setHoleDesc("15", "331", "18", "4");
  vHoleDesc[16].setHoleDesc("16", "521", "2", "5");
  vHoleDesc[17].setHoleDesc("17", "168", "14", "3");
  vHoleDesc[18].setHoleDesc("18", "337", "10", "4");
}

void btnOK_cb(Fl_Widget *w, void *data) {
  Fl_Window *parent = (Fl_Window *)data;
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
  box->color(FL_YELLOW);
}

void toggleSelection(Fl_Box *box) {
  if (box == scoreBox || box == scoreValue) {
    scoreValue->color(FL_YELLOW);
    puttValue->color(FL_WHITE);
    udValue->color(FL_WHITE);
  } else if (box == puttBox || box == puttValue) {
    scoreValue->color(FL_WHITE);
    puttValue->color(FL_YELLOW);
    udValue->color(FL_WHITE);
  } else if (box == udBox || box == udValue) {
    scoreValue->color(FL_WHITE);
    puttValue->color(FL_WHITE);
    udValue->color(FL_YELLOW);
  }
  sel = box;
}

void CScoreDlg2::updateHoleDescription(int n) {
  holeValue->label(vHoleDesc[n].hole.c_str());
  yardsValue->label(vHoleDesc[n].yards.c_str());
  hdcpValue->label(vHoleDesc[n].hdcp.c_str());
  parValue->label(vHoleDesc[n].par.c_str());
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
          toggleSelection(scoreValue);
        } else if (w == puttBox || w == puttValue) {
          toggleSelection(puttValue);
        } else if (w == udBox || w == udValue) {
          toggleSelection(udValue);
        } else if (w == box0) {
          toggleNumbers(box0);
          sel->label("0");
        } else if (w == box1) {
          toggleNumbers(box1);
          sel->label("1");
        } else if (w == box2) {
          toggleNumbers(box2);
          sel->label("2");
        } else if (w == box3) {
          toggleNumbers(box3);
          sel->label("3");
        } else if (w == box4) {
          toggleNumbers(box4);
          sel->label("4");
        } else if (w == box5) {
          toggleNumbers(box5);
          sel->label("5");
        } else if (w == box6) {
          toggleNumbers(box6);
          sel->label("6");
        } else if (w == box7) {
          toggleNumbers(box7);
          sel->label("7");
        } else if (w == box8) {
          toggleNumbers(box8);
          sel->label("8");
        } else if (w == box9) {
          toggleNumbers(box9);
          sel->label("9");
        } else if (w == prevBtn) {
          hole -= 1;
          if (hole == 0) hole = 1;
          updateHoleDescription(hole);
        } else if (w == nextBtn) {
          hole += 1;
          if (hole == 19) hole = 18;
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
  {
    holeBox = new Fl_Box(60, 101, 90, 56, "Hole");
    holeBox->box(FL_BORDER_BOX);
    holeBox->color(FL_BACKGROUND2_COLOR);
    holeBox->selection_color(FL_BACKGROUND_COLOR);
    holeBox->labeltype(FL_NORMAL_LABEL);
    holeBox->labelfont(0);
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
    yardsBox->labelfont(0);
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
    hdcpBox->labelfont(0);
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
    parBox->labelfont(0);
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
    scoreBox->labelfont(0);
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
    puttBox->labelfont(0);
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
    udBox->labelfont(0);
    udBox->labelsize(28);
    udBox->labelcolor(FL_FOREGROUND_COLOR);
    udBox->align(Fl_Align(FL_ALIGN_CENTER));
    udBox->when(FL_WHEN_RELEASE);
  }  // Fl_Box* udBox
  {
    box0 = new Fl_Box(12, 410, 84, 100, "0");
    box0->box(FL_BORDER_BOX);
    box0->color(FL_BACKGROUND2_COLOR);
    box0->selection_color(FL_BACKGROUND_COLOR);
    box0->labeltype(FL_NORMAL_LABEL);
    box0->labelfont(0);
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
    box1->labelfont(0);
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
    box2->labelfont(0);
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
    box3->labelfont(0);
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
    box4->labelfont(0);
    box4->labelsize(60);
    box4->labelcolor(FL_FOREGROUND_COLOR);
    box4->align(Fl_Align(FL_ALIGN_CENTER));
    box4->when(FL_WHEN_RELEASE);
  }  // Fl_Box* box4
  {
    box5 = new Fl_Box(12, 545, 84, 100, "5");
    box5->box(FL_BORDER_BOX);
    box5->color(FL_BACKGROUND2_COLOR);
    box5->selection_color(FL_BACKGROUND_COLOR);
    box5->labeltype(FL_NORMAL_LABEL);
    box5->labelfont(0);
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
    box6->labelfont(0);
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
    box7->labelfont(0);
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
    box8->labelfont(0);
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
    box9->labelfont(0);
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
  {
    Fl_Box *o = new Fl_Box(195, 25, 90, 65, "Hole");
    o->labelsize(32);
  }  // Fl_Box* o
  {
    okBtn = new Fl_Button(174, 675, 140, 42, "OK");
    okBtn->color(FL_BACKGROUND2_COLOR);
    okBtn->labelsize(32);
    okBtn->callback(btnOK_cb, this);
  }  // Fl_Button* bntOK
  color((Fl_Color)159);
  set_modal();
  size_range(480, 800, 480, 800);
  end();
  initHoleDescVector();
  toggleSelection(scoreValue);
  hole = gCurrentHole;
  if (hole == 0) hole = 1;
  updateHoleDescription(hole);
  show();
}

void createScoreDlg2() { scoreDlg2 = new CScoreDlg2(0, 0, 480, 800); }
