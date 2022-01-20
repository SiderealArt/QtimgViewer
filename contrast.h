#ifndef CONTRAST_H
#define CONTRAST_H
#include <QDialog>
#include <QSlider>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class Contrast:public QDialog{
  Q_OBJECT
public:
  Contrast();
  ~Contrast();
  QSlider *slider;
  QVBoxLayout *mainLayout;
  QDialogButtonBox *buttonbox;
};
#endif // CONTRAST_H
