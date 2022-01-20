#include "fileinfo.h"
Fileinfo::Fileinfo()
{
  this->setWindowTitle(tr("File Info"));
  this->setFixedHeight(200);
  QLabel *fileNameLabel = new QLabel(tr("File Name: %1").arg(img.fileName()));
  QLabel *pathLabel = new QLabel(tr("Path: %1").arg(img.path()));
  QLabel *sizeLabel = new QLabel(tr("File Size: %1").arg(img.size()));
  QLabel *lastReadLabel = new QLabel(tr("Last Read: %1").arg(img.lastRead().toString("yyyy/MM/dd hh:mm:ss")));
  QLabel *lastModLabel = new QLabel(tr("Last Modified: %1").arg(img.lastModified().toString("yyyy/MM/dd hh:mm:ss")));
  QLabel *pixelLabel = new QLabel(tr("Size: %1"));
  QLabel *ratioLabel = new QLabel(tr("Ratio: %1"));
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(fileNameLabel);
  mainLayout->addWidget(pathLabel);
  mainLayout->addWidget(sizeLabel);
  mainLayout->addWidget(lastReadLabel);
  mainLayout->addWidget(lastModLabel);
  mainLayout->addWidget(pixelLabel);
  mainLayout->addWidget(ratioLabel);
}

Fileinfo::~Fileinfo()
{

}

