#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>

bool compareNotes(int pitchA, int pitchB, int octaveA, int octaveB);
int value2octave(int value, QString clef);
int value2pitch(int value, QString clef);
int note2value(int pitch, int octave, QString clef);
#endif // FUNCTIONS_H
