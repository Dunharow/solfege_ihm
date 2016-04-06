#include "fenetre.h"

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

    /* Génération d'une note aléatoire */
    Note m_note(1,6,4,5);
    m_image_clef->setPixmap(QPixmap(":/resources/images/clef_sol.png"));
    m_image_note->setPixmap(QPixmap(":/resources/images/sol_"+m_note.getNote()+".png"));
    setWindowTitle(m_note.getNote());

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
    m_image_clef = new QLabel("");
    m_image_note = new QLabel("");
    layout_partition->insertStretch(0); // horizontal space
    layout_partition->addWidget(m_image_clef);
    layout_partition->addWidget(m_image_note);
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

    m_reponse2->setText(m_noteNames[m_note.getPitch()]);

    if (a_pitch == m_note.getPitch()) {
        m_reponse2->setStyleSheet("QLabel {color:green;}");
        return true;
    } else {
        m_reponse2->setStyleSheet("QLabel {color:red;}");
        return false;
    }
}
