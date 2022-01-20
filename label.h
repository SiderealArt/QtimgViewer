#ifndef LABEL_H
#define LABEL_H
#include <QWidget>
#include <QLabel>
#include <QPoint>
#include <QMouseEvent>
#include <QImage>
#include <QDebug>
class Label: public QLabel{
public:
  Label(){
    setMouseTracking(true);
  }
  QImage a;
  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void drawLineTo(const QPoint &endPoint);
  bool drawing;
  QPoint lastPoint;
};

#endif // LABEL_H
