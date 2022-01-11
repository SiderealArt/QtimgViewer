#include "threshold.h"
Threshold::Threshold()
{
  slider = new QSlider(Qt::Horizontal);
  slider->setRange(0, 255);
  QDialogButtonBox *buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(slider);
  mainLayout->addWidget(buttonbox);
}

Threshold::~Threshold()
{
}

