#include "threshold.h"
Threshold::Threshold(Label *mainWindowImage)
{
  img = new QImage(mainWindowImage->pixmap().toImage());
  result = new QImage();
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

void Threshold::updateimg(int a){
  int tmp;
  *result = QImage(QSize(img->width(),img->height()),QImage::Format_Mono);
  for(int j=0;j<img->height();j++){
      for(int i=0;i<img->width();i++){
          tmp = (qGray(img->pixel(i,j))>a)?1:0;
          result->setPixel(i,j,tmp);
        }
    }
  clipboard->setImage(*result);
}
