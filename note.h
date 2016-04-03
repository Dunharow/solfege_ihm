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
	Note(); // create a random note
    QString getNote();
    int getPitch();
};

#endif
