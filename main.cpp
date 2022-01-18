#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QSettings>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile stylesheet(":/main/resources/theme/style.qss");
    stylesheet.open(QFile::ReadOnly);
    QString style(stylesheet.readAll());
    QTranslator myappTranslator;
    myappTranslator.load(QLocale(), QLatin1String("myapp"), QLatin1String("_"), QLatin1String(":/i18n"));
    a.installTranslator(&myappTranslator);
   //a.setStyleSheet(style);
    MainWindow w;
    w.show();
    return a.exec();
}
