#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#define STAFF_SIZE 10

#include <QApplication>
#include <QtWidgets>

#include <Note.h>
#include <Staff.h>
#include <Score.h>

class Fenetre : public QWidget {

    Q_OBJECT

    private:
        // IHM
        QPushButton *m_buttons[7];
        QLabel *m_imageClef;
        QLabel *m_imageNote[STAFF_SIZE];
        QLabel *m_textNote[STAFF_SIZE];
        QLabel *m_scoreLabel;
        QLabel *m_debugLabel[13][2];

        // VARIABLES UTILES
        Staff *m_staff;
        Score *m_score;
        int m_currentNote;
        int m_nbNotes;

        // OTHER
        QString m_noteNames[7];

    public:
        Fenetre();
        void createLayout();
        void showStaff();
        void showScore();
        void showDebug();
        void endOfStaff();
        void createNewStaff();

    public slots:
        void checkSolution(int a_pitch);
};

#endif
