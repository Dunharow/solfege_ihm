#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QSignalMapper>

#include <note.h>

class Fenetre : public QWidget {

    Q_OBJECT

    private:
        // IHM
        QPushButton *m_buttons[7];
        QLabel *m_image_note;
        QPushButton *m_buttonDO;
        QPushButton *m_buttonRE;
        QPushButton *m_buttonMI;
        QPushButton *m_buttonFA;
        QPushButton *m_buttonSOL;
        QPushButton *m_buttonLA;
        QPushButton *m_buttonSI;
        QLabel *m_reponse1;
        QLabel *m_reponse2;
        QLabel *m_reponse3;

        // VARIABLES UTILES
        Note m_note;

        // OTHER
        QString m_noteNames[7];

    public:
        Fenetre();
        void createLayout();

    public slots:
        bool checkSolution(int a_pitch);
};

#endif
