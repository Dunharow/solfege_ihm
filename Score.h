#ifndef SCORE_H
#define SCORE_H

#include <QString>

#include <functions.h>
#include <stdlib.h>

class Score {
private:
    int m_solCorrect[13]; // each column is a note
    int m_faCorrect[13];
    int m_solTotal[13];
    int m_faTotal[13];

    double m_solPerc[13];
    double m_faPerc[13];
public:
    int m_solRanking[13];
    int m_faRanking[13];

//public:
    Score();
    void correctAnswer(int a_octave, int a_pitch, QString a_clef);
    void wrongAnswer(int a_octave, int a_pitch, QString a_clef);
    void updatePerc();
    int getCorrect();
    int getTotal(QString a_clef="all");
    QString getScore();
    double getPerc(QString a_clef, int a_note);
    void makeRanking();
    void getRanking(int pitchTable[], int octaTable[], int longueur, QString a_clef);

};

#endif // SCORE_H
