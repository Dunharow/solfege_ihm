#include "Score.h"

/**
 *  Constructeur de la classe Score
 *  Initialise les vecteurs.
 */
Score::Score() {
    for(int i=0; i<13; i++) {
        m_solCorrect[i] = 0;
        m_solTotal[i] = 0;
        m_faCorrect[i] = 0;
        m_faTotal[i] = 0;
        m_solPerc[i] = 0;
        m_faPerc[i] = 0;
    }
}

/**
 *  Comportement quand la note donnée est juste.
 */
void Score::correctAnswer(int a_octave, int a_pitch, QString a_clef) {
    if (a_clef == "fa") {
        m_faCorrect[note2value(a_pitch, a_octave, a_clef)-1] += 1;
        m_faTotal  [note2value(a_pitch, a_octave, a_clef)-1] += 1;
    } else {
        m_solCorrect[note2value(a_pitch, a_octave, a_clef)-1] += 1;
        m_solTotal  [note2value(a_pitch, a_octave, a_clef)-1] += 1;
    }
    updatePerc();
}

/**
 *  Comportement quand la note donnée est fausse.
 */
void Score::wrongAnswer(int a_octave, int a_pitch, QString a_clef) {
    if (a_clef == "fa") {
        m_faTotal[note2value(a_pitch, a_octave, a_clef)-1]  += 1;
    } else {
        m_solTotal[note2value(a_pitch, a_octave, a_clef)-1] += 1;
    }
    updatePerc();
}

void Score::updatePerc() {
    int correctPerc,timePerc,freqPerc;

    for(int i=0; i<13; i++) {
        // SOL PERCENTAGES
        correctPerc = 0;
        timePerc = 0;
        freqPerc = 0;

        if (m_solTotal[i] != 0)
            {correctPerc = (double)m_solCorrect[i] / m_solTotal[i] * 50;}

        if (getTotal("sol") != 0)
            {freqPerc = (double)m_solTotal[i] / getTotal("sol") * 30;}

        m_solPerc[i] = correctPerc + timePerc + freqPerc;

        // FA PERCENTAGES
        correctPerc = 0;
        timePerc = 0;
        freqPerc = 0;

        if (m_faTotal[i] != 0)
            {correctPerc= (double)m_faCorrect[i] / m_faTotal[i] * 50;}

        if (getTotal("fa") != 0)
            {freqPerc = (double)m_faTotal[i] / getTotal("fa") * 30;}

        m_faPerc[i] = correctPerc + timePerc + freqPerc;
    }
}

int Score::getCorrect() {
    int sum = 0;
    for(int i=0; i<13; i++) { sum += m_solCorrect[i] + m_faCorrect[i]; }
    return sum;
}

int Score::getTotal(QString a_clef) {
    int sum = 0;
    if ((a_clef=="all") || (a_clef=="sol")) {
        for(int i=0; i<13; i++) { sum += m_solTotal[i]; }
    }

    if ((a_clef=="all") || (a_clef=="fa")) {
        for(int i=0; i<13; i++) { sum += m_faTotal[i]; }
    }

    return sum;
}

QString Score::getScore() {
    return QString::number(this->getCorrect()) +"/"+ QString::number(this->getTotal());
}

double Score::getPerc(QString a_clef, int a_note) {
    if (a_clef=="fa") {
        return m_solPerc[a_note];
    } else {
        return m_faPerc[a_note];
    }
}
