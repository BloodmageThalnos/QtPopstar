#include "main.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->setFont(QFont("Georgia",20));

    mainWindow* S=new mainWindow();

    return a.exec();
}
