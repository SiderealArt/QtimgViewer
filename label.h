#ifndef LABEL_H
#define LABEL_H
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
class Label: public QLabel{
public:
  Label(){
    setMouseTracking(true);
    }

  void mousePressEvent(QMouseEvent *e) {
    // vvv That's where the magic happens
if (e->button() == Qt::LeftButton) {
            QPoint pos = e->pos();
            // ^^^
            qDebug()<<pos.x() << " " <<pos.y();
  }
  }
  void mouseMoveEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton) {
                QPoint pos = e->pos();
                // ^^^
                qDebug()<<pos.x() << " " <<pos.y();
      }
  }
  void mouseReleaseEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton) {
                QPoint pos = e->pos();
                // ^^^
                qDebug()<<pos.x() << " " <<pos.y();
      }
  }
};

#endif // LABEL_H
