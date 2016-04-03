#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QFont>
#include <QIcon>

#include "fenetre.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Fenetre fenetre;
    fenetre.show();

    return app.exec();
}
