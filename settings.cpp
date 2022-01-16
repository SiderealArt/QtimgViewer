#include "settings.h"
#include <QtWidgets>
#include <QCoreApplication>
#include <QDebug>
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
  QComboBox *languagedropdown = new QComboBox();
  connect(languagedropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(slotLanguageChanged(int)));
  QVBoxLayout *permissionsLayout = new QVBoxLayout;
  permissionsLayout->addWidget(readable);
  permissionsLayout->addWidget(writable);
  permissionsLayout->addWidget(executable);
  permissionsGroup->setLayout(permissionsLayout);
  QVBoxLayout *ownerLayout = new QVBoxLayout;
  ownerLayout->addWidget(languagedropdown);
  ownerGroup->setLayout(ownerLayout);
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(permissionsGroup);
  mainLayout->addWidget(ownerGroup);
  mainLayout->addStretch(1);
  languagemenu();
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

void GeneralTab::languagemenu(){

   QString defaultLocale = QLocale::system().name();
   defaultLocale.truncate(defaultLocale.lastIndexOf('_'));
   m_langPath = QApplication::applicationDirPath();
   m_langPath.append("/i18n");
   QDir dir(m_langPath);
   QStringList fileNames = dir.entryList(QStringList("daruma_*.qm"));
   qDebug() << "path: " << m_langPath << fileNames.size();
   for (int i = 0; i < fileNames.size(); ++i) {
    QString locale;
    qDebug() << fileNames[i];
    locale = fileNames[i];
    locale.truncate(locale.lastIndexOf('.'));
    locale.remove(0, locale.lastIndexOf('_') + 1);
    QString lang = QLocale::languageToString(QLocale(locale).language());
     qDebug() << lang;
    QIcon ico(QString("%1/%2.png").arg(m_langPath).arg(locale));
    languagedropdown->addItem(ico,lang);
   }
}

void switchTranslator(QTranslator& translator, const QString& filename) {
 QCoreApplication::removeTranslator(&translator);
QString path = QApplication::applicationDirPath();
        path.append("/i18n/");
 if(translator.load(path + filename))
  QCoreApplication::installTranslator(&translator);
}

void GeneralTab::loadLanguage(const QString& rLanguage) {
 if(m_currLang != rLanguage) {
  m_currLang = rLanguage;
  QLocale locale = QLocale(m_currLang);
  QLocale::setDefault(locale);
  QString languageName = QLocale::languageToString(locale.language());
  switchTranslator(m_translator, QString("daruma_%1.qm").arg(rLanguage));
  switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
 }
}

void GeneralTab::slotLanguageChanged(int index)
{
  loadLanguage(this->languagedropdown->currentText());
}
