#ifndef CSCORESTATS_H
#include "CScoreStats.h"
#endif

CScoreStats cStats;

CScoreStats::CScoreStats() : totalUpdown(0), totalPutts(0), totalScore(0) {
  for (int ii = 0; ii < k18; ++ii) {
    statsRA[ii].setHole(ii + 1);
    statsRA[ii].setScore(parRA[ii]);
    statsRA[ii].setPutts(2);
    statsRA[ii].setUpdown(2);
  }
}

CScores* CScoreStats::getScoreStats(const int hole) {
  CScores* cs = nullptr;
  for (int ii = 0; ii < k18; ++ii) {
    if (statsRA[ii].getHole() == hole) *cs = statsRA[ii];
    break;
  }
  return cs;
}

int CScoreStats::getAccumUpdowns() {
  int total = 0;
  for (int ii = 0; ii < k18; ++ii)
    if (bPlayedHole[ii]) total += statsRA[ii].getUpdown();
  return total;
}

int CScoreStats::getAccumPutts() {
  int total = 0;
  for (int ii = 0; ii < k18; ++ii)
    if (bPlayedHole[ii]) total += statsRA[ii].getPutts();
  return total;
}

int CScoreStats::getAccumScore() {
  int total = 0;
  for (int ii = 0; ii < k18; ++ii)
    if (bPlayedHole[ii]) total += statsRA[ii].getScore();
  return total;
}

int CScoreStats::getAccumPar() {
  int total = 0;
  for (int ii = 0; ii < k18; ++ii)
    if (bPlayedHole[ii]) total += parRA[ii];
  return total;
}

void CScoreStats::printScores() {  for (int ix = 0; ix < k18; ++ix) {
    if (bPlayedHole[ix]) cout << statsRA[ix];
  }
}
