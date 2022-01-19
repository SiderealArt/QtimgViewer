#include "adjustment.h"
Adjustment::Adjustment(QWidget *parent)
    : QDialog(parent)
{
  this->setWindowTitle(tr("Adjustment..."));
  this->setFixedSize(310,180);
  QLabel *brightness = new QLabel(tr("Brightness"));
  QLabel *contrast = new QLabel(tr("Contrast"));
  QLabel *saturation = new QLabel(tr("Saturation"));
  QDialogButtonBox *buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
  brightness_slider = new QSlider(Qt::Horizontal);
  brightness_slider->setRange(-100, 100);
  brightness_slider->setValue(0);
  contrast_slider = new QSlider(Qt::Horizontal);
  contrast_slider->setRange(-100, 100);
  contrast_slider->setValue(0);
 saturation_slider = new QSlider(Qt::Horizontal);
  saturation_slider->setRange(0, 100);
  saturation_slider->setValue(50);
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(brightness);
  mainLayout->addWidget(brightness_slider);
  mainLayout->addWidget(contrast);
  mainLayout->addWidget(contrast_slider);
  mainLayout->addWidget(saturation);
  mainLayout->addWidget(saturation_slider);
  mainLayout->addWidget(buttonbox);
}

Adjustment::~Adjustment()
{
}
