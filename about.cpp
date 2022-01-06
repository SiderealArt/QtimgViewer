#include "about.h"
About::About(QWidget *parent)
    : QWidget(parent)
{
  this->setWindowTitle("About");
  appIcon = new QLabel();
  appIcon->setPixmap(QPixmap(":/main/resources/icon/app.png"));
  appIcon->show();
  mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(appIcon);
}

About::~About()
{
}
