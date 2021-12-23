#include "mainwindow.h"
#include "transform.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Image Editor");
    center = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(center);
    imgWin = new QLabel();
    QPixmap *initPixmap = new QPixmap(300,200);
    gWin = new Transform();
    initPixmap->fill(QColor(255,255,255));
    imgWin->resize(300,200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(center);
    createActions();
    createMenus();
    createToolbars();
}

MainWindow::~MainWindow()
{
}
void MainWindow::createActions(){
    Pen = new QAction("Pen");
    Pen->setIcon(QIcon("C:/Users/user/Desktop/ImageEditor/pen.png"));
    openFileAction = new QAction("&Open File",this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip("Open Image File");
    openFileAction->setIcon(QIcon("C:/Users/user/Desktop/ImageEditor/openfile.png"));
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(showOpenFile()));
    exitAction = new QAction("&Quit",this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip("Quit Application");
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    zoomInAction = new QAction("Zoom &In",this);
    zoomInAction->setShortcut(tr("Ctrl+I"));
    zoomInAction->setIcon(QIcon("C:/Users/user/Desktop/ImageEditor/zoomin.png"));
     connect(zoomInAction,SIGNAL(triggered()),this,SLOT(zoomIn()));
    zoomOutAction = new QAction("Zoom O&ut",this);
    zoomOutAction->setShortcut(tr("Ctrl+U"));
    zoomOutAction->setIcon(QIcon("C:/Users/user/Desktop/ImageEditor/zoomout.png"));
     connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(zoomOut()));
     connect(exitAction,SIGNAL(triggered()),imgWin,SLOT(close()));
    geometryAction = new QAction("Geometry Transform",this);
    geometryAction->setShortcut(tr("Ctrl+G"));
    geometryAction->setStatusTip("Image Geometry Transform");
    connect(geometryAction,SIGNAL(triggered()),this,SLOT(showGeometryTransform()));
    connect(exitAction,SIGNAL(triggered()),gWin,SLOT(close()));
}

 void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(geometryAction);
    fileMenu->addAction(zoomInAction);
    fileMenu->addAction(zoomOutAction);
    fileMenu->addAction(exitAction);
}
void MainWindow::createToolbars(){
    fileTool = addToolBar("File");
    fileTool->addAction(openFileAction);
     fileTool->addAction(geometryAction);
    fileTool->addAction(zoomInAction);
    fileTool->addAction(zoomOutAction);
    ImageTool = addToolBar("Image");
    ImageTool->addAction(Pen);
}
void MainWindow::loadFile(QString filename){
    QByteArray b = filename.toLatin1();
    img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::showOpenFile(){
    filename = QFileDialog::getOpenFileName(this, "Open Image",".",";;png(*.png)"";;Jpeg(*.jpg");
    if(!filename.isEmpty()){
        if(!img.isNull()){
            loadFile(filename);
        }else{
            MainWindow *newIPWin = new MainWindow();
            newIPWin->show();
            newIPWin->loadFile(filename);
        }
    }
}
void MainWindow::zoomIn(){
  MainWindow *newWin = new MainWindow();
  newWin->imgWin->setPixmap(QPixmap::fromImage(img.scaled(img.width()*2,img.height()*2)));
  newWin->imgWin->resize(img.width()*2,img.height()*2);
  newWin->setWindowTitle("Result");
  newWin->fileTool->close();
  newWin->show();
}

void MainWindow::zoomOut(){
MainWindow *newWin = new MainWindow();
newWin->imgWin->setPixmap(QPixmap::fromImage(img.scaled(img.width()/2,img.height()/2)));
newWin->imgWin->resize(img.width()/2,img.height()/2);
newWin->setWindowTitle("Result");
newWin->fileTool->close();
newWin->show();
}

void MainWindow::showGeometryTransform(){
    if(!img.isNull())
        gWin->srcImg = img;
    gWin->inWin->setPixmap(QPixmap::fromImage(gWin->srcImg));
    gWin->show();
}
