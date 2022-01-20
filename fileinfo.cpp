#include "fileinfo.h"
Fileinfo::Fileinfo()
{
  this->setWindowTitle(tr("File Info"));
  this->setFixedHeight(200);
  fileNameLabel = new QLabel(tr("File Name: %1").arg(img.fileName()));
  pathLabel = new QLabel(tr("Path: %1").arg(img.path()));
  sizeLabel = new QLabel(tr("File Size: %1").arg(img.size()));
  lastReadLabel = new QLabel(tr("Last Read: %1").arg(img.lastRead().toString("yyyy/MM/dd hh:mm:ss")));
  lastModLabel = new QLabel(tr("Last Modified: %1").arg(img.lastModified().toString("yyyy/MM/dd hh:mm:ss")));
  widthLabel = new QLabel(tr("Size: %1"));
  heightLabel = new QLabel(tr("Size: %1"));
  megapixelLabel = new QLabel(tr("Size: %1"));
  ratioLabel = new QLabel(tr("Ratio: %1"));
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(fileNameLabel);
  mainLayout->addWidget(pathLabel);
  mainLayout->addWidget(sizeLabel);
  mainLayout->addWidget(lastReadLabel);
  mainLayout->addWidget(lastModLabel);
  mainLayout->addWidget(widthLabel);
  mainLayout->addWidget(heightLabel);
  mainLayout->addWidget(megapixelLabel);
  mainLayout->addWidget(ratioLabel);
}

Fileinfo::~Fileinfo()
{

}

