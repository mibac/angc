#ifndef CGLOBALS_H
#define CGLOBALS_H

#include <ctime>
#include <fstream>

using namespace std;

extern int gCurrentHole;
extern time_t gToday;

extern ofstream gFileStats;
extern ofstream gFileClub;
extern ofstream gFileGPS;

extern void initGlobals();

#endif  // CGLOBALS_H
