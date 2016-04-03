#include "note.h"

using namespace std;

Note::Note() {

	srand((unsigned int)time(NULL));

    // RANDOM PITCH
	switch (rand() % 7 + 1) {
	case 1:
		m_pitch = "do";
		break;
	case 2:
		m_pitch = "re";
		break;
	case 3:
		m_pitch = "mi";
		break;
	case 4:
		m_pitch = "fa";
		break;
	case 5:
		m_pitch = "sol";
		break;
	case 6:
		m_pitch = "la";
		break;
	case 7:
		m_pitch = "si";
		break;
	}

    // RANDOM OCTAVE
	m_octave = rand() % 6 + 2;

    // OTHERS
	m_duration = 4;
	m_dot = false;
}

QString Note::getNote() {
    return m_pitch + QString::number(m_octave);
}

QString Note::getPitch() {
    return m_pitch;
}
