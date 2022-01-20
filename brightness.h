#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H
#include <QDialog>
#include <QSlider>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class Brightness:public QDialog{
  Q_OBJECT
public:
  Brightness();
  ~Brightness();
  QSlider *slider;
  QVBoxLayout *mainLayout;
  QDialogButtonBox *buttonbox;
};
#endif // BRIGHTNESS_H
