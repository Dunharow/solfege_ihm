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
    Note(int min_pitch, int max_pitch, int min_octave, int max_octave);
    Note(unsigned int a_pitch, unsigned int an_octave);
    QString getNote(); // must change to image output
    int getPitch();
    int getOctave();
};

#endif
