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

    /* Creation de l'interface */
    createLayout();

    // Génération d'une partition
    m_staff = new Staff(4,"sol",0,5,4,5);
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
    m_reponse3 = new QLabel("Score : ?/?");
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

    m_reponse2->setText(m_noteNames[m_staff->getPitches(1)]);

    if (a_pitch == m_staff->getPitches(1)) {
        m_reponse2->setStyleSheet("QLabel {color:green;}");
        return true;
    } else {
        m_reponse2->setStyleSheet("QLabel {color:red;}");
        return false;
    }
}
