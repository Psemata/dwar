#include "mainwidget.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget mainWidget;
    mainWidget.setWindowState(Qt::WindowMaximized);

    mainWidget.setWindowIcon(QIcon(":classes/Images/red/Archer/sprite_archer_fight_red_1.png"));
    mainWidget.show();

    return app.exec();
}
