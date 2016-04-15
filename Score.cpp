#include "Score.h"

Score::Score() {
    for(int i=0; i<7; i++) {
        m_correct[i] = 0;
        m_total[i] = 0;
    }
}

void Score::correctAnswer(unsigned int a_pitch){
    if (a_pitch<7) {
        m_correct[a_pitch] += 1;
        m_total[a_pitch] += 1;
    }
}

void Score::wrongAnswer(unsigned int a_pitch){
    if (a_pitch<7) {
        m_total[a_pitch] += 1;
    }
}

int Score::getCorrect() {
    int sum = 0;
    for(int i=0; i<7; i++) { sum += m_correct[i]; }
    return sum;
}

int Score::getTotal() {
    int sum = 0;
    for(int i=0; i<7; i++) { sum += m_total[i]; }
    return sum;
}

QString Score::getScore() {
    return QString::number(this->getCorrect()) +"/"+QString::number(this->getTotal());
}
