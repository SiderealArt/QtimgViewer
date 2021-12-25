#include "mainwindow.h"
#include "transform.h"
#include "about.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Image Editor");
    setWindowIcon(QIcon(":/main/resources/icon/app.png"));
    center = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(center);
    imgWin = new QLabel();
    QPixmap *initPixmap = new QPixmap(300,200);
    gWin = new Transform();
    aWin = new About();
    initPixmap->fill(QColor(255,255,255));
    imgWin->resize(300,200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    QScrollArea *imageScrollArea = new QScrollArea();
       imageScrollArea->setAlignment(Qt::AlignCenter);
       imageScrollArea->setFrameShape(QFrame::NoFrame);
       imageScrollArea->setWidget(imgWin);
    mainLayout->addWidget(imageScrollArea);
    setCentralWidget(center);
    createActions();
    createMenus();
    createToolbars();
}

MainWindow::~MainWindow()
{
}
void MainWindow::createActions(){
  settingAction = new QAction("Settings");
  aboutAction = new QAction("About");
 connect(aboutAction,SIGNAL(triggered()),this,SLOT(aboutMenu()));
  checkupdateAction = new QAction("Check for Updates");
    penAction = new QAction("Pen");
    penAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/pen.png")));
    hFlipAction = new QAction("Horizontal Flip");
    hFlipAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/hflip.png")));
    connect(hFlipAction,SIGNAL(triggered()),this,SLOT(hflip()));
    vFlipAction = new QAction("Vertical Flip");
    vFlipAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/vflip.png")));
    connect(vFlipAction,SIGNAL(triggered()),this,SLOT(vflip()));
    openFileAction = new QAction("&Open File",this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip("Open Image File");
    openFileAction->setIcon(QIcon(":/main/resources/icon/openfile.png"));
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(showOpenFile()));
    exitAction = new QAction("&Quit",this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip("Quit Application");
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    zoomInAction = new QAction("Zoom &In",this);
    zoomInAction->setShortcut(tr("Ctrl+I"));
    zoomInAction->setIcon(QIcon(":/main/resources/icon/zoomin.png"));
     connect(zoomInAction,SIGNAL(triggered()),this,SLOT(zoomIn()));
    zoomOutAction = new QAction("Zoom O&ut",this);
    zoomOutAction->setShortcut(tr("Ctrl+U"));
    zoomOutAction->setIcon(QIcon(":/main/resources/icon/zoomout.png"));
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
    fileMenu->addAction(exitAction);
    editMenu = menuBar()->addMenu("&Edit");
    viewMenu = menuBar()->addMenu("&View");
    viewMenu->addAction(hFlipAction);
    viewMenu->addAction(vFlipAction);
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    toolsMenu =menuBar()->addMenu("&Tools");
    toolsMenu->addAction(geometryAction);
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(checkupdateAction);
}
void MainWindow::createToolbars(){
    fileTool = addToolBar("File");
    fileTool->addAction(openFileAction);
     fileTool->addAction(geometryAction);
    fileTool->addAction(zoomInAction);
    fileTool->addAction(zoomOutAction);
    ImageTool = addToolBar("Image");
    ImageTool->addAction(penAction);
    ImageTool->addAction(vFlipAction);
    ImageTool->addAction(hFlipAction);
}
void MainWindow::loadFile(QString filename){
    img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));
    imgWin->resize(QPixmap::fromImage(img).size());
}
void MainWindow::showOpenFile(){
    filename = QFileDialog::getOpenFileName(this, "Open Image",".",tr("Images (*.jpg *.jpeg *.png *.bmp *.gif)"));
    loadFile(filename);
}
void MainWindow::zoomIn(){
  imgWin->setPixmap(QPixmap::fromImage(img.scaled(img.width()*2,img.height()*2)));
  imgWin->resize(QPixmap::fromImage(img.scaled(img.width()*2,img.height()*2)).size());
}

void MainWindow::zoomOut(){
imgWin->setPixmap(QPixmap::fromImage(img.scaled(img.width()/2,img.height()/2)));
imgWin->resize(QPixmap::fromImage(img.scaled(img.width()/2,img.height()/2)).size());
}

void MainWindow::showGeometryTransform(){
    if(!img.isNull())
        gWin->srcImg = img;
    gWin->inWin->setPixmap(QPixmap::fromImage(gWin->srcImg));
    gWin->show();
}
void MainWindow::aboutMenu(){
  aWin->show();
}
void MainWindow::vflip(){
  imgWin->setPixmap(QPixmap::fromImage(img.mirrored(false,true)));
}
void MainWindow::hflip(){
  imgWin->setPixmap(QPixmap::fromImage(img.mirrored(true,false)));
}
