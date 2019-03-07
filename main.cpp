#include <QtWidgets/QApplication>
#include"game.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game DarkEcho;
    DarkEcho.run();
    return a.exec();
}
