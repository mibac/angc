#ifndef CSCORES_H
#define CSCORES_H

#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

class CScores
{
public:
    CScores();
    CScores(const int hole, const int updown, const int putt, const int score);

    ~CScores() = default;
    CScores(const CScores& other) = default;
    CScores(CScores&& other) = default;
    CScores& operator=(const CScores& other) = default;
    CScores& operator=(CScores&& other) = default;

    time_t getDate();
    int getHole();
    int getUpdown();
    int getPutts();
    int getScore();

    void setDate(time_t t);
    void setHole(int n);
    void setUpdown(int n);
    void setPutts(int n);
    void setScore(int n);

    void printAsciiDate();

friend ostream &operator<<(ostream &strm, const CScores &cs);

private:
    time_t date;
    int hole;
    int updown;
    int putts;
    int score;
};

#endif  // CSCORES_H
