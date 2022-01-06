#include "mainwindow.h"

#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile stylesheet(":/main/resources/theme/style.qss");
    stylesheet.open(QFile::ReadOnly);
    QString style(stylesheet.readAll());
   a.setStyleSheet(style);
    MainWindow w;
    w.show();
    return a.exec();
}
