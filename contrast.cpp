#include "contrast.h"
Contrast::Contrast()
{
  slider = new QSlider(Qt::Horizontal);
  slider->setRange(100, -100);
  slider->setValue(0);
  QDialogButtonBox *buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(slider);
  mainLayout->addWidget(buttonbox);
  connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));
}

Contrast::~Contrast()
{
}

