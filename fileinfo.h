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
  QDialogButtonBox *buttonbox;
};
#endif // FILEINFO_H
