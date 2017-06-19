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
#define CSCORECARD_H

#include <FL/Fl.H>
#include <FL/Fl_Table.H>

#include <string>

using namespace std;

#define MAX_ROWS 6
#define MAX_COLS 11
// #define MAX_COLS 10

// Derive a class from Fl_Table
class CScorecard : public Fl_Table {
  int data[MAX_ROWS][MAX_COLS];  // data array for cells
  // Draw the row/col headings
  //    Make this a dark thin upbox with the text inside.
  //
  void DrawHeader(const char *s, int X, int Y, int W, int H);
  // Draw the cell data
  //    Dark gray text on white background with subtle border
  //
  void DrawData(const char *s, int X, int Y, int W, int H);
  // Handle drawing table's cells
  //     Fl_Table calls this function to draw each visible cell in the table.
  //     It's up to us to use FLTK's drawing functions to draw the cells the way
  //     we want.
  //
  void draw_cell(TableContext context, int ROW = 0, int COL = 0, int X = 0,
                 int Y = 0, int W = 0, int H = 0);

  void drawHoleData(int COL, int X, int Y, int W, int H);
  void drawHdcpData(int COL, int X, int Y, int W, int H);
  void drawParData(int COL, int X, int Y, int W, int H);
  void drawScoreData(int COL, int X, int Y, int W, int H);
  void drawPuttData(int COL, int X, int Y, int W, int H);
  void drawUDData(int COL, int X, int Y, int W, int H);
  string sumRow(const int row);

 public:
  // Constructor
  //     Make our data array, and initialize the table options.
  //
  CScorecard(int X, int Y, int W, int H, const char *L = 0);
  ~CScorecard() {}
};

#endif
//
// End of "$Id$".
//
