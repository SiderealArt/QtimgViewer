#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "transform.h"

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
#include <QScrollArea>
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
    void showGeometryTransform();
 private:
    Transform *gWin;
    QWidget *center;
    QMenu *fileMenu;
    QScrollArea *imageScrollArea;
    QToolBar *fileTool;
    QToolBar *ImageTool;
    QImage img;
    QString filename;
    QLabel *imgWin;
    QAction *openFileAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *exitAction;
    QAction *geometryAction;
    QAction *hFlipAction;
    QAction *vFlipAction;
    QAction *penAction;
    QAction *cursorAction;
};
#endif // MAINWINDOW_H
