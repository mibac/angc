#ifndef CSCORESTATS_H
#define CSCORESTATS_H

#include <ctime>
#include <array>

#ifndef CGLOBALS_H
#include "globals.h"
#endif

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
  // int getTotalUpdown();
  // int getTotalPutts();
  // int getTotalScore();
  int getAccumUpdowns();
  int getAccumPutts();
  int getAccumScore();
  int getAccumPar();
  void printScores();
  
  array<CScores, k18> statsRA;
  const array<int, k18> parRA = {{5,3,4,5,4,4,3,4,4,4,3,5,4,4,4,5,3,4}};

 private:
  int totalUpdown;
  int totalPutts;
  int totalScore;
  int relToPar;
};

extern CScoreStats cStats;
#endif  // CSCORESTATS_H
