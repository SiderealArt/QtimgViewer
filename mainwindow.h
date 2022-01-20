#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "about.h"
#include "label.h"
#include "settings.h"
#include "threshold.h"
#include "adjustment.h"
#include "fileinfo.h"
#include "camera.h"
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QSplitter>
#include <QImage>
#include <QMovie>
#include <QLabel>
#include <QScrollArea>
#include <QClipboard>
#include <QPainter>
#include <QUndoStack>
#include <QTreeView>
#include <QFileSystemModel>
#include <QNetworkAccessManager>
#include <QPrinter>
#include <QPrintDialog>
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
  int gcd(int,int);
friend class Label;
 private slots:
  void showOpenUrl();
  void openUrl(QUrl &url);
  void handleReply(QNetworkReply *reply);
  void handleimgbbReply(QNetworkReply *reply);
  void downloadFinished(QNetworkReply *reply);
    void showOpenFile();
    void colorpicker();
    void zoomIn();
    void grayscale();
    void invert();
    void camera();
    void imagefromcamera();
    void adjustment();
    void fileinfo();
    void brightness(int);
    void contrast(int);
    void cameraimage(int, QImage);
    void saturation(int);
    void zoomOut();
    void hflip();
    void vflip();
    void rotate();
    void aboutMenu();
    void settingsMenu();
    void fullscreen();
    void saveAs();
    void saveAsBMP();
    void saveAsJPG();
    void sepia();
    void warmth(int);
    void hue(int);
    void save();
    void copytoclipboard();
    void newWindow();
    void imgur();
    void imgbb();
    void replyFinished();
    void print();
    void threshold();
    void histogram();
    void updateimg(int);
    void ok();
    void cancel();
    void loadfileviatree(QModelIndex);
    void alwaysontop();
    void dirup();
    void dirhome();

 private:
    QSplitter *spliter;
    QFileSystemModel *model;
    QTreeView *tree;
    Threshold *thresholdWin;
    QPainter *painter;
    QPrinter printer;
    QPrintDialog pdialog;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *imgurupload;
    QUndoStack *undoStack = nullptr;
    QClipboard *clipboard;
    About *aWin;
    Settings *sWin;
    Fileinfo *fWin;
    Adjustment *adWin;
    Camera *cWin;
    QWidget *center;
    QMenu *fileMenu;
    QMenu *saveMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;
    QMenu *editMenu;
    QMenu *shareMenu;
    QMenu *toolsMenu;
    QScrollArea *imageScrollArea;
    QToolBar *fileTool;
    QToolBar *ImageTool;
    QToolBar *treeviewTool;
    QImage img;
    QMovie gif;
    QImage histogramimg;
    QImage result;
    QString filename;
    Label *imgWin;
    Label *tempWin;
    QLabel *histogramWin;
    QAction *dirupAction;
    QAction *dirhomeAction;
    QAction *sepiaAction;
    QAction *cameraAction;
    QAction *alwaysontopAction;
    QAction *histogramAction;
    QAction *thresholdAction;
    QAction *openFileAction;
    QAction *printAction;
    QAction *saveAction;
    QAction *imgurAction;
    QAction *imgbbAction;
    QAction *imageshackAction;
    QAction *grayscaleAction;
    QAction *invertAction;
    QAction *fileinfoAction;
    QAction *adjustmentAction;
    QAction *newWindowAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *saveAsAction;
    QAction *saveAsBMPAction;
    QAction *saveAsJPGAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *fullscreenAction;
    QAction *clipboardAction;
    QAction *exitAction;
    QAction *hFlipAction;
    QAction *vFlipAction;
    QAction *rotateAction;
    QAction *penAction;
    QAction *colorpickerAction;
    QAction *cursorAction;
    QAction *aboutAction;
    QAction *settingAction;
    QAction *checkupdateAction;
    QAction *openFromUrlAction;
    unsigned int mtx[256];
    int b =0;
};
#endif // MAINWINDOW_H
