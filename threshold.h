#ifndef THRESHOLD_H
#define THRESHOLD_H
#include <QWidget>
#include <QSlider>
#include "label.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QClipboard>
class Threshold:public QWidget{
  Q_OBJECT
public:
  void getthreshold();
  int avg;
  Threshold(QImage mainWindowImage);
  ~Threshold();
  QImage *img;
  QImage *result;
  QSlider *slider;
  QPushButton *okButton;
  QClipboard *clipboard;
  QPushButton *cancelButton;
  QVBoxLayout *mainLayout;
  QHBoxLayout *buttonGroup;
  unsigned int mtx[256];
private slots:
  void cancel();
  void ok();
  void updateimg(int a);

};
#endif // THRESHOLD_H
