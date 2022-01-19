#ifndef ABOUT_H
#define ABOUT_H
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
class About:public QDialog{
  Q_OBJECT
public:
  About(QWidget *parent = nullptr);
  ~About();
  QLabel *appIcon;
  QLabel *about;
  QLabel *website;
  QLabel *version;
  QVBoxLayout *mainLayout;
};

#endif // ABOUT_H
