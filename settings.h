#ifndef SETTINGS_H
#define SETTINGS_H
#include <QWidget>
#include <QLocale>
#include <QTabWidget>
#include <QFileInfo>
#include <QSettings>
#include <QTranslator>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
class GeneralTab : public QWidget{
  Q_OBJECT
public:
  GeneralTab(QWidget *parent = nullptr);
  QComboBox *languagedropdown;
  QString m_currLang;
  QString m_langPath;
  QTranslator m_translator; // contains the translations for this application
  QTranslator m_translatorQt; // contains the translations for qt
private:
  void languagemenu();
  void loadLanguage(const QString& rLanguage);
private slots:
  void slotLanguageChanged(int);
};

class WindowTab : public QWidget{
  Q_OBJECT

public:
   WindowTab(QWidget *parent = nullptr);
};
class AppearenceTab : public QWidget{
  Q_OBJECT

public:
  AppearenceTab(QWidget *parent = nullptr);
};

class Settings:public QWidget{
  Q_OBJECT
public:
  Settings(QWidget *parent = nullptr);
  ~Settings();
  QSettings *settings;
  QVBoxLayout *mainLayout;
  QTabWidget *tabWidget;
  QDialogButtonBox *buttonbox;
private slots:


};
#endif
