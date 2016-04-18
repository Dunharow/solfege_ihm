#include "Fenetre.h"

/**
 *  Constructeur de la fenêtre
 */
Fenetre::Fenetre() : QWidget() {

    /* Initialisation */
    m_noteNames[0] = "Do";
    m_noteNames[1] = "Ré";
    m_noteNames[2] = "Mi";
    m_noteNames[3] = "Fa";
    m_noteNames[4] = "Sol";
    m_noteNames[5] = "La";
    m_noteNames[6] = "Si";

    m_nbNotes = 4;
    m_currentNote = 0;

    m_score = new Score();
    m_staff = new Staff(m_nbNotes);

    /* Creation de l'interface */
    createLayout();
    showStaff();

    /* Connection des signaux/slots */
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(checkSolution(int))); // Connection du mapper au slot
    for (int i=0; i<7; i++) {
        signalMapper->setMapping(m_buttons[i],i); // Creation du mapper
        connect(m_buttons[i], SIGNAL(clicked()), signalMapper, SLOT(map())); // Connection mapper/boutons
    }
}

/**
 *  Créations des layouts et design de la fenêtre
*/
void Fenetre::createLayout() {

    /* Layout de la partition */
    QGridLayout *layout_partitionGrid = new QGridLayout;

    m_imageClef = new QLabel("");
    layout_partitionGrid->addWidget(m_imageClef,0,0);

    for (int i=0; i<STAFF_SIZE; i++) {
        m_imageNote[i] = new QLabel("");
        m_textNote[i] = new QLabel("");
        layout_partitionGrid->addWidget(m_imageNote[i],0,i+1);
        layout_partitionGrid->addWidget(m_textNote[i],1,i+1);
        m_textNote[i]->setAlignment(Qt::AlignCenter);
    }
    layout_partitionGrid->setHorizontalSpacing(0);

    QHBoxLayout *layout_partition = new QHBoxLayout;
    layout_partition->insertStretch(0); // horizontal space
    layout_partition->addLayout(layout_partitionGrid);
    layout_partition->insertStretch(-1); // horizontal space

    /* Layout des boutons */
    QHBoxLayout *layout_buttons = new QHBoxLayout;

    for (int i=0; i<7; i++) {
        m_buttons[i] = new QPushButton(m_noteNames[i]);
        layout_buttons->addWidget(m_buttons[i]);
    }

    /* Widget du bottom */
    QHBoxLayout *layout_bottom = new QHBoxLayout;

    m_scoreLabel = new QLabel("");
    showScore();

    layout_bottom->insertStretch(0); // horizontal space
    layout_bottom->addWidget(m_scoreLabel);

    // Debug grid
    QGridLayout *m_debugGrid = new QGridLayout;

    for (int i=0; i<13; i++) {
        m_debugLabel[i][0] = new QLabel(QString::number(m_score->getPerc("sol",i)));
        m_debugGrid->addWidget(m_debugLabel[i][0],0,i);
        m_debugLabel[i][1] = new QLabel(QString::number(m_score->getPerc("fa",i)));
        m_debugGrid->addWidget(m_debugLabel[i][1],1,i);
    }

    /* Assemblage de l'image et des boutons */
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->insertStretch(0); // vertical space
    layoutPrincipal->addLayout(layout_partition);
    layoutPrincipal->addLayout(layout_buttons);
    layoutPrincipal->addLayout(layout_bottom);
    layoutPrincipal->addLayout(m_debugGrid);
    layoutPrincipal->insertStretch(-1); // vertical space
    setLayout(layoutPrincipal);


}

/**
 *  Afficher la portée sans couleur
*/
void Fenetre::showStaff() {

    m_imageClef->setPixmap(QPixmap(":/resources/images/clef_" + m_staff->getClef() + ".png"));

    for (int i=0; i<4; i++) {
        m_imageNote[i]->setPixmap(QPixmap(":/resources/images/"
            +QString::number(note2value(m_staff->getPitches(i), m_staff->getOctaves(i),m_staff->getClef()))+".png"));
    }
}

/**
 *  Afficher le score
*/
void Fenetre::showScore() {
    QString texte="Score : ";
    texte += QString::number(m_score->getCorrect()) +"/"+QString::number(m_score->getTotal()) + " ";

    if (m_score->getTotal()==0) {
        texte += "(0.0 %)";
    } else {
        texte += "(" + QString::number((double)m_score->getCorrect()/m_score->getTotal()*100,'f',1) + " %)";
    }

    m_scoreLabel->setText(texte);
}

/**
 *  Afficher la grille de débug
*/
void Fenetre::showDebug() {
    for (int i=0; i<13; i++) {
        m_debugLabel[i][0]->setText(QString::number(m_score->getPerc("sol",i)));
        m_debugLabel[i][1]->setText(QString::number(m_score->getPerc("fa",i)));
    }
}

/**
 *  Vérifier la solution depuis un bouton
*/
void Fenetre::checkSolution(int a_pitch) {

    int solutionPitch = m_staff->getPitches(m_currentNote);
    int solutionOcta =  m_staff->getOctaves(m_currentNote);
    QString solutionClef = m_staff->getClef();

    m_textNote[m_currentNote]->setText(m_noteNames[solutionPitch]);

    if (a_pitch == solutionPitch) {
        // Good answer
        m_score->correctAnswer(solutionOcta,solutionPitch,solutionClef);
        m_textNote[m_currentNote]->setStyleSheet("QLabel {color:green;}");
        m_imageNote[m_currentNote]->setPixmap(QPixmap(":/resources/images/"
            +QString::number(note2value(solutionPitch, solutionOcta, solutionClef))+"_vert.png"));
    } else {
        // Bad answer
        m_score->wrongAnswer(solutionOcta,solutionPitch,solutionClef);
        m_textNote[m_currentNote]->setStyleSheet("QLabel {color:red;}");
        m_imageNote[m_currentNote]->setPixmap(QPixmap(":/resources/images/"
            +QString::number(note2value(solutionPitch, solutionOcta, solutionClef))+"_rouge.png"));
    }

    showScore();
    showDebug();

    m_currentNote++;

    if (m_currentNote==m_nbNotes) {endOfStaff();}
}

/**
 *  Fin du jeu
*/
void Fenetre::endOfStaff() {

    switch(QMessageBox::question(this, "Fin du jeu",
             "Le jeu est fini ! \nVotre score est " + m_score->getScore()+"\nVoulez-vous continuer ?",
             QMessageBox::Yes | QMessageBox::No)) {
    case QMessageBox::Yes:
        createNewStaff();
        break;

    case QMessageBox::No:
        qApp->quit();
        break;
    }
}

/**
 *  Continuer le jeu
*/
void Fenetre::createNewStaff() {

    m_currentNote = 0;

    delete m_staff;
    m_score->makeRanking();

    QString a_clef;
    int pitchTable[4], octaTable[4];

    for (int i=0; i<4; i++) {
        pitchTable[i]=i;
        octaTable[i]=i;
    }

    if (rand() %2 == 0) { a_clef = "sol"; }
    else                { a_clef = "fa";}

    m_score->getRanking(pitchTable, octaTable,4,a_clef);

    m_staff = new Staff(pitchTable, octaTable,4,a_clef);
    showStaff();

    for (int i=0; i<STAFF_SIZE; i++) {
        m_textNote[i]->setText("");
    }
}
