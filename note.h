#ifndef DEF_NOTE
#define DEF_NOTE

#include <string>
#include <stdlib.h>  // srand, rand
#include <QString>

#include <functions.h>

class Note {

private:
    int m_pitch;
	int m_octave;
    int m_duration;
	bool m_dot;


public:
    Note(int min_pitch = 0, int max_pitch = 7, int min_octave = 1, int max_octave = 7);
    QString getNote(); // must change to image output
    int getPitch();
    int Note::getOctave();
};

#endif
