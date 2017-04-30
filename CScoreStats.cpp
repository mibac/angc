#ifndef CSCORESTATS_H
#include "CScoreStats.h"
#endif

CScoreStats cStats;

CScoreStats::CScoreStats() : totalUpdown(0), totalPutts(0), totalScore(0) {}

int CScoreStats::getTotalUpdown() {
  for (int ii = 0; ii < 18; ++ii) {
    totalUpdown += statsRA[ii].getUpdown();
  }
  return totalUpdown;
}

int CScoreStats::getTotalPutts() {
  for (int ii = 0; ii < 18; ++ii) {
    totalPutts += statsRA[ii].getPutts();
  }
  return totalPutts;
}
int CScoreStats::getTotalScore() {
  for (int ii = 0; ii < 18; ++ii) {
    totalScore += statsRA[ii].getScore();
  }
  return totalScore;
}

CScores* CScoreStats::getScoreStats(const int hole) {
  CScores* cs = nullptr;
  for (int ii = 0; ii < 18; ++ii) {
    if (statsRA[ii].getHole() == hole) *cs = statsRA[ii];
    break;
  }
  return cs;
}
