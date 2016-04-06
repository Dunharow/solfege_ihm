#ifndef DEF_NOTE
#define DEF_NOTE

#include <string>
#include <stdlib.h>  // srand, rand
#include <time.h> // time to initialize random
#include <QString>

class Note {

private:
    int m_pitch;
	int m_octave;
    QString m_duration;
	bool m_dot;


public:
    Note(int min_pitch = 0, int max_pitch = 7, int min_octave = 1, int max_octave = 7);
    QString getNote(); // must change to image output
    int getPitch();
    int Note::getOctave();
};

#endif
