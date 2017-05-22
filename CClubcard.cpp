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

#ifndef CCLUBCARD_H
#include "CClubcard.h"
#endif

#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <FL/fl_draw.H>
#include <chrono>
#include <random>
#include <string>

using namespace std;

const int kRow1 = 0;
const int kRow2 = 1;
const int kRow3 = 2;
const int kRow4 = 3;
const int kRow5 = 4;
const int kRow6 = 5;

int getRandomYards(unsigned seed) {
  std::default_random_engine generator (seed*1000000);
  std::uniform_int_distribution<int> distribution(30, 200);
  int dice_roll =
      distribution(generator);  // generates number in the range 1..200
  return dice_roll;
}

void setupTestClubVector() {
  UtmLatLng utm(4922170.0, 488471.0);
  int h = 0;
  int marks = 0;
  gShotRA[h].nmarks = marks = 3;
  for (int ix = 0; ix < marks; ++ix) {
    gShotRA[h].holeStatsRA[ix].club = "";
    gShotRA[h].holeStatsRA[ix].utm.lat = utm.lat + getRandomYards(ix*(h+ix));
    gShotRA[h].holeStatsRA[ix].utm.lng = utm.lng + getRandomYards(ix*(h+ix));
  }

  h = 1;
  gShotRA[h].nmarks = marks = 7;
  for (int ix = 0; ix < marks; ++ix) {
    gShotRA[h].holeStatsRA[ix].club = "";
    gShotRA[h].holeStatsRA[ix].utm.lat = utm.lat + getRandomYards(ix*(h+ix));
    gShotRA[h].holeStatsRA[ix].utm.lng = utm.lng + getRandomYards(ix*(h+ix));
  }

  h = 2;
  gShotRA[h].nmarks = marks = 5;
  for (int ix = 0; ix < marks; ++ix) {
    gShotRA[h].holeStatsRA[ix].club = "";
    gShotRA[h].holeStatsRA[ix].utm.lat = utm.lat + getRandomYards(ix*(h+ix));
    gShotRA[h].holeStatsRA[ix].utm.lng = utm.lng + getRandomYards(ix*(h+ix));
  }

  h = 3;
  gShotRA[h].nmarks = marks = 2;
  for (int ix = 0; ix < marks; ++ix) {
    gShotRA[h].holeStatsRA[ix].club = "";
    gShotRA[h].holeStatsRA[ix].utm.lat = utm.lat + getRandomYards(ix*(h+ix));
    gShotRA[h].holeStatsRA[ix].utm.lng = utm.lng + getRandomYards(ix*(h+ix));
  }
}

// Draw the row/col headings
//    Make this a dark thin upbox with the text inside.
//
void CClubcard::DrawHeader(const char *s, int X, int Y, int W, int H) {
  fl_push_clip(X, Y, W, H);
  fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
  fl_color(FL_BLACK);
  fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
  fl_pop_clip();
}
// Draw the cell data
//    Dark gray text on white background with subtle border
//
void CClubcard::DrawData(const char *s, int X, int Y, int W, int H, int ROW,
                         int COL) {
  fl_push_clip(X, Y, W, H);
  // Draw cell bg
  fl_color(is_selected(ROW, COL) ? FL_YELLOW : FL_WHITE);
  fl_rectf(X, Y, W, H);
  // fl_color(FL_WHITE);
  fl_rectf(X, Y, W, H);
  // Draw cell data
  fl_color(FL_GRAY0);
  fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
  // Draw box border
  fl_color(color());
  fl_rect(X, Y, W, H);
  fl_pop_clip();
}

void CClubcard::drawShotData(int ROW, int COL, int X, int Y, int W, int H) {
  if (COL == 0) {
    DrawData(gShotRA[hole].holeStatsRA[ROW].club.c_str(), X, Y, W, H, ROW, COL);
  } else if (COL == 1) {
    int d = calcUTMdistance(gShotRA[hole].holeStatsRA[ROW + 1].utm,
                            gShotRA[hole].holeStatsRA[ROW].utm);
    gShotRA[hole].holeStatsRA[ROW].yards = d;
    DrawData(to_string(d).c_str(), X, Y, W, H, ROW, COL);
    cout << "Hole " << hole << " ";
    // cout << "ROW+1 " << gShotRA[hole].holeStatsRA[ROW + 1].utm << endl;
    // cout << "ROW " << gShotRA[hole].holeStatsRA[ROW].utm << endl;
    cout << "dist " << d << endl;
  }
}

// Handle drawing table's cells
//     Fl_Table calls this function to draw each visible cell in the
//     table. It's up to us to use FLTK's drawing functions to draw the
//     cells the way we want.
//
void CClubcard::draw_cell(TableContext context, int ROW, int COL, int X, int Y,
                          int W, int H) {
  // static char s[40];
  string str;
  int v = 0;
  switch (context) {
    case CONTEXT_STARTPAGE:  // before page is drawn..
      fl_font(FL_HELVETICA_BOLD,
              18);  // set the font for our drawing operations
      return;
    case CONTEXT_COL_HEADER:  // Draw column headers
      if (COL == 0)
        DrawHeader("Club", X, Y, W, H);
      else if (COL == 1)
        DrawHeader("Distance", X, Y, W, H);
      return;
    case CONTEXT_ROW_HEADER:  // Draw row headers
      v = countValidDistances(hole);
      if (ROW < v) DrawHeader(to_string(ROW + 1).c_str(), X, Y, W, H);
      return;
    case CONTEXT_CELL:  // Draw data in cells
                        // set the font for our drawing operations
      fl_font(FL_HELVETICA_BOLD, 24);
      drawShotData(ROW, COL, X, Y, W, H);
      return;  // CONTEXT_CELL

    default:
      return;
  }
}
// Constructor
//     Make our data array, and initialize the table options.
//
CClubcard::CClubcard(int X, int Y, int W, int H, const char *L)
    : Fl_Table(X, Y, W, H, L) {
  hole = 0;
  setupTestClubVector();
  // Rows
  int v = countValidDistances(hole);
  rows(v);             // how many rows
  row_header(1);       // enable row headers (along left)
  row_height_all(40);  // default height of rows
  row_header_width(48);
  row_resize(0);  // disable row resizing
  // Cols
  cols(MAX_C);         // how many columns
  col_header(1);       // enable column headers (along top)
  col_width_all(200);  // default width of columns
  col_resize(0);       // enable column resizing

  color((Fl_Color)159);
  end();  // end the Fl_Table group
  set_selection(0, 0, 0, 0);
}

//
// End of "$Id$".
//
