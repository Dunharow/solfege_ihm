#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QFont>
#include <QIcon>
#include <stdlib.h>  // srand, rand
#include <time.h> // time to initialize random

#include "Fenetre.h"

int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL)); // initialize random numbers

    QApplication app(argc, argv);

    Fenetre fenetre;
    fenetre.show();

    return app.exec();
}
