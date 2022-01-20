#ifndef SATURATION_H
#define SATURATION_H
#include <QDialog>
#include <QSlider>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class Saturation:public QDialog{
  Q_OBJECT
public:
  Saturation();
  ~Saturation();
  QSlider *slider;
  QVBoxLayout *mainLayout;
  QDialogButtonBox *buttonbox;
};
#endif // WARMTH_H
