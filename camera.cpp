#include "camera.h"
#include "about.h"
Camera::Camera(QWidget *parent)
    : QDialog(parent)
{
  this->setWindowTitle(tr("Capture Photo"));
  this->setFixedSize(600,400);
  camera = new QCamera(this);
  session = new QMediaCaptureSession;
  imgcapture = new QImageCapture;
  preview = new QVideoWidget();
  mainLayout = new QVBoxLayout(this);
  preview->show();
  session->setCamera(camera);
  session->setVideoOutput(preview);
  session->setImageCapture(imgcapture);
  camera->start();
  capture = new QPushButton((""));
  capture->setIcon(QIcon(":/main/resources/icon/capture.png"));
  capture->setIconSize(QSize(35,35));
  mainLayout->addWidget(preview);
  mainLayout->addWidget(capture);
}

Camera::~Camera()
{
}
