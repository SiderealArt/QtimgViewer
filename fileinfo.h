#ifndef FILEINFO_H
#define FILEINFO_H
#include <QWidget>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class Fileinfo:public QWidget{
  Q_OBJECT
public:
  Fileinfo();
  ~Fileinfo();
  QVBoxLayout *mainLayout;
  QDialogButtonBox *buttonbox;
};
#endif // FILEINFO_H
