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
    else           {return (value-1)/7 + 4;}
}

int value2pitch(int value, QString clef) {
    if (clef=="fa") {return value % 7 + 1;}
    else           {return value % 7 - 1;}
}

int note2value(int pitch, int octave, QString clef) {
    if (clef=="fa") {return (octave-2)*7 + pitch-1;}
    else            {return (octave-4)*6 + pitch+1;}
}

/// Fonctions pour les tableaux

void echanger(double tableau[], int a, int b) {
    double c = tableau[a];
    tableau[a] = tableau[b];
    tableau[b] = c;
}

void echanger(int tableau[], int a, int b) {
    int c = tableau[a];
    tableau[a] = tableau[b];
    tableau[b] = c;
}

int idxMin(double tableau[], int debut, int fin) {
    int idx = debut;
    int min = tableau[debut];

    for (int i=debut; i<fin; i++) {
        if (tableau[i]<min) {
            min = tableau[i];
            idx = i;
        }
    }

    return idx;
}

int idxMin(int tableau[], int debut, int fin) {
    int idx = debut;
    int min = tableau[debut];

    for (int i=debut; i<fin; i++) {
        if (tableau[i]<min) {
            min = tableau[i];
            idx = i;
        }
    }

    return idx;
}

void trierTableau(double tableau[], int index[], int longueur) {
    for (int i=0; i<longueur; i++) {
        echanger(tableau, i, idxMin(tableau,i,longueur));
        echanger(index, i, idxMin(index,i,longueur));
    }
}
