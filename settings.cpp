#include "settings.h"
#include <QtWidgets>
Settings::Settings(QWidget *parent)
: QWidget(parent)
{
  this->setWindowTitle("Settings");
  this->setFixedSize(QSize(750, 400));
  QDialogButtonBox *buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel|QDialogButtonBox::Apply);
  QTabWidget *tabWidget = new QTabWidget();
  QSettings settings(QString("config.ini"), QSettings::IniFormat);
  QString someValue = settings.value("some/config/key", "default value if unset").toString();
  QVBoxLayout *mainLayout = new QVBoxLayout();
  tabWidget->addTab(new GeneralTab(), tr("General"));
  tabWidget->addTab(new AppearenceTab(), tr("Appearence"));
  tabWidget->addTab(new WindowTab(), tr("Window"));
  mainLayout->addWidget(tabWidget);
  mainLayout->addWidget(buttonbox);
  setLayout(mainLayout);
//should have language, api keys, theme
}

Settings::~Settings()
{
}

GeneralTab::GeneralTab(QWidget *parent)
    : QWidget(parent)
{
  QGroupBox *permissionsGroup = new QGroupBox(tr("Permissions"));

      QCheckBox *readable = new QCheckBox(tr("Readable"));


      QCheckBox *writable = new QCheckBox(tr("Writable"));


      QCheckBox *executable = new QCheckBox(tr("Executable"));


      QGroupBox *ownerGroup = new QGroupBox(tr("Ownership"));

      QLabel *ownerLabel = new QLabel(tr("Owner"));

      QLabel *groupLabel = new QLabel(tr("Group"));

      QVBoxLayout *permissionsLayout = new QVBoxLayout;
      permissionsLayout->addWidget(readable);
      permissionsLayout->addWidget(writable);
      permissionsLayout->addWidget(executable);
      permissionsGroup->setLayout(permissionsLayout);

      QVBoxLayout *ownerLayout = new QVBoxLayout;
      ownerLayout->addWidget(ownerLabel);
      ownerLayout->addWidget(groupLabel);
      ownerGroup->setLayout(ownerLayout);

      QVBoxLayout *mainLayout = new QVBoxLayout;
      mainLayout->addWidget(permissionsGroup);
      mainLayout->addWidget(ownerGroup);
      mainLayout->addStretch(1);
      setLayout(mainLayout);
}

AppearenceTab::AppearenceTab(QWidget *parent)
  : QWidget(parent)
{
  QLabel *fileNameLabel = new QLabel(tr("File Name:"));

      QLabel *pathLabel = new QLabel(tr("Path:"));

      QLabel *sizeLabel = new QLabel(tr("Size:"));

      QLabel *lastReadLabel = new QLabel(tr("Last Read:"));

      QLabel *lastModLabel = new QLabel(tr("Last Modified:"));

      QVBoxLayout *mainLayout = new QVBoxLayout;
      mainLayout->addWidget(fileNameLabel);
      mainLayout->addWidget(pathLabel);
      mainLayout->addWidget(sizeLabel);
      mainLayout->addWidget(lastReadLabel);
      mainLayout->addWidget(lastModLabel);
      mainLayout->addStretch(1);
      setLayout(mainLayout);
}

WindowTab::WindowTab(QWidget *parent)
  : QWidget(parent)
{

}
