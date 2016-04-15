#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QtWidgets>

#include <Note.h>
#include <Staff.h>

class Fenetre : public QWidget {

    Q_OBJECT

    private:
        // IHM
        QPushButton *m_buttons[7];
        QLabel *m_image_clef;
        QLabel *m_image_note[4];
        QLabel *m_reponse1;
        QLabel *m_reponse2;
        QLabel *m_reponse3;

        // VARIABLES UTILES
        Staff *m_staff;

        // OTHER
        QString m_noteNames[7];

    public:
        Fenetre();
        void createLayout();

    public slots:
        bool checkSolution(int a_pitch);
};

#endif
