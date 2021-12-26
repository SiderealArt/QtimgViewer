#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "about.h"
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
#include <QScrollArea>
#include <QClipboard>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createActions();
    void createMenus();
    void createToolbars();
    void loadFile(QString filename);
 private slots:
    void showOpenFile();
    void zoomIn();
    void zoomOut();
    void hflip();
    void vflip();
    void rotate();
    void aboutMenu();
    void fullscreen();
    void saveAs();
    void save();
    void copytoclipboard();
 private:
    QClipboard *clipboard;
    About *aWin;
    QWidget *center;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;
    QMenu *editMenu;
    QMenu *shareMenu;
    QMenu *toolsMenu;
    QScrollArea *imageScrollArea;
    QToolBar *fileTool;
    QToolBar *ImageTool;
    QImage img;
    QString filename;
    QLabel *imgWin;
    QAction *openFileAction;
    QAction *saveAction;
    QAction *imgurAction;
    QAction *imgbbAction;
    QAction *imageshackAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *saveAsAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *fullscreenAction;
    QAction *clipboardAction;
    QAction *exitAction;
    QAction *hFlipAction;
    QAction *vFlipAction;
    QAction *rotateAction;
    QAction *penAction;
    QAction *cursorAction;
    QAction *aboutAction;
    QAction *settingAction;
    QAction *checkupdateAction;
};
#endif // MAINWINDOW_H
