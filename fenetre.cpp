#include "fenetre.h"

Fenetre::Fenetre() : QWidget() {

    // -- Initialisation
    m_noteNames[0] = "Do";
    m_noteNames[1] = "Ré";
    m_noteNames[2] = "Mi";
    m_noteNames[3] = "Fa";
    m_noteNames[4] = "Sol";
    m_noteNames[5] = "La";
    m_noteNames[6] = "Si";

    // -- Creation de l'interface
    createLayout();

    // -- Génération d'une note aléatoire
    Note m_note;
    m_image_note->setText(m_note.getNote());

    // -- Connection des signaux / slot
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(checkSolution(int))); // Connection du mapper au slot
    for (int i=0; i<7; i++) { // Connection des signaux boutons au mapper
        signalMapper->setMapping(m_buttons[i],i);
        connect(m_buttons[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
    }

}

void Fenetre::createLayout() {
    // Widget de l'image
    m_image_note = new QLabel("");
    m_image_note->setAlignment(Qt::AlignHCenter);

    // Layout des boutons
    QHBoxLayout *layout_buttons = new QHBoxLayout;
    for (int i=0; i<7; i++) {
        m_buttons[i] = new QPushButton(m_noteNames[i]);
        layout_buttons->addWidget(m_buttons[i]);
    }

    // Widget du bottom
    QHBoxLayout *layout_bottom = new QHBoxLayout;
    m_reponse1 = new QLabel("Réponse : ");
    m_reponse2 = new QLabel("");
    m_reponse3 = new QLabel("Score : 5/5");
    layout_bottom->addWidget(m_reponse1);
    layout_bottom->addWidget(m_reponse2);
    layout_bottom->insertStretch(2); // horizontal space
    layout_bottom->addWidget(m_reponse3);

    // Assemblage de l'image et des boutons
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(m_image_note);
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
