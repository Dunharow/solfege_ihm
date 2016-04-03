#include "fenetre.h"

Fenetre::Fenetre() : QWidget() {

    // Creation de l'interface
    createLayout();

    // Génération d'une note aléatoire
    Note m_note;
    m_image_note->setText(m_note.getNote());

    // Connection des signaux / slot
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(checkSolution(int)));

    signalMapper->setMapping(m_buttonDO,1);
    signalMapper->setMapping(m_buttonRE,2);
    signalMapper->setMapping(m_buttonMI,3);
    signalMapper->setMapping(m_buttonFA,4);
    signalMapper->setMapping(m_buttonSOL,5);
    signalMapper->setMapping(m_buttonLA,6);
    signalMapper->setMapping(m_buttonSI,7);

    connect(m_buttonDO, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(m_buttonRE, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(m_buttonMI, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(m_buttonFA, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(m_buttonSOL, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(m_buttonLA, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(m_buttonSI, SIGNAL(clicked()), signalMapper, SLOT(map()));
}

void Fenetre::createLayout() {
    // Widget de l'image
    m_image_note = new QLabel("Image de note");
    m_image_note->setAlignment(Qt::AlignHCenter);

    // Layout des boutons
    m_buttonDO = new QPushButton("DO");
    m_buttonRE = new QPushButton("RE");
    m_buttonMI = new QPushButton("MI");
    m_buttonFA = new QPushButton("FA");
    m_buttonSOL = new QPushButton("SOL");
    m_buttonLA = new QPushButton("LA");
    m_buttonSI = new QPushButton("SI");

    QHBoxLayout *layout_buttons = new QHBoxLayout;
    layout_buttons->addWidget(m_buttonDO);
    layout_buttons->addWidget(m_buttonRE);
    layout_buttons->addWidget(m_buttonMI);
    layout_buttons->addWidget(m_buttonFA);
    layout_buttons->addWidget(m_buttonSOL);
    layout_buttons->addWidget(m_buttonLA);
    layout_buttons->addWidget(m_buttonSI);

    // Widget du commentaire
    m_commentaire = new QLabel("");
    m_commentaire->setAlignment(Qt::AlignHCenter);

    // Assemblage de l'image et des boutons
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(m_image_note);
    layoutPrincipal->addLayout(layout_buttons);
    layoutPrincipal->addWidget(m_commentaire);
    setLayout(layoutPrincipal);

}

bool Fenetre::checkSolution(int a_pitch) {

    QString a_note;

    switch (a_pitch) {
    case 1:
        a_note = "do";
        break;
    default:
        a_note = "fa";
        break;
    }

    if (a_note == m_note.getPitch()) {
        m_commentaire->setText("C'est la bonne note :-)");
        return true;
    } else {
        m_commentaire->setText("C'est pas la bonne note :-(");
        return false;
    }
}
