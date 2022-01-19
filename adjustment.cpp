#include "adjustment.h"
Adjustment::Adjustment(QWidget *parent)
    : QDialog(parent)
{
  this->setWindowTitle(tr("Adjustment..."));
  this->setFixedSize(310,300);
  QLabel *brightness = new QLabel(tr("Brightness"));
  QLabel *contrast = new QLabel(tr("Contrast"));
  QLabel *saturation = new QLabel(tr("Saturation"));
  brightness_slider = new QSlider(Qt::Horizontal);
  brightness_slider->setRange(0, 255);
  contrast_slider = new QSlider(Qt::Horizontal);
  contrast_slider->setRange(0, 255);
 saturation_slider = new QSlider(Qt::Horizontal);
  saturation_slider->setRange(0, 255);
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(brightness);
  mainLayout->addWidget(brightness_slider);
  mainLayout->addWidget(contrast);
  mainLayout->addWidget(contrast_slider);
  mainLayout->addWidget(saturation);
  mainLayout->addWidget(saturation_slider);

}

Adjustment::~Adjustment()
{
}
