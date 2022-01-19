#ifndef CAMERA_H
#define CAMERA_H
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCamera>
#include <QImageCapture>
#include <QVideoWidget>
#include <QMediaCaptureSession>
class Camera:public QDialog{
  Q_OBJECT
public:
  Camera(QWidget *parent = nullptr);
  ~Camera();
  QCamera *camera;
  QImage *img;
  QImageCapture *imgcapture;
  QMediaCaptureSession *session;
  QPushButton *capture;
  QVideoWidget *preview;
  QVBoxLayout *mainLayout;
};

#endif // CAMERA_H
