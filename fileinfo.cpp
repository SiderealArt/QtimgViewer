﻿#include "fileinfo.h"
Fileinfo::Fileinfo()
{
  this->setWindowTitle(tr("File Info"));
  this->setFixedSize(310,300);
  QLabel *fileNameLabel = new QLabel(tr("File Name:"));
  QLabel *pathLabel = new QLabel(tr("Path:"));
  QLabel *sizeLabel = new QLabel(tr("Size:"));
  QLabel *lastReadLabel = new QLabel(tr("Last Read:"));
  QLabel *lastModLabel = new QLabel(tr("Last Modified:"));
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(fileNameLabel);
  mainLayout->addWidget(pathLabel);
  mainLayout->addWidget(sizeLabel);
  mainLayout->addWidget(lastReadLabel);
  mainLayout->addWidget(lastModLabel);
}

Fileinfo::~Fileinfo()
{

}

