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
#define CCLUBCARD_H

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <FL/Fl.H>
#include <FL/Fl_Table.H>

#include <string>

using namespace std;

const int MAX_R = kMAX_SHOTS;
const int MAX_C = 2;  // A-Z

// Derive a class from Fl_Table
class CClubcard : public Fl_Table {
  int data[MAX_R][MAX_C];  // data array for cells
  // Draw the row/col headings
  //    Make this a dark thin upbox with the text inside.
  //
  void DrawHeader(const char *s, int X, int Y, int W, int H);
  // Draw the cell data
  //    Dark gray text on white background with subtle border
  //
  void DrawData(const char *s, int X, int Y, int W, int H, int ROW, int COL);
  // Handle drawing table's cells
  //     Fl_Table calls this function to draw each visible cell in the table.
  //     It's up to us to use FLTK's drawing functions to draw the cells the way
  //     we want.
  //
  void draw_cell(TableContext context, int ROW = 0, int COL = 0, int X = 0,
                 int Y = 0, int W = 0, int H = 0);

  void drawClubData(int ROW, int COL, int X, int Y, int W, int H);
  void drawDistanceData(int ROW, int COL, int X, int Y, int W, int H);

 public:
  // Constructor
  //     Make our data array, and initialize the table options.
  //
  CClubcard(int X, int Y, int W, int H, const char *L = 0);
  ~CClubcard() {}
};

#endif
//
// End of "$Id$".
//
