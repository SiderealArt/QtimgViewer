#ifndef THRESHOLD_H
#define THRESHOLD_H
#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
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
  QHBoxLayout *buttonGroup;
private slots:
  void cancel();
  void ok();
};
#endif // THRESHOLD_H
