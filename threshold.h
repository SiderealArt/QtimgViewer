#ifndef THRESHOLD_H
#define THRESHOLD_H
#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
class Threshold:public QWidget{
  Q_OBJECT
public:
  Threshold(QWidget *parent = nullptr);
  ~Threshold();
  QSlider *slider;
  QHBoxLayout *mainLayout;
private slots:

};
#endif // THRESHOLD_H
