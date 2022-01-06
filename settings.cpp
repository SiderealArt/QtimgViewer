#include "settings.h"
Settings::Settings(QWidget *parent)
: QWidget(parent)
{
  this->setWindowTitle("Settings");
  this->setFixedSize(QSize(750, 400));
  QTabWidget *tabWidget = new QTabWidget();
  QSettings settings(QString("config.ini"), QSettings::IniFormat);
  QString someValue = settings.value("some/config/key", "default value if unset").toString();
  QVBoxLayout *mainLayout = new QVBoxLayout();
  tabWidget->addTab(new GeneralTab(), tr("General"));
  tabWidget->addTab(new AppearenceTab(), tr("Appearence"));
  tabWidget->addTab(new WindowTab(), tr("Window"));
  mainLayout->addWidget(tabWidget);
  setLayout(mainLayout);
//should have language, api keys, theme
}

Settings::~Settings()
{
}

GeneralTab::GeneralTab(QWidget *parent)
    : QWidget(parent)
{

}

AppearenceTab::AppearenceTab(QWidget *parent)
  : QWidget(parent)
{

}

WindowTab::WindowTab(QWidget *parent)
  : QWidget(parent)
{

}
