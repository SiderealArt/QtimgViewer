#include "label.h"
#include <QPainter>
#include <QDebug>
void Label::mouseMoveEvent(QMouseEvent *event){
  if (event->button() == Qt::LeftButton) {
         lastPoint = event->pos();
         drawing = true;
     }
}
void Label::mousePressEvent(QMouseEvent *event){
  qDebug() << "down";
  if (event->button() == Qt::LeftButton) {
         lastPoint = event->pos();
         drawing = true;
     }
}
void Label::mouseReleaseEvent(QMouseEvent *event){
  if (event->button() == Qt::LeftButton && drawing) {
          drawLineTo(event->pos());
          drawing = false;
      }
}

void Label::drawLineTo(const QPoint &endPoint)
{
    a = this->pixmap().toImage();
    QPainter painter(&a);
    painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    int rad = (2 / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

