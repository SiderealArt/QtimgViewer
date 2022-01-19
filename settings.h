#ifndef SETTINGS_H
#define SETTINGS_H
#include <QWidget>
#include <QDialog>
#include <QLocale>
#include <QTabWidget>
#include <QFileInfo>
#include <QList>
#include <QSettings>
#include <QTranslator>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QDialogButtonBox>
class GeneralTab : public QWidget{
  Q_OBJECT
public:
  GeneralTab(QWidget *parent = nullptr);
  QComboBox *languagedropdown;
  QComboBox *stylesheetdropdown;
  QString m_currLang;
  QSettings *settings;
  QString m_langPath;
  QTranslator m_translator; // contains the translations for this application
  QTranslator m_translatorQt; // contains the translations for qt
private:
  void languagemenu();
  void loadLanguage(const QString& rLanguage);
  void switchTranslator(QTranslator& translator, const QString& filename);
private slots:
  void slotLanguageChanged(int);
  void stylesheetChanged(int);
};

class WindowTab : public QWidget{
  Q_OBJECT
public:
  WindowTab(QWidget *parent = nullptr);
  QString oldAccelText;
  QTableWidget *actionsTable;
  QList<QAction*> actionsList;
private slots:
  void recordAction(int row, int column);
  void validateAction(int row, int column);
};
class AppearenceTab : public QWidget{
  Q_OBJECT
public:
  AppearenceTab(QWidget *parent = nullptr);

};

class Settings:public QDialog{
  Q_OBJECT
public:
  Settings(QWidget *parent = nullptr);
  ~Settings();
  QVBoxLayout *mainLayout;
  QTabWidget *tabWidget;
  QDialogButtonBox *buttonbox;

private slots:


};
#endif
