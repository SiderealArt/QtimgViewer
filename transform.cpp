#include "transform.h"
#include <QPixmap>
Transform::Transform(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    leftLayout = new QVBoxLayout(this);
    mirrorGroup = new QGroupBox("Mirror",this);
    groupLayout = new QVBoxLayout(mirrorGroup);
    hCheckBox = new QCheckBox("Horizontal",mirrorGroup);
    vCheckBox = new QCheckBox("Vertical",mirrorGroup);
    mirrorButton = new QPushButton("Run", mirrorGroup);
    saveButton = new QPushButton("Save");
    hCheckBox->setGeometry(QRect(13,28,87,19));
    vCheckBox->setGeometry(QRect(13,54,87,19));
    mirrorButton->setGeometry(QRect(13,80,93,28));
    groupLayout->addWidget(hCheckBox);
    groupLayout->addWidget(vCheckBox);
    groupLayout->addWidget(mirrorButton);
    leftLayout->addWidget(mirrorGroup);
    leftLayout->addWidget(saveButton);
    rotateDial = new QDial(this);
    rotateDial->setNotchesVisible(true);
    vSpacer = new QSpacerItem(20,58,QSizePolicy::Minimum,QSizePolicy::Expanding);
    leftLayout->addWidget(rotateDial);
    leftLayout->addItem(vSpacer);
    mainLayout->addLayout(leftLayout);
    inWin = new QLabel(this);
    inWin->setScaledContents(true);
    QPixmap *initPixmap = new QPixmap(300,200);
    initPixmap->fill(QColor(255,255,255));
    inWin->setPixmap(*initPixmap);
    inWin->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    if(srcImg.isNull()){
        QPixmap *initPixmap = new QPixmap(300,200);
        inWin->setPixmap(*initPixmap);
    }
    mainLayout->addWidget(inWin);
    connect(mirrorButton,SIGNAL(clicked()),this,SLOT(mirrorImage()));
    connect(rotateDial,SIGNAL(valueChanged(int)),this,SLOT(rotateImage()));
}

Transform::~Transform()
{
}

void Transform::mirrorImage(){
    bool H,V;
    if(srcImg.isNull()){
        return;
    }
    H=hCheckBox->isChecked();
    V = vCheckBox->isChecked();
    dstImg = srcImg.mirrored(H,V);
    inWin->setPixmap(QPixmap::fromImage(dstImg));
    srcImg = dstImg;
}
void Transform::rotateImage(){
    QTransform t;
    int a;
    if(srcImg.isNull()){
        return;
    }
    a = rotateDial->value();
    t.rotate(a);
    dstImg = srcImg.transformed(t);
    inWin->setPixmap(QPixmap::fromImage(dstImg));
}
