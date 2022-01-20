#ifndef WARMTH_H
#define WARMTH_H
#include <QDialog>
#include <QSlider>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class Warmth:public QDialog{
  Q_OBJECT
public:
  Warmth();
  ~Warmth();
  QSlider *slider;
  QVBoxLayout *mainLayout;
  QDialogButtonBox *buttonbox;
};
#endif // WARMTH_H
