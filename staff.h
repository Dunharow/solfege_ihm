#ifndef STAFF_H
#define STAFF_H

#define NB_NOTE_MAX 10
#include <Note.h>

class Staff {
private:
    QString m_clef;
    Note* m_notes[NB_NOTE_MAX];
    int m_nbNotes;

public:
    Staff(unsigned int m_nbNotes=4, QString m_clef="sol", int pitch_min=0, int pitch_max=6, int oct_min=4, int oct_max=6);
    void regenerate(unsigned int m_nbNotes=4, QString m_clef="sol", int pitch_min=0, int pitch_max=6, int oct_min=4, int oct_max=6);
    void setClef(QString a_clef);
    QString getClef();
    int getPitches(int number=-1);
    QString getNotes(int number=-1);
    ~Staff(); // destructeur
};

#endif // STAFF_H
