#include "settings.h"
#include <QtWidgets>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
Settings::Settings(QWidget *parent)
  : QWidget(parent)
{
  this->setWindowTitle("Settings");
  this->setFixedSize(QSize(450, 250));
  QDialogButtonBox *buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel|QDialogButtonBox::Apply);
  QTabWidget *tabWidget = new QTabWidget();

  QVBoxLayout *mainLayout = new QVBoxLayout();
  tabWidget->addTab(new GeneralTab(), tr("General"));
  /* tabWidget->addTab(new AppearenceTab(), tr("Appearence"));
  tabWidget->addTab(new WindowTab(), tr("Window"));*/
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

  /* QGroupBox *permissionsGroup = new QGroupBox(tr("Permissions"));
  QCheckBox *readable = new QCheckBox(tr("Readable"));
  QCheckBox *writable = new QCheckBox(tr("Writable"));
  QCheckBox *executable = new QCheckBox(tr("Executable"));*/
  QGroupBox *ownerGroup = new QGroupBox(tr(""));
  languagedropdown = new QComboBox();
  stylesheetdropdown = new QComboBox();
  stylesheetdropdown->addItem(tr("White"));
  stylesheetdropdown->addItem(tr("Black"));
  connect(stylesheetdropdown,SIGNAL(currentIndexChanged(int)), this, SLOT(stylesheetChanged(int)));
  const auto entries = QDir(":/i18n/").entryList();
  for (auto entry : entries)
    {
      if(entry.right(2) == "qm"){
          entry.remove(0, 7);
          entry.remove(entry.length()-3, 3);
          QLocale locale(entry);
          const QString langString = locale.nativeLanguageName() + " (" + entry + ")";
          languagedropdown->addItem(langString,entry);
        }
    }
  connect(languagedropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotLanguageChanged(int)));
  /*QVBoxLayout *permissionsLayout = new QVBoxLayout;
  permissionsLayout->addWidget(readable);
  permissionsLayout->addWidget(writable);
  permissionsLayout->addWidget(executable);
  permissionsGroup->setLayout(permissionsLayout);*/

  QVBoxLayout *ownerLayout = new QVBoxLayout;
  ownerLayout->addWidget(languagedropdown);
  ownerLayout->addWidget(stylesheetdropdown);
  ownerGroup->setLayout(ownerLayout);
  QVBoxLayout *mainLayout = new QVBoxLayout;
  //mainLayout->addWidget(permissionsGroup);
  mainLayout->addWidget(ownerGroup);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}

AppearenceTab::AppearenceTab(QWidget *parent)
  : QWidget(parent)
{
  QVBoxLayout *mainLayout = new QVBoxLayout;
  setLayout(mainLayout);
}

WindowTab::WindowTab(QWidget *parent)
  : QWidget(parent)
{

}

void GeneralTab::switchTranslator(QTranslator& translator, const QString& filename) {

  QSettings *settings = new QSettings(QString("config.ini"), QSettings::IniFormat);
  QCoreApplication::removeTranslator(&translator);
  QString path = QApplication::applicationDirPath();
  path.append("/i18n/");
  if(translator.load(filename,":/i18n")){
      settings->setValue("language", filename);
    }
}

void GeneralTab::loadLanguage(const QString& rLanguage) {
  if(m_currLang != rLanguage) {
      m_currLang = rLanguage;
      QLocale locale = QLocale(m_currLang);
      QLocale::setDefault(locale);
      switchTranslator(m_translator, QString("daruma_%1.qm").arg(rLanguage));
    }
}

void GeneralTab::slotLanguageChanged(int index)
{
  Q_UNUSED(index)
  loadLanguage(languagedropdown->currentData().toString());
}

void GeneralTab::stylesheetChanged(int index){
  QSettings *settings = new QSettings(QString("style.ini"), QSettings::IniFormat);
  settings->setValue("style", index);
}
