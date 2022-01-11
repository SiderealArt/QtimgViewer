#ifndef THRESHOLD_H
#define THRESHOLD_H
#include <QWidget>
#include <QSlider>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class Threshold:public QWidget{
  Q_OBJECT
public:
  Threshold();
  ~Threshold();
  QSlider *slider;
  QPushButton *okButton;
  QPushButton *cancelButton;
  QVBoxLayout *mainLayout;
  QDialogButtonBox *buttonbox;
};
#endif // THRESHOLD_H
