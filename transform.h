#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QDial>
#include <QSpacerItem>
#include <QImage>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
class Transform : public QWidget
{
    Q_OBJECT

public:
    Transform(QWidget *parent = nullptr);
    ~Transform();
    QLabel *inWin;
    QGroupBox *mirrorGroup;
    QCheckBox *hCheckBox;
    QCheckBox *vCheckBox;
    QPushButton *mirrorButton;
    QPushButton *saveButton;
    QDial *rotateDial;
    QSpacerItem *vSpacer;
    QHBoxLayout *mainLayout;
    QVBoxLayout *groupLayout;
    QVBoxLayout *leftLayout;
    QImage srcImg;
    QImage dstImg;
private slots:
    void mirrorImage();
    void rotateImage();
};
#endif // TRANSFORM_H
