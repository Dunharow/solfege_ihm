#include "Staff.h"

Staff::Staff(unsigned int a_nbNotes) {
    int pitch_min, pitch_max, oct_min, oct_max;

    m_nbNotes = (a_nbNotes < NB_NOTE_MAX) ? a_nbNotes : NB_NOTE_MAX;

    switch (rand() %2) {
        case 0:
            m_clef = "sol";
            oct_min = 4;
            pitch_min = 0;
            oct_max = 5;
            pitch_max = 5;
            break;
        case 1:
            m_clef = "fa";
            pitch_min = 2;
            pitch_max = 0;
            oct_min =2;
            oct_max =4;
            break;
    }

    for (int i=0; i<m_nbNotes; i++) {
        m_notes[i] = new Note(pitch_min, pitch_max, oct_min, oct_max);
    }
}

Staff::Staff(int pitchTable[], int octaTable[], unsigned int a_nbNotes, QString a_clef) {

    m_nbNotes = (a_nbNotes < NB_NOTE_MAX) ? a_nbNotes : NB_NOTE_MAX;

    for (int i=0; i<m_nbNotes; i++) {
        m_notes[i] = new Note(pitchTable[i], octaTable[i]);
    }

    if (a_clef == "fa") {m_clef = "fa";}
    else                {m_clef = "sol";}
}

void Staff::setClef (QString a_clef) {
    if (a_clef=="sol" || a_clef=="fa") {
        m_clef = a_clef;
    }
}

QString Staff::getClef() {return m_clef;}

//void Staff::regenerate(unsigned int a_nbNotes, QString a_clef, int pitch_min, int pitch_max, int oct_min, int oct_max) {
//    m_nbNotes = (a_nbNotes < NB_NOTE_MAX) ? a_nbNotes : NB_NOTE_MAX;

//    m_clef = a_clef;

//    for (int i=0; i<m_nbNotes; i++) {
//        //m_notes[i]->regenerate(pitch_min, pitch_max, oct_min, oct_max);
//    }
//}

QString Staff::getNotes(int number) {

    if ((number > NB_NOTE_MAX) || (number<0)) {number = NB_NOTE_MAX;}

    return m_notes[number]->getNote();
}

int Staff::getPitches(int number) {

    if ((number > NB_NOTE_MAX) || (number<0)) {number = NB_NOTE_MAX;}

    return m_notes[number]->getPitch();
}

int Staff::getOctaves(int number) {

    if ((number > NB_NOTE_MAX) || (number<0)) {number = NB_NOTE_MAX;}

    return m_notes[number]->getOctave();
}

Staff::~Staff() {
    for (int i=0; i<m_nbNotes; i++) {
        delete m_notes[i];
    }
}
