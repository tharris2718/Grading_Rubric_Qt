#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    connect(GradeCalcpushButton, released(), Scorelabel, setText(grade()));

    return a.exec();
}
