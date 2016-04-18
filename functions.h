#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>

bool compareNotes(int pitchA, int pitchB, int octaveA, int octaveB);
int value2octave(int value, QString clef);
int value2pitch(int value, QString clef);
int note2value(int pitch, int octave, QString clef);

void echanger(double tableau[], int a, int b);
void echanger(int tableau[], int a, int b);
int idxMin(double tableau[], int debut, int fin);
int idxMin(int tableau[], int debut, int fin);
void trierTableau(double tableau[], int index[], int longueur);

#endif // FUNCTIONS_H
