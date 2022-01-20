#include "warmth.h"
Warmth::Warmth()
{
  slider = new QSlider(Qt::Horizontal);
  slider->setRange(-30,30);
  slider->setValue(0);
  QDialogButtonBox *buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(slider);
  mainLayout->addWidget(buttonbox);
  connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));
}

Warmth::~Warmth()
{
}

