#include "Fenetre.h"

Fenetre::Fenetre() : QWidget() {

    /* Initialisation */
    m_noteNames[0] = "Do";
    m_noteNames[1] = "Ré";
    m_noteNames[2] = "Mi";
    m_noteNames[3] = "Fa";
    m_noteNames[4] = "Sol";
    m_noteNames[5] = "La";
    m_noteNames[6] = "Si";

    /* Initialisation du score et de la portée */
    m_score = new Score();
    m_staff = new Staff(STAFF_NB_NOTES,"sol",0,5,4,5);
    m_current_note = 0;

    /* Creation de l'interface */
    createLayout();
    m_image_clef->setPixmap(QPixmap(":/resources/images/clef_" + m_staff->getClef() + ".png"));
    for (int i=0; i<4; i++) {
        m_image_note[i]->setPixmap(QPixmap(":/resources/images/sol_"+m_staff->getNotes(i)+".png"));
    }

    /* Connection des signaux / slot */
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(checkSolution(int))); // Connection du mapper au slot
    for (int i=0; i<7; i++) {
        signalMapper->setMapping(m_buttons[i],i); // Creation du mapper
        connect(m_buttons[i], SIGNAL(clicked()), signalMapper, SLOT(map())); // Connection mapper/boutons
    }

}

void Fenetre::createLayout() {

    /* Layout de la partition */
    QHBoxLayout *layout_partition = new QHBoxLayout;
    layout_partition->insertStretch(0); // horizontal space
    m_image_clef = new QLabel("");
    layout_partition->addWidget(m_image_clef);
    for (int i=0; i<4; i++) {
        m_image_note[i] = new QLabel("");
        layout_partition->addWidget(m_image_note[i]);
    }
    layout_partition->insertStretch(-1); // horizontal space
    layout_partition->setSpacing(0);

    /* Layout des boutons */
    QHBoxLayout *layout_buttons = new QHBoxLayout;
    for (int i=0; i<7; i++) {
        m_buttons[i] = new QPushButton(m_noteNames[i]);
        layout_buttons->addWidget(m_buttons[i]);
    }

    /* Widget du bottom */
    QHBoxLayout *layout_bottom = new QHBoxLayout;
    m_reponse1 = new QLabel("Réponse : ");
    m_reponse2 = new QLabel("");
    m_reponse3 = new QLabel("Score : "+m_score->getScore());
    layout_bottom->addWidget(m_reponse1);
    layout_bottom->addWidget(m_reponse2);
    layout_bottom->insertStretch(2); // horizontal space
    layout_bottom->addWidget(m_reponse3);

    /* Assemblage de l'image et des boutons */
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(layout_partition);
    layoutPrincipal->addLayout(layout_buttons);
    layoutPrincipal->addLayout(layout_bottom);
    setLayout(layoutPrincipal);
}

bool Fenetre::checkSolution(int a_pitch) {

    int solution = m_staff->getPitches(m_current_note);

    m_reponse2->setText(m_noteNames[solution]);

    if (a_pitch == solution) {
        // Good answer
        m_score->correctAnswer(solution);
        m_reponse2->setStyleSheet("QLabel {color:green;}");
    } else {
        // Bad answer
        m_score->wrongAnswer(solution);
        m_reponse2->setStyleSheet("QLabel {color:red;}");
    }

    m_reponse3->setText("Score : " + m_score->getScore());

    m_current_note++;

    if (m_current_note==STAFF_NB_NOTES) {endGame();}

    return true;
}

void Fenetre::continueGame() {
    m_current_note = 0;

    delete m_staff;
    m_staff = new Staff(STAFF_NB_NOTES,"sol",0,5,4,5);

    m_image_clef->setPixmap(QPixmap(":/resources/images/clef_" + m_staff->getClef() + ".png"));
    for (int i=0; i<4; i++) {
        m_image_note[i]->setPixmap(QPixmap(":/resources/images/sol_"+m_staff->getNotes(i)+".png"));
    }
}

void Fenetre::endGame() {

    switch(QMessageBox::question(this, "Fin du jeu",
             "Le jeu est fini ! \nVotre score est " + m_score->getScore()+"\nVoulez-vous continuer ?",
             QMessageBox::Yes | QMessageBox::No)) {
    case QMessageBox::Yes:
        continueGame();
        break;

    case QMessageBox::No:
        qApp->quit();
        break;
    }
}
