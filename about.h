#ifndef ABOUT_H
#define ABOUT_H
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
class About:public QWidget{
  Q_OBJECT
public:
  About(QWidget *parent = nullptr);
  ~About();
  QLabel *appIcon;
  QHBoxLayout *mainLayout;
private slots:

};

#endif // ABOUT_H
