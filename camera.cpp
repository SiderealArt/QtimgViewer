#include "camera.h"
#include "about.h"
Camera::Camera(QWidget *parent)
    : QDialog(parent)
{
  this->setWindowTitle(tr("Capture Photo"));
  this->setFixedSize(310,300);
  camera = new QCamera(this);
  capture = new QPushButton(tr("Capture"));
  capture->setIcon(":/main/resources/icon/capture.png");
  capture->setIconSize(QSize(50,50));
}

About::~About()
{
}
