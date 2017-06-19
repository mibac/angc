//
// "$Id$"
//
//    Simple example of using Fl_Table - Greg Ercolano 11/29/2010
//
//    Demonstrates the simplest use of Fl_Table possible.
//    Display a 10x10 array of integers with row/col headers.
//    No interaction; simple display of data only.
//    See other examples for more complex interactions with the table.
//
// Copyright 2010 Greg Ercolano.
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#ifndef CSCORECARD_H
#include "CScorecard.h"
#endif

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <FL/fl_draw.H>

#include <string>

using namespace std;

const int kHoleRow = 0;
const int kHdcpRow = 1;
const int kParRow = 2;
const int kScoreRow = 3;
const int kPuttRow = 4;
const int kUDRow = 5;

struct frontBackResults {
  int fscore;
  int bscore;
  int fputts;
  int bputts;
  int fuds;
  int buds;
};

frontBackResults results;

// Draw the row/col headings
//    Make this a dark thin upbox with the text inside.
//
void CScorecard::DrawHeader(const char *s, int X, int Y, int W, int H) {
  fl_push_clip(X, Y, W, H);
  fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
  fl_color(FL_BLACK);
  fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
  fl_pop_clip();
}
// Draw the cell data
//    Dark gray text on white background with subtle border
//
void CScorecard::DrawData(const char *s, int X, int Y, int W, int H) {
  fl_push_clip(X, Y, W, H);
  // Draw cell bg
  fl_color(FL_WHITE);
  fl_rectf(X, Y, W, H);
  // Draw cell data
  fl_color(FL_GRAY0);
  string str(s);
  if (str == "0") str = " ";
  fl_draw(str.c_str(), X, Y, W, H, FL_ALIGN_CENTER);
  // Draw box border
  fl_color(color());
  fl_rect(X, Y, W, H);
  fl_pop_clip();
}

void CScorecard::drawHoleData(int COL, int X, int Y, int W, int H) {
  if (COL == 9) {
    DrawData("T", X, Y, W, H);
    } else if (COL == 10) {
      DrawData("TT", X, Y, W, H);
  } else if (gFront9) {
    DrawData(aNGCHoles[COL].hole.c_str(), X, Y, W, H);
  } else {
    DrawData(aNGCHoles[COL + 9].hole.c_str(), X, Y, W, H);
  }
}

void CScorecard::drawHdcpData(int COL, int X, int Y, int W, int H) {
  if ((COL == 9) || (COL == 10)) {
    DrawData(" ", X, Y, W, H);
  } else if (gFront9) {
    DrawData(aNGCHoles[COL].hdcp.c_str(), X, Y, W, H);
  } else {
    DrawData(aNGCHoles[COL + 9].hdcp.c_str(), X, Y, W, H);
  }
}

void CScorecard::drawParData(int COL, int X, int Y, int W, int H) {
  if (COL == 9) {
    DrawData(sumRow(kParRow).c_str(), X, Y, W, H);
  } else if (COL == 10) {
    if (gFront9) {
      DrawData(" ", X, Y, W, H);
    } else {
      DrawData(" ", X, Y, W, H);
    }
  } else if (gFront9) {
    DrawData(aNGCHoles[COL].par.c_str(), X, Y, W, H);
  } else {
    DrawData(aNGCHoles[COL + 9].par.c_str(), X, Y, W, H);
  }
}

void CScorecard::drawScoreData(int COL, int X, int Y, int W, int H) {
  if (COL == 9) {
    DrawData(sumRow(kScoreRow).c_str(), X, Y, W, H);
    } else if ((COL == 10) && (!gFront9)) {
      int n = results.fscore + results.bscore;
      string s = to_string(n);
      DrawData(s.c_str(), X, Y, W, H);
  } else if (gFront9) {
    DrawData(gsd[COL].score.c_str(), X, Y, W, H);
  } else {
    DrawData(gsd[COL + 9].score.c_str(), X, Y, W, H);
  }
}

void CScorecard::drawPuttData(int COL, int X, int Y, int W, int H) {
  if (COL == 9) {
    DrawData(sumRow(kPuttRow).c_str(), X, Y, W, H);
    } else if ((COL == 10) && (!gFront9)) {
      int n = results.fputts + results.bputts;
      string s = to_string(n);
      DrawData(s.c_str(), X, Y, W, H);
  } else if (gFront9) {
    DrawData(gsd[COL].putts.c_str(), X, Y, W, H);
  } else {
    DrawData(gsd[COL + 9].putts.c_str(), X, Y, W, H);
  }
}

void CScorecard::drawUDData(int COL, int X, int Y, int W, int H) {
  if (COL == 9) {
    DrawData(sumRow(kUDRow).c_str(), X, Y, W, H);
    } else if ((COL == 10) && (!gFront9)) {
      int n = results.fuds + results.buds;
      string s = to_string(n);
      DrawData(s.c_str(), X, Y, W, H);
  } else if (gFront9) {
    DrawData(gsd[COL].uds.c_str(), X, Y, W, H);
  } else {
    DrawData(gsd[COL + 9].uds.c_str(), X, Y, W, H);
  }
}

string CScorecard::sumRow(const int row) {
  int total = 0;
  int tmp;
  string s;

  switch (row) {
    case kParRow:
      if (gFront9) {
        for (int ix = 0; ix < 9; ++ix) total += stoi(aNGCHoles[ix].par);
      } else {
        for (int ix = 9; ix < k18; ++ix) total += stoi(aNGCHoles[ix].par);
      }
      break;
    case kScoreRow:
      if (gFront9) {
        for (int ix = 0; ix < 9; ++ix) {
          if (gsd[ix].score == "")
            tmp = 0;
          else
            tmp = stoi(gsd[ix].score);
          total += tmp;
        }
        results.fscore = total;
      } else {
        for (int ix = 9; ix < k18; ++ix) {
          if (gsd[ix].score == "")
            tmp = 0;
          else
            tmp = stoi(gsd[ix].score);
          total += tmp;
        }
        results.bscore = total;
      }
      break;
    case kPuttRow:
      if (gFront9) {
        for (int ix = 0; ix < 9; ++ix) {
          if (gsd[ix].putts == "")
            tmp = 0;
          else
            tmp = stoi(gsd[ix].putts);
          total += tmp;
        }
        results.fputts = total;
      } else {
        for (int ix = 9; ix < k18; ++ix) {
          if (gsd[ix].putts == "")
            tmp = 0;
          else
            tmp = stoi(gsd[ix].putts);
          total += tmp;
        }
        results.bputts = total;
      }
      break;
    case kUDRow:
      if (gFront9) {
        for (int ix = 0; ix < 9; ++ix) {
          if (gsd[ix].uds == "")
            tmp = 0;
          else
            tmp = stoi(gsd[ix].uds);
          total += tmp;
        }
        results.fuds = total;
      } else {
        for (int ix = 9; ix < k18; ++ix) {
          if (gsd[ix].uds == "")
            tmp = 0;
          else
            tmp = stoi(gsd[ix].uds);
          total += tmp;
        }
        results.buds = total;
      }
      break;
    default:
      /* code */
      break;
  }
  s = to_string(total);
  return s;
}

// Handle drawing table's cells
//     Fl_Table calls this function to draw each visible cell in the
//     table. It's up to us to use FLTK's drawing functions to draw the
//     cells the way we want.
//
void CScorecard::draw_cell(TableContext context, int ROW, int COL, int X, int Y,
                           int W, int H) {
  static char s[40];
  string str;
  switch (context) {
    case CONTEXT_STARTPAGE:  // before page is drawn..
      fl_font(FL_HELVETICA_BOLD,
              18);  // set the font for our drawing operations
      return;
    case CONTEXT_COL_HEADER:        // Draw column headers
      sprintf(s, "%c", 'A' + COL);  // "A", "B", "C", etc.
      DrawHeader(s, X, Y, W, H);
      return;
    case CONTEXT_ROW_HEADER:  // Draw row headers
      if (ROW == 0)
        str = "Hole";
      else if (ROW == 1)
        str = "Hdcp";
      else if (ROW == 2)
        str = "Par";
      else if (ROW == 3)
        str = "Score";
      else if (ROW == 4)
        str = "Putt";
      else if (ROW == 5)
        str = "UD";
      DrawHeader(str.c_str(), X, Y, W, H);
      return;
    case CONTEXT_CELL:  // Draw data in cells
      fl_font(FL_HELVETICA_BOLD,
              24);  // set the font for our drawing operations
      if (COL == 10) DrawData(" ", X, Y, W, H);
      if (ROW == kHoleRow)
        drawHoleData(COL, X, Y, W, H);
      else if (ROW == kHdcpRow)
        drawHdcpData(COL, X, Y, W, H);
      else if (ROW == kParRow)
        drawParData(COL, X, Y, W, H);
      else if (ROW == kScoreRow)
        drawScoreData(COL, X, Y, W, H);
      else if (ROW == kPuttRow)
        drawPuttData(COL, X, Y, W, H);
      else if (ROW == kUDRow)
        drawUDData(COL, X, Y, W, H);

      return;  // CONTEXT_CELL

    default:
      return;
  }
}

// Constructor
//     Make our data array, and initialize the table options.
//
CScorecard::CScorecard(int X, int Y, int W, int H, const char *L)
    : Fl_Table(X, Y, W, H, L) {
  // Rows
  rows(MAX_ROWS);      // how many rows
  row_header(1);       // enable row headers (along left)
  row_height_all(40);  // default height of rows
  row_header_width(60);
  row_resize(0);  // disable row resizing
  // Cols
  cols(MAX_COLS);     // how many columns
  col_header(0);      // enable column headers (along top)
  col_width_all(36);  // default width of columns
  col_resize(0);      // enable column resizing

  color((Fl_Color)159);
  end();  // end the Fl_Table group
}

//
// End of "$Id$".
//
