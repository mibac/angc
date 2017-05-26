// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef CCLUBDLG_H
#include "CClubDlg.h"
#endif

#ifndef CClubcard_H
#include "CClubcard.h"
#endif

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Text_Display.H>

#ifndef FL_IMAGE_BUTTON_H
#include "Fl_Image_Button.h"
#endif

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

CClubDlg *clubcardDlg;
Fl_Button *oKBtn;
Fl_Image_Button *btnPrev;
Fl_Image_Button *btnNext;
Fl_Text_Display *boxHole;
Fl_Text_Buffer *buff;
Fl_Image_Button *upBtn;
Fl_Image_Button *downBtn;
CClubcard *clubcard;

Fl_Button *btnDr = nullptr;
Fl_Button *btn3w = nullptr;
Fl_Button *btn5w = nullptr;
Fl_Button *btn7w = nullptr;
Fl_Button *btnHy = nullptr;
Fl_Button *btn2 = nullptr;
Fl_Button *btn3 = nullptr;
Fl_Button *btn4 = nullptr;
Fl_Button *btn5 = nullptr;
Fl_Button *btn6 = nullptr;
Fl_Button *btn7 = nullptr;
Fl_Button *btn8 = nullptr;
Fl_Button *btn9 = nullptr;
Fl_Button *btnPW = nullptr;
Fl_Button *btnGW = nullptr;
Fl_Button *btnSW = nullptr;
Fl_Button *btnLW = nullptr;
Fl_Button *btnX = nullptr;

int btnIndex = 0;
int btnPresses = 0;
int saveCurrentHole = 0;
int clubDlgHole = 0;

void updateFileStats() {
  gFileShotStats << setprecision(kPrecision);
  for (int ix = 0; ix < k18; ++ix) {
    if (gShotRA[ix].nmarks > 1) {
      gFileShotStats << "Hole\t" << ix + 1 << endl;
      gFileShotStats << gShotRA[ix] << endl;
    }
  }
  gFileShotStats.flush();
}

static void oKBtn_cb(Fl_Widget *w, void *data) {
  updateFileStats();
  CClubDlg *ccd = (CClubDlg *)data;
  ccd->hide();
  gCurrentHole = saveCurrentHole;
}

static void btnPrev_cb(Fl_Widget *w, void *data) {
  clubDlgHole--;
  if (clubDlgHole < 1) clubDlgHole = 1;
  gCurrentHole = clubDlgHole;
  string s = to_string(clubDlgHole);
  buff->text(s.c_str());
  boxHole->redraw();
  int v = countValidDistances(clubDlgHole - 1);
  clubcard->rows(v);
  clubcard->setHole(clubDlgHole - 1);
  clubcard->set_selection(0, 0, 0, 0);
  clubcard->redraw();
}

static void btnNext_cb(Fl_Widget *w, void *data) {
  clubDlgHole++;
  if (clubDlgHole > 18) clubDlgHole = 18;
  gCurrentHole = clubDlgHole;
  string s = to_string(clubDlgHole);
  buff->text(s.c_str());
  boxHole->redraw();
  int v = countValidDistances(clubDlgHole - 1);
  clubcard->rows(v);
  clubcard->setHole(clubDlgHole - 1);
  clubcard->set_selection(0, 0, 0, 0);
  clubcard->redraw();
}

void updateClubCard(int btnIndex) {
  int h = clubDlgHole - 1;
  clubcard->setHole(h);
  int v = countValidDistances(h);
  int sel_row;
  int col_left;
  int row_bot;
  int col_right;
  clubcard->get_selection(sel_row, col_left, row_bot, col_right);
  gShotRA[h].shot[sel_row].club = clubNamesRA[btnIndex];
  sel_row++;
  if (sel_row >= v) sel_row = 0;
  clubcard->set_selection(sel_row, 0, sel_row, 0);
  clubcard->redraw();
}

static void upBtn_cb(Fl_Widget *w, void *data) {
  int row_top;
  int col_left;
  int row_bot;
  int col_right;
  clubcard->get_selection(row_top, col_left, row_bot, col_right);
  btnPresses = row_top;
  btnPresses--;
  int v = countValidDistances(clubDlgHole - 1);
  if (btnPresses < 0) btnPresses = v - 1;
  clubcard->set_selection(btnPresses, 0, btnPresses, 0);
  clubcard->redraw();
}

static void downBtn_cb(Fl_Widget *w, void *data) {
  int row_top;
  int col_left;
  int row_bot;
  int col_right;
  clubcard->get_selection(row_top, col_left, row_bot, col_right);
  btnPresses = row_top;
  btnPresses++;
  int v = countValidDistances(clubDlgHole - 1);
  if (btnPresses >= v) btnPresses = 0;
  clubcard->set_selection(btnPresses, 0, btnPresses, 0);
  clubcard->redraw();
}

void clubBtn_cb(Fl_Widget *w, void *data) {
  if (w == btnDr) {
    btnIndex = 0;
  } else if (w == btn3w) {
    btnIndex = 1;
  } else if (w == btn5w) {
    btnIndex = 2;
  } else if (w == btn7w) {
    btnIndex = 3;
  } else if (w == btnHy) {
    btnIndex = 4;
  } else if (w == btn2) {
    btnIndex = 5;
  } else if (w == btn3) {
    btnIndex = 6;
  } else if (w == btn4) {
    btnIndex = 7;
  } else if (w == btn5) {
    btnIndex = 8;
  } else if (w == btn6) {
    btnIndex = 9;
  } else if (w == btn7) {
    btnIndex = 10;
  } else if (w == btn8) {
    btnIndex = 11;
  } else if (w == btn9) {
    btnIndex = 12;
  } else if (w == btnPW) {
    btnIndex = 13;
  } else if (w == btnGW) {
    btnIndex = 14;
  } else if (w == btnSW) {
    btnIndex = 15;
  } else if (w == btnLW) {
    btnIndex = 16;
  } else if (w == btnX) {
    btnIndex = 17;
  }
  updateClubCard(btnIndex);
}

void CClubDlg::setClubBtnStyle(Fl_Button *b) {
  b->labelfont(1);
  b->labelsize(36);
  b->color(FL_WHITE);
  b->down_color(FL_DARK_BLUE);
}

void setImageBtnSytle(Fl_Image_Button *b, Fl_JPEG_Image *up,
                      Fl_JPEG_Image *down) {
  b->up_image(up);  // buttons default image is down image
  b->down_image(down);
  b->image(NULL);
  b->color(FL_WHITE);
  b->down_color(FL_DARK_BLUE);
}

CClubDlg::CClubDlg(int X, int Y, int W, int H, const char *L)
    : Fl_Window(X, Y, W, H, L) {
  const int kLMargin = 12;
  const int kDY = 8;
  ////
  const int kNavBtnY = 8;
  const int kNavBtnSz = 48;
  const int kboxHoleX = 240;
  const int kNavBtnDX = 100;
  const int kbtnPrevX = kboxHoleX - kNavBtnDX;
  const int kbtnNextX = kboxHoleX + kNavBtnSz + 36;

  ////
  const int kClubcardY = kNavBtnY + kNavBtnSz + kDY;
  const int kClubcardH = 280;
  const int kClubcardW = 458;
  ////
  const int kUpDownY = kClubcardY + kClubcardH + kDY;
  const int kUpDownSz = 60;
  int upX = 0;
  int downX = 0;
  ////
  const int kClubBtnsY = kUpDownY + kUpDownSz + kDY;
  const int kBSize = 72;
  const int kClubBtnsDX = 4;
  int col = kLMargin;
  int row = kClubBtnsY;
  ////
  const int kOkX = 174;
  const int kOkW = kBtnW;

  {
    btnPrev = new Fl_Image_Button(kbtnPrevX, kNavBtnY, kNavBtnSz, kNavBtnSz);
    Fl_JPEG_Image *iup = new Fl_JPEG_Image("img/prev-arrow.jpg");
    if (iup->Fl_Image::fail())
      cout << "up-arrow.jpg could not be loaded" << endl;
    Fl_JPEG_Image *iup_down = new Fl_JPEG_Image("img/prev-arrow-down.jpg");
    if (iup_down->Fl_Image::fail())
      cout << "up-arrow-down.jpg could not be loaded" << endl;
    setImageBtnSytle(btnPrev, iup, iup_down);
    btnPrev->callback(btnPrev_cb, this);
  }
  {
    boxHole = new Fl_Text_Display(kboxHoleX, kNavBtnY, kNavBtnSz, kNavBtnSz);
    boxHole->textfont(1);
    boxHole->textsize(40);
    boxHole->textcolor(FL_BLACK);
    boxHole->color(Fl_Color(159), Fl_Color(159));
    boxHole->box(FL_NO_BOX);
    buff = new Fl_Text_Buffer();
    boxHole->buffer(buff);
    string s = to_string(gCurrentHole);
    buff->text(s.c_str());
    boxHole->scrollbar_width(0);
    // boxHole->insert(s.c_str());
  }
  {
    btnNext = new Fl_Image_Button(kbtnNextX, kNavBtnY, kNavBtnSz, kNavBtnSz);
    Fl_JPEG_Image *idown = new Fl_JPEG_Image("img/next-arrow.jpg");
    if (idown->Fl_Image::fail())
      cout << "down-arrow.jpg could not be loaded" << endl;
    Fl_JPEG_Image *idown_down = new Fl_JPEG_Image("img/next-arrow-down.jpg");
    if (idown_down->Fl_Image::fail())
      cout << "down-arrow-down.jpg could not be loaded" << endl;
    setImageBtnSytle(btnNext, idown, idown_down);
    btnNext->callback(btnNext_cb, this);
  }

  { clubcard = new CClubcard(kLMargin, kClubcardY, kClubcardW, kClubcardH); }
  // Row 1
  {
    btnDr = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[kDr].c_str());
    btnDr->callback(clubBtn_cb, this);
    setClubBtnStyle(btnDr);
    col += kBSize + kClubBtnsDX;
  }
  {
    btn3w = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[k3w].c_str());
    btn3w->callback(clubBtn_cb, this);
    setClubBtnStyle(btn3w);
    upX = col;
    col += kBSize + kClubBtnsDX;
  }
  {
    btn5w = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[k5w].c_str());
    btn5w->callback(clubBtn_cb, this);
    setClubBtnStyle(btn5w);
    downX = col;
    col += kBSize + kClubBtnsDX;
  }
  {
    btn7w = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[k7w].c_str());
    btn7w->callback(clubBtn_cb, this);
    setClubBtnStyle(btn7w);
    col += kBSize + kClubBtnsDX;
  }
  {
    btnHy = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[kHy].c_str());
    btnHy->callback(clubBtn_cb, this);
    setClubBtnStyle(btnHy);
    col += kBSize + kClubBtnsDX;
  }
  {
    btn2 = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[k2].c_str());
    btn2->callback(clubBtn_cb, this);
    setClubBtnStyle(btn2);
    col = kLMargin;
    row += kBSize;
  }
  // Row 2
  {
    btn3 = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[k3].c_str());
    btn3->callback(clubBtn_cb, this);
    setClubBtnStyle(btn3);
    col += kBSize + kClubBtnsDX;
  }
  {
    btn4 = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[k4].c_str());
    btn4->callback(clubBtn_cb, this);
    setClubBtnStyle(btn4);
    col += kBSize + kClubBtnsDX;
  }
  {
    btn5 = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[k5].c_str());
    btn5->callback(clubBtn_cb, this);
    setClubBtnStyle(btn5);
    col += kBSize + kClubBtnsDX;
  }
  {
    btn6 = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[k6].c_str());
    btn6->callback(clubBtn_cb, this);
    setClubBtnStyle(btn6);
    col += kBSize + kClubBtnsDX;
  }
  {
    btn7 = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[k7].c_str());
    btn7->callback(clubBtn_cb, this);
    setClubBtnStyle(btn7);
    col += kBSize + kClubBtnsDX;
  }
  {
    btn8 = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[k8].c_str());
    btn8->callback(clubBtn_cb, this);
    setClubBtnStyle(btn8);
    col = kLMargin;
    row += kBSize;
  }
  // Row 3
  {
    btn9 = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[k9].c_str());
    btn9->callback(clubBtn_cb, this);
    setClubBtnStyle(btn9);
    col += kBSize + kClubBtnsDX;
  }
  {
    btnPW = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[kPW].c_str());
    btnPW->callback(clubBtn_cb, this);
    setClubBtnStyle(btnPW);
    col += kBSize + kClubBtnsDX;
  }
  {
    btnGW = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[kGW].c_str());
    btnGW->callback(clubBtn_cb, this);
    setClubBtnStyle(btnGW);
    col += kBSize + kClubBtnsDX;
  }
  {
    btnSW = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[kSW].c_str());
    btnSW->callback(clubBtn_cb, this);
    setClubBtnStyle(btnSW);
    col += kBSize + kClubBtnsDX;
  }
  {
    btnLW = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[kLW].c_str());
    btnLW->callback(clubBtn_cb, this);
    setClubBtnStyle(btnLW);
    col += kBSize + kClubBtnsDX;
  }
  {
    btnX = new Fl_Button(col, row, kBSize, kBSize, clubNamesRA[kx].c_str());
    btnX->callback(clubBtn_cb, this);
    setClubBtnStyle(btnX);
  }
  // order important upX, downX set above
  {
    upBtn = new Fl_Image_Button(upX, kUpDownY, kUpDownSz, kUpDownSz);
    Fl_JPEG_Image *iup = new Fl_JPEG_Image("img/up-arrow.jpg");
    if (iup->Fl_Image::fail())
      cout << "up-arrow.jpg could not be loaded" << endl;
    Fl_JPEG_Image *iup_down = new Fl_JPEG_Image("img/up-arrow-down.jpg");
    if (iup_down->Fl_Image::fail())
      cout << "up-arrow-down.jpg could not be loaded" << endl;
    upBtn->up_image(iup);         // buttons default image is up image
    upBtn->down_image(iup_down);  // the identifyable name as described above
    upBtn->image(NULL);
    upBtn->color(FL_WHITE);
    upBtn->down_color(FL_DARK_BLUE);
    upBtn->callback(upBtn_cb, this);
  }
  {
    downBtn = new Fl_Image_Button(downX, kUpDownY, kUpDownSz, kUpDownSz);
    Fl_JPEG_Image *idown = new Fl_JPEG_Image("img/down-arrow.jpg");
    if (idown->Fl_Image::fail())
      cout << "down-arrow.jpg could not be loaded" << endl;
    Fl_JPEG_Image *idown_down = new Fl_JPEG_Image("img/down-arrow-down.jpg");
    if (idown_down->Fl_Image::fail())
      cout << "down-arrow-down.jpg could not be loaded" << endl;
    downBtn->up_image(idown);  // buttons default image is down image
    downBtn->down_image(
        idown_down);  // the identifyable name as described above
    downBtn->image(NULL);
    downBtn->color(FL_WHITE);
    downBtn->down_color(FL_DARK_BLUE);
    downBtn->callback(downBtn_cb, this);
  }
  {
    oKBtn = new Fl_Button(kOkX, kBtnWinBottomY, kOkW, kBtnH, "OK");
    setButtonStyle(oKBtn);
    oKBtn->callback(oKBtn_cb, this);
  }
  end();

  color((Fl_Color)159);
  set_modal();
  size_range(480, 800, 480, 800);
  clear_border();

  saveCurrentHole = gCurrentHole;
  clubDlgHole = gCurrentHole;
  int h = clubDlgHole - 1;
  clubcard->setHole(h);
  show();
}

void createCClubDlg() { clubcardDlg = new CClubDlg(0, 0, 480, 800); }
