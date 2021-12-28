#include "threshold.h"
Threshold::Threshold()
{
  okButton = new QPushButton("Ok");
  cancelButton = new QPushButton("Cancel");
  slider = new QSlider(Qt::Horizontal);
  slider->setRange(0, 255);
  mainLayout = new QVBoxLayout(this);
  buttonGroup = new QHBoxLayout(this);
  mainLayout->addWidget(slider);
  mainLayout->addLayout(buttonGroup);
  buttonGroup->addWidget(okButton);
  buttonGroup->addWidget(cancelButton);
}

Threshold::~Threshold()
{
}

void Threshold::ok(){

}
void Threshold::cancel(){

}
