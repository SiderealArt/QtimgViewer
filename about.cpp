#include "about.h"
About::About(QWidget *parent)
    : QDialog(parent)
{
  this->setWindowTitle(tr("About"));
  this->setFixedSize(310,300);
  appIcon = new QLabel();
  version = new QLabel();
  website = new QLabel();
  about = new QLabel();
  appIcon->setPixmap(QPixmap(":/main/resources/icon/app.png").scaled(160,160));
  appIcon->show();
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(appIcon,1, Qt::AlignHCenter);
  const QString aboutstr = tr("Built with Qt %1 (%2)<br>"
                                    R"(Source code available under GPLv3 on <a style="color: #03A9F4; text-decoration:none;" href="https://github.com/SiderealArt/Daruma">GitHub</a><br>)"
                                    "Icon provided by Icon8<br>"
                                    "Copyright © %3 SiderealArt")
                                    .arg(QT_VERSION_STR, QSysInfo::buildCpuArchitecture(), "2021-2022");
  version->setText(tr("Version 1.34.2"));
  website->setText( tr(R"(<a style="color: #03A9F4; text-decoration:none;" href="https://daruma.siderealart.me/">daruma.siderealart.me</a>)"));
  website->setTextInteractionFlags(Qt::TextBrowserInteraction);
  website->setOpenExternalLinks(true);
  about->setText(aboutstr);
  about->setTextInteractionFlags(Qt::TextBrowserInteraction);
  about->setOpenExternalLinks(true);
  mainLayout->addWidget(version,1, Qt::AlignHCenter);
  mainLayout->addWidget(website,1, Qt::AlignHCenter);
  mainLayout->addWidget(about,1, Qt::AlignHCenter);
}

About::~About()
{
}
