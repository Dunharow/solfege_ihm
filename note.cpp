#include "note.h"

using namespace std;

Note::Note() {

	srand((unsigned int)time(NULL));

    // RANDOM PITCH
    m_pitch = rand() % 7;

    // RANDOM OCTAVE
	m_octave = rand() % 6 + 2;

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


