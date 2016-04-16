#include "Fenetre.h"

// Constructeur de la fenêtre
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

// Créations des layouts et design de la fenêtre
void Fenetre::createLayout() {

    /* Layout de la partition */
    QGridLayout *layout_partitionGrid = new QGridLayout;

    m_imageClef = new QLabel("");
    layout_partitionGrid->addWidget(m_imageClef,0,0);

    for (int i=0; i<STAFF_SIZE; i++) {
        m_imageNote[i] = new QLabel("");
        m_textNote[i] = new QLabel("");
        layout_partitionGrid->addWidget(m_imageNote[i],0,i+1);
        layout_partitionGrid->addWidget(m_textNote[i],0,i+1);
    }
    layout_partitionGrid->setHorizontalSpacing(0);
    layout_partitionGrid->setVerticalSpacing(1000);
    layout_partitionGrid->setRowMinimumHeight(0,200);

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

    m_reponse1 = new QLabel("Réponse : ");
    m_reponse2 = new QLabel("");
    m_reponse3 = new QLabel("Score : "+m_score->getScore());

    layout_bottom->addWidget(m_reponse1);
    layout_bottom->addWidget(m_reponse2);
    layout_bottom->insertStretch(2); // horizontal space
    layout_bottom->addWidget(m_reponse3);

    /* Assemblage de l'image et des boutons */
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->insertStretch(0); // vertical space
    layoutPrincipal->addLayout(layout_partition);
    layoutPrincipal->addLayout(layout_buttons);
    layoutPrincipal->addLayout(layout_bottom);
    layoutPrincipal->insertStretch(-1); // vertical space
    setLayout(layoutPrincipal);
}

// Afficher la portée sans couleur
void Fenetre::showStaff() {

    m_imageClef->setPixmap(QPixmap(":/resources/images/clef_" + m_staff->getClef() + ".png"));

    for (int i=0; i<4; i++) {
        m_imageNote[i]->setPixmap(QPixmap(":/resources/images/"+m_staff->getClef()+"_"+m_staff->getNotes(i)+".png"));
    }
}

// Vérifier la solution avec le bouton
void Fenetre::checkSolution(int a_pitch) {

    int solution = m_staff->getPitches(m_currentNote);

    m_reponse2->setText(m_noteNames[solution]);

    if (a_pitch == solution) {
        // Good answer
        m_score->correctAnswer(solution);
        m_reponse2->setStyleSheet("QLabel {color:green;}");
        m_textNote[m_currentNote+1]->setText(m_noteNames[solution]);
        m_textNote[m_currentNote+1]->setStyleSheet("QLabel {color:green;}");
        m_imageNote[m_currentNote]->setPixmap(QPixmap(":/resources/images/"+m_staff->getClef()+"_"+m_staff->getNotes(m_currentNote)+"_vert.png"));
    } else {
        // Bad answer
        m_score->wrongAnswer(solution);
        m_reponse2->setStyleSheet("QLabel {color:red;}");
        m_textNote[m_currentNote+1]->setText(m_noteNames[solution]);
        m_textNote[m_currentNote+1]->setStyleSheet("QLabel {color:red;}");
        m_imageNote[m_currentNote]->setPixmap(QPixmap(":/resources/images/"+m_staff->getClef()+"_"+m_staff->getNotes(m_currentNote)+"_rouge.png"));
    }

    m_reponse3->setText("Score : " + m_score->getScore());

    m_currentNote++;

    if (m_currentNote==m_nbNotes) {endGame();}
}

// Triggered when last note is checked
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

// Reset the staff but not the score
void Fenetre::continueGame() {

    m_currentNote = 0;

    delete m_staff;
    m_staff = new Staff(m_nbNotes);
    showStaff();
}
