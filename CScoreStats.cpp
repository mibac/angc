#ifndef CSCORESTATS_H
#include "CScoreStats.h"
#endif

CScoreStats cStats;

CScoreStats::CScoreStats() : totalUpdown(0), totalPutts(0), totalScore(0) {
  for (int ii = 0; ii < k18; ++ii) {
    statsRA[ii].setHole(ii + 1);
    statsRA[ii].setUpdown(2);
    statsRA[ii].setPutts(2);
    statsRA[ii].setScore(parRA[ii]);
  }
}

// int CScoreStats::getTotalUpdown() {
//   for (int ii = 0; ii < k18; ++ii) {
//     totalUpdown += statsRA[ii].getUpdown();
//   }
//   return totalUpdown;
// }
//
// int CScoreStats::getTotalPutts() {
//   for (int ii = 0; ii < k18; ++ii) {
//     totalPutts += statsRA[ii].getPutts();
//   }
//   return totalPutts;
// }
// int CScoreStats::getTotalScore() {
//   for (int ii = 0; ii < k18; ++ii) {
//     totalScore += statsRA[ii].getScore();
//   }
//   return totalScore;
// }
//
// int CScoreStats::getRelationToPar() {
//   int myscore = 0;
//
//   for (int ii = 0; ii < k18; ++ii) myscore += statsRA[ii].getScore();
//   return myscore - 72;
// }

CScores* CScoreStats::getScoreStats(const int hole) {
  CScores* cs = nullptr;
  for (int ii = 0; ii < k18; ++ii) {
    if (statsRA[ii].getHole() == hole) *cs = statsRA[ii];
    break;
  }
  return cs;
}

int CScoreStats::getAccumUpdowns(int fromHole, int toHole) {
  int total = 0;
  for (int ii = fromHole; ii < toHole; ++ii) total += statsRA[ii].getUpdown();
  return total;
}

int CScoreStats::getAccumPutts(int fromHole, int toHole) {
  int total = 0;
  for (int ii = fromHole; ii < toHole; ++ii) total += statsRA[ii].getPutts();
  return total;
}

int CScoreStats::getAccumScore(int fromHole, int toHole) {
  int total = 0;
  for (int ii = fromHole; ii < toHole; ++ii) total += statsRA[ii].getScore();
  return total;
}

int CScoreStats::getAccumPar(int fromHole, int toHole) {
  int total = 0;
  for (int ii = fromHole; ii < toHole; ++ii) total += parRA[ii];
  return total;
}
