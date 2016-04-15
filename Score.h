#ifndef SCORE_H
#define SCORE_H

#include <QString>

class Score {
private:
    int m_correct[7]; // each column is a note
    int m_total[7]; // each column is a note

public:
    Score();
    void correctAnswer(unsigned int a_pitch);
    void wrongAnswer(unsigned int a_pitch);
    int getCorrect();
    int getTotal();
    QString getScore();
};

#endif // SCORE_H
