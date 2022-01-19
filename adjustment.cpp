#include "adjustment.h"
Adjustment::Adjustment(QWidget *parent)
    : QDialog(parent)
{
  this->setWindowTitle(tr("Adjustment..."));
  this->setFixedSize(310,300);
  QLabel *brightness = new QLabel(tr("Brightness"));
  QLabel *contrast = new QLabel(tr("Contrast"));
  QLabel *saturation = new QLabel(tr("Saturation"));
  mainLayout = new QVBoxLayout(this);
}

Adjustment::~Adjustment()
{
}
