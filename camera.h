#ifndef CAMERA_H
#define CAMERA_H
#include <QVBoxLayout>
#include <QPushButton>
#include <QCamera>
#include <QImageCapture>
class Camera:public QDialog{
  Q_OBJECT
public:
  Camera(QWidget *parent = nullptr);
  ~Camera();
  QCamera *camera;
  QImage *img;
  QImageCapture *session;
  QPushButton *capture;
  QVBoxLayout *mainLayout;
};

#endif // CAMERA_H
