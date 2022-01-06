#ifndef SETTINGS_H
#define SETTINGS_H
#include <QWidget>
#include <QTabWidget>
#include <QFileInfo>
#include <QSettings>
#include <QVBoxLayout>
class Settings:public QWidget{
  Q_OBJECT
public:
  Settings(QWidget *parent = nullptr);
  ~Settings();
  QSettings *settings;
  QVBoxLayout *mainLayout;
  QTabWidget *tabWidget;
private slots:

};
class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralTab(QWidget *parent = nullptr);
};
//! [0]


//! [1]
class WindowTab : public QWidget
{
    Q_OBJECT

public:
    explicit WindowTab(QWidget *parent = nullptr);
};
//! [1]


//! [2]
class AppearenceTab : public QWidget
{
    Q_OBJECT

public:
    explicit AppearenceTab(QWidget *parent = nullptr);
};
#endif
