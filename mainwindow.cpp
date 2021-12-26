#include "mainwindow.h"
#include "about.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QtNetwork>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Image Editor");
    setWindowIcon(QIcon(":/main/resources/icon/app.png"));
    center = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(center);
    imgWin = new QLabel();
    aWin = new About();
    imgWin->resize(500,300);
    imgWin->setScaledContents(true);
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
  printAction = new QAction("Print");
  connect(printAction,SIGNAL(triggered()),this,SLOT(print()));
  newWindowAction = new QAction("Open New Window");
  connect(newWindowAction,SIGNAL(triggered()),this,SLOT(newWindow()));
  redoAction = new QAction("Redo");
  redoAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/redo.png")));
  redoAction->setDisabled(true);
  undoAction = new QAction("Undo");
  undoAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/undo.png")));
  undoAction->setDisabled(true);
  imgurAction = new QAction("Upload to Imgur");
  imgbbAction = new QAction("Upload to ImgBB");
  imageshackAction = new QAction("Upload to ImageShack");
  clipboardAction = new QAction("Copy to Clipboard");
  clipboardAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/clipboard.png")));
  connect(clipboardAction,SIGNAL(triggered()),this,SLOT(copytoclipboard()));
  saveAction = new QAction("Save");
  saveAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/save.png")));
   connect(saveAction,SIGNAL(triggered()),this,SLOT(save()));
  saveAsAction = new QAction("Save as...");
  saveAsAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/saveas.png")));
  connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));
  settingAction = new QAction("Settings");
  settingAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/setting.png")));
  rotateAction = new QAction("Rotate");
  rotateAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/rotate.png")));
  connect(rotateAction,SIGNAL(triggered()),this,SLOT(rotate()));
  fullscreenAction=new QAction("Fullscreen");
  connect(fullscreenAction,SIGNAL(triggered()),this,SLOT(fullscreen()));
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
    zoomInAction->setShortcut(tr("Ctrl++"));
    zoomInAction->setIcon(QIcon(":/main/resources/icon/zoomin.png"));
     connect(zoomInAction,SIGNAL(triggered()),this,SLOT(zoomIn()));
    zoomOutAction = new QAction("Zoom O&ut",this);
    zoomOutAction->setShortcut(tr("Ctrl+-"));
    zoomOutAction->setIcon(QIcon(":/main/resources/icon/zoomout.png"));
     connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(zoomOut()));
     connect(exitAction,SIGNAL(triggered()),imgWin,SLOT(close()));
}

 void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(newWindowAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(printAction);
    fileMenu->addAction(exitAction);
    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    viewMenu = menuBar()->addMenu("&View");
    viewMenu->addAction(hFlipAction);
    viewMenu->addAction(vFlipAction);
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addAction(fullscreenAction);
    toolsMenu =menuBar()->addMenu("&Tools");
    shareMenu = toolsMenu->addMenu("Share");
    shareMenu->addAction(imgurAction);
    shareMenu->addAction(imgbbAction);
    shareMenu->addAction(imageshackAction);
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(checkupdateAction);
}
void MainWindow::createToolbars(){
    fileTool = addToolBar("File");
    fileTool->addAction(openFileAction);
    fileTool->addAction(zoomInAction);
    fileTool->addAction(zoomOutAction);
    fileTool->addAction(clipboardAction);
    ImageTool = addToolBar("Image");
    ImageTool->addAction(undoAction);
    ImageTool->addAction(redoAction);
    ImageTool->addAction(penAction);
    ImageTool->addAction(vFlipAction);
    ImageTool->addAction(hFlipAction);
    ImageTool->addAction(rotateAction);
}
void MainWindow::loadFile(QString filename){
    img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));
    imgWin->resize(QPixmap::fromImage(img).size());
    undoAction->setEnabled(true);
    redoAction->setEnabled(true);
}
void MainWindow::showOpenFile(){
    filename = QFileDialog::getOpenFileName(this, "Open Image",".",tr("Images (*.jpg *.jpeg *.png *.bmp *.gif)"));
    loadFile(filename);
}
void MainWindow::zoomIn(){
  imgWin->resize(imgWin->width()*(1.8),imgWin->height()*(1.8));
}

void MainWindow::zoomOut(){
imgWin->resize(imgWin->width()*(0.8),imgWin->height()*(0.8));
}

void MainWindow::aboutMenu(){
  aWin->show();
}
void MainWindow::vflip(){
  imgWin->setPixmap(imgWin->pixmap().transformed(QTransform().scale(-1, 1)));
}
void MainWindow::hflip(){
  imgWin->setPixmap(imgWin->pixmap().transformed(QTransform().scale(1, -1)));
}

void MainWindow::fullscreen(){
  isFullScreen() ? showNormal() : showFullScreen();
}
void MainWindow::save(){
  imgWin->pixmap().save(filename);
}
void MainWindow::saveAs(){
  filename = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                          QString(),
                                          tr("Images (*.png)"));
  if (!filename.isEmpty())
  {
    imgWin->pixmap().save(filename);
  }
}

void MainWindow::rotate(){
  QPixmap pixmap(imgWin->pixmap());
      QTransform tr;
      tr.rotate(90);
      pixmap = pixmap.transformed(tr);
      imgWin->setPixmap(pixmap);
      imgWin->resize(pixmap.size());
}
void MainWindow::copytoclipboard(){
  clipboard->setPixmap(imgWin->pixmap());
}

void MainWindow::imgur(){
  connect(manager, &QNetworkAccessManager::finished,
          this, &MainWindow::replyFinished);

 /* QNetworkReply *reply =*/ manager->get(QNetworkRequest(QUrl("http://qt-project.org")));
}

void MainWindow::replyFinished(){

}

void MainWindow::newWindow(){
  MainWindow *n = new MainWindow();
  n->show();
}

void MainWindow::print(){
  QPrintDialog pdialog(&printer, this);
  if (pdialog.exec()) {
      QPainter painter(&printer);
      QPixmap pixmap = imgWin->pixmap(Qt::ReturnByValue);
      QRect rect = painter.viewport();
      QSize size = pixmap.size();
      size.scale(rect.size(), Qt::KeepAspectRatio);
      painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
      painter.setWindow(pixmap.rect());
      painter.drawPixmap(0, 0, pixmap);
  }
}
