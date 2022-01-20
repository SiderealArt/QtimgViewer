#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QSettings>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings settings("config.ini",QSettings::IniFormat);
    QFile stylesheet(":/main/resources/theme/style.qss");
    stylesheet.open(QFile::ReadOnly);
    QString style(stylesheet.readAll());
    QTranslator myappTranslator;
    QString l = settings.value("language", "daruma_en.qm").toString();
    int t = settings.value("style", 1).toInt();

    if(t==1){
        a.setStyleSheet(style);
     }
    myappTranslator.load(l, QLatin1String(":/i18n"));
    a.installTranslator(&myappTranslator);
    MainWindow w;
    w.show();
    return a.exec();
}
