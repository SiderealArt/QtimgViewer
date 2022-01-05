#include "settings.h"
Settings::Settings(QWidget *parent)
: QWidget(parent)
{
  QTabWidget *tabWidget = new QTabWidget();
  QVBoxLayout *mainLayout = new QVBoxLayout();
      mainLayout->addWidget(tabWidget);
      this->show();
//should have language, api keys, theme
}

Settings::~Settings()
{
}

