#ifndef SETTINGS_H
#define SETTINGS_H
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
class Settings:public QWidget{
  Q_OBJECT
public:
  Settings(QWidget *parent = nullptr);
  ~Settings();
  QVBoxLayout *mainLayout;
  QTabWidget *tabWidget;
private slots:

};
#endif
