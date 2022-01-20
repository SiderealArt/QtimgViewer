#include "adjustment.h"
Adjustment::Adjustment(QWidget *parent)
  : QDialog(parent)
{
  this->setWindowTitle(tr("Adjustment..."));
  this->setFixedSize(310,250);
  QLabel *brightness = new QLabel(tr("Brightness"));
  QLabel *contrast = new QLabel(tr("Contrast"));
  QLabel *saturation = new QLabel(tr("Saturation"));
  QLabel *warmth = new QLabel(tr("Warmth"));
  QLabel *hue = new QLabel(tr("Hue"));
  QDialogButtonBox *buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
  brightness_slider = new QSlider(Qt::Horizontal);
  brightness_slider->setRange(-100, 100);
  brightness_slider->setValue(0);
  contrast_slider = new QSlider(Qt::Horizontal);
  contrast_slider->setRange(-100, 100);
  contrast_slider->setValue(0);
  saturation_slider = new QSlider(Qt::Horizontal);
  saturation_slider->setRange(-100, 100);
  saturation_slider->setValue(0);
  warmth_slider = new QSlider(Qt::Horizontal);
  warmth_slider->setRange(-30, 30);
  warmth_slider->setValue(0);
  hue_slider = new QSlider(Qt::Horizontal);
  hue_slider->setRange(0, 200);
  hue_slider->setValue(0);
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(brightness);
  mainLayout->addWidget(brightness_slider);
  mainLayout->addWidget(contrast);
  mainLayout->addWidget(contrast_slider);
  mainLayout->addWidget(saturation);
  mainLayout->addWidget(saturation_slider);
  mainLayout->addWidget(warmth);
  mainLayout->addWidget(warmth_slider);
  mainLayout->addWidget(hue);
  mainLayout->addWidget(hue_slider);
  mainLayout->addWidget(buttonbox);
  connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));
}

Adjustment::~Adjustment()
{
}
