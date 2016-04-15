#include "Note.h"

using namespace std;

Note::Note(int min_pitch, int max_pitch, int min_octave, int max_octave) {
    srand((unsigned int)time(NULL));

    m_pitch = m_octave = -1;

    m_octave = rand()%(max_octave-min_octave) + min_octave; // random between min and max

    while(compareNotes(min_pitch,m_pitch,min_octave,m_octave) || compareNotes(m_pitch,max_pitch,m_octave,max_octave)) {
        m_pitch = rand() % 7; // random between 0 and 6
    }

    // OTHERS
    m_duration = 4;
    m_dot = false;
}

QString Note::getNote() {
    QString result("");

    switch (m_pitch){
    case 0:
        result = "do";
        break;
    case 1:
        result = "re";
        break;
    case 2:
        result = "mi";
        break;
    case 3:
        result = "fa";
        break;
    case 4:
        result = "sol";
        break;
    case 5:
        result = "la";
        break;
    case 6:
        result = "si";
        break;
    }

    return result + QString::number(m_octave);
}

int Note::getPitch() {
    return m_pitch;
}

int Note::getOctave() {
    return m_octave;
}

