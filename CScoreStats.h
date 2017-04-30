#ifndef CSCORESTATS_H
#define CSCORESTATS_H

#include <ctime>
#include <array>

#ifndef CSCORES_H
#include "CScores.h"
#endif

using namespace std;

class CScoreStats {
 public:
  CScoreStats();

  ~CScoreStats() = default;
  CScoreStats(const CScoreStats& other) = default;
  CScoreStats(CScoreStats&& other) = default;
  CScoreStats& operator=(const CScoreStats& other) = default;
  CScoreStats& operator=(CScoreStats&& other) = default;

  CScores* getScoreStats(const int hole);
  int getTotalUpdown();
  int getTotalPutts();
  int getTotalScore();
  array<CScores, 18> statsRA;

 private:
  int totalUpdown;
  int totalPutts;
  int totalScore;
};

extern CScoreStats cStats;
#endif  // CSCORESTATS_H
