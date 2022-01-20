#ifndef HUE_H
#define HUE_H
#include <QDialog>
#include <QSlider>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class Hue:public QDialog{
  Q_OBJECT
public:
  Hue();
  ~Hue();
  QSlider *slider;
  QVBoxLayout *mainLayout;
  QDialogButtonBox *buttonbox;
};
#endif // HUE_H
