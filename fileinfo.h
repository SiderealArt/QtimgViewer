#ifndef FILEINFO_H
#define FILEINFO_H
#include <QDialog>
#include <QFileInfo>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class Fileinfo:public QDialog{
  Q_OBJECT
public:
  Fileinfo();
  ~Fileinfo();
  QVBoxLayout *mainLayout;
  QFileInfo img;
  QLabel *fileNameLabel;
  QLabel *pathLabel;
  QLabel *sizeLabel;
  QLabel *lastReadLabel;
  QLabel *lastModLabel;
  QLabel *widthLabel;
  QLabel *heightLabel;
  QLabel *megapixelLabel;
  QLabel *ratioLabel;
  QDialogButtonBox *buttonbox;
};
#endif // FILEINFO_H
