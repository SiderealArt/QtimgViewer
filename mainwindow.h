#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "transform.h"

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
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
    QToolBar *fileTool;
    QToolBar *ImageTool;
    QAction *Pen;
    QAction *Cursor;
    QImage img;
    QString filename;
    QLabel *imgWin;
    QAction *openFileAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *exitAction;
    QAction *geometryAction;
};
#endif // MAINWINDOW_H
