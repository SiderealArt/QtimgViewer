#ifndef ADJUSTMENT_H
#define ADJUSTMENT_H
#include <QSlider>
#include <QLabel>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
class Adjustment:public QDialog{
  Q_OBJECT
public:
  Adjustment(QWidget *parent = nullptr);
  ~Adjustment();
  QSlider *brightness_slider;
  QSlider *contrast_slider;
  QSlider *saturation_slider;
  QVBoxLayout *mainLayout;
  QDialogButtonBox *buttonbox;
};
#endif // ADJUSTMENT_H
