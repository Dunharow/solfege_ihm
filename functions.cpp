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
