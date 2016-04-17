#include <functions.h>

bool compareNotes(int pitchA, int pitchB, int octaveA, int octaveB) {
    if (octaveA > octaveB) {
        return true;
    } else if (octaveA < octaveB) {
        return false;
    } else { // if octaves equal
        if (pitchA > pitchB) {
            return true;
        } else {
            return false;
        }
    }
}

int value2octave(int value, QString clef) {
    if (clef=="fa") {return (value+1)/7 + 2;}
    else           {return (value-1)/7 + 3;}
}

int value2pitch(int value, QString clef) {
    if (clef=="fa") {return value % 7 + 1;}
    else           {return value % 7 - 1;}
}

int note2value(int pitch, int octave, QString clef) {
    if (clef=="fa") {return (octave-2)*7 + pitch-1;}
    else            {return (octave-4)*6 + pitch+1;}
}

