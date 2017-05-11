#ifndef CSCORES_H
#include "CScores.h"
#endif

#ifndef CGLOBALS_H
#include "globals.h"
#endif


CScores::CScores() : date(gToday), hole(0), updown(0), putts(0), score(0) {}

CScores::CScores( const int h, const int u, const int p, const int s) {
  date = gToday;
  hole = h;
  updown = u;
  putts = p;
  score = s;
}

time_t CScores::getDate() { return date; }
int CScores::getHole() { return hole; }
int CScores::getScore() { return score; }
int CScores::getUpdown() { return updown; }
int CScores::getPutts() { return putts; }

void CScores::setDate(time_t t) { date = t; }
void CScores::setHole(int n) { hole = n; }
void CScores::setScore(int n) { score = n; }
void CScores::setUpdown(int n) { updown = n; }
void CScores::setPutts(int n) { putts = n; }

string getAsciiDate(const time_t date) {
    return asctime(std::localtime(&date));
}


ostream& operator<<(ostream& strm, const CScores& cs) {
  strm << cs.hole << "\t"
  << cs.updown << "\t"
  << cs.putts << "\t"
  << cs.score << "\t"
  << getAsciiDate(cs.date);

  return strm;
}
