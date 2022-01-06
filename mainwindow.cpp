/*TODO: update all the Signal Slot syntax to new ones
https://wiki.qt.io/New_Signal_Slot_Syntax

Next Previous Image

Hide treeview
*/

#include "mainwindow.h"
#include "about.h"
#include "settings.h"
#include "threshold.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QPainter>
#include <QtNetwork>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Daruma");
    setWindowIcon(QIcon(":/main/resources/icon/app.png"));
    //center = new QWidget();
    QWidget *imageside = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    QWidget *treeside = new QWidget();
    QVBoxLayout *treeLayout = new QVBoxLayout();
    treeLayout->setContentsMargins(0,0,0,0);
    QSplitter *splitter = new QSplitter();
    model = new QFileSystemModel();
    model->setRootPath("");
    model->setNameFilters(QStringList() << "*.png" << "*.jpg" << "*.gif" << "*.webp" << "*.jpeg");
    model->setNameFilterDisables(false);
    tree = new QTreeView();
    tree->setModel(model);
    tree->setUniformRowHeights(true); /*https://stackoverflow.com/questions/29798646/qt5-qtreeview-with-custom-model-and-large-data-very-slow-scrolling*/
    tree->setHeaderHidden(true);
    connect(tree, SIGNAL(clicked(QModelIndex)),
                     this, SLOT(loadfileviatree(QModelIndex)));
    for (int i = 1; i < model->columnCount(); ++i)
        tree->hideColumn(i);
    imgWin = new Label();
    tempWin = new Label();
    histogramWin = new QLabel();
    aWin = new About();
    sWin = new Settings();
    thresholdWin = new Threshold();
    imgWin->resize(500,300);
    imgWin->setScaledContents(true);
    QScrollArea *imageScrollArea = new QScrollArea();
       imageScrollArea->setAlignment(Qt::AlignCenter);
       imageScrollArea->setFrameShape(QFrame::NoFrame);
       imageScrollArea->setWidget(imgWin);
    mainLayout->addWidget(imageScrollArea);
    imageside->setLayout(mainLayout);
    treeviewTool = addToolBar("Tree View");
    treeLayout->addWidget(treeviewTool);
    treeLayout->addWidget(tree);
    treeside->setLayout(treeLayout);
    splitter->addWidget(treeside);
    splitter->addWidget(imageside);
    setCentralWidget(splitter);
    createActions();
    createMenus();
    createToolbars();
}

MainWindow::~MainWindow()
{
}
void MainWindow::createActions(){
  dirupAction = new QAction("Up to parent directory");
  dirupAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/up.png")));
  connect(dirupAction,SIGNAL(triggered()),this,SLOT(dirup()));
  dirhomeAction = new QAction("Back to home directory");
  dirhomeAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/home.png")));
  connect(dirhomeAction,SIGNAL(triggered()),this,SLOT(dirhome()));
  alwaysontopAction = new QAction("Always on top");
  alwaysontopAction->setCheckable(true);
  connect(alwaysontopAction,SIGNAL(triggered()),this,SLOT(alwaysontop()));
  histogramAction = new QAction("Show Histrogram");
  connect(histogramAction,SIGNAL(triggered()),this,SLOT(histogram()));
  thresholdAction = new QAction("Threshold...");
  connect(thresholdAction,SIGNAL(triggered()),this,SLOT(threshold()));
  printAction = new QAction("Print");
  printAction->setDisabled(true);
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
  saveAction->setDisabled(true);
   connect(saveAction,SIGNAL(triggered()),this,SLOT(save()));
  saveAsAction = new QAction("Save as...");
  saveAsAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/saveas.png")));
  saveAsAction->setDisabled(true);
  connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));
  settingAction = new QAction("Settings");
  settingAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/setting.png")));
  connect(settingAction,SIGNAL(triggered()),this,SLOT(settingsMenu()));
  rotateAction = new QAction("Rotate");
  rotateAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/rotate.png")));
  rotateAction->setDisabled(true);
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
    hFlipAction->setDisabled(true);
    connect(hFlipAction,SIGNAL(triggered()),this,SLOT(hflip()));
    vFlipAction = new QAction("Vertical Flip");
    vFlipAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/vflip.png")));
    vFlipAction->setDisabled(true);
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
    zoomInAction->setDisabled(true);
     connect(zoomInAction,SIGNAL(triggered()),this,SLOT(zoomIn()));
    zoomOutAction = new QAction("Zoom O&ut",this);
    zoomOutAction->setShortcut(tr("Ctrl+-"));
    zoomOutAction->setIcon(QIcon(":/main/resources/icon/zoomout.png"));
    zoomOutAction->setDisabled(true);
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
    editMenu->addAction(thresholdAction);
    viewMenu = menuBar()->addMenu("&View");
    viewMenu->addAction(histogramAction);
    viewMenu->addAction(hFlipAction);
    viewMenu->addAction(vFlipAction);
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addAction(fullscreenAction);
    viewMenu->addAction(alwaysontopAction);
    toolsMenu =menuBar()->addMenu("&Tools");
    shareMenu = toolsMenu->addMenu("Share");
    toolsMenu->addAction(settingAction);
    shareMenu->addAction(imgurAction);
    shareMenu->addAction(imgbbAction);
    shareMenu->addAction(imageshackAction);
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(checkupdateAction);
}
void MainWindow::createToolbars(){
    fileTool = addToolBar("File");
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
    treeviewTool->addAction(openFileAction);
    treeviewTool->addAction(dirupAction);
    treeviewTool->addAction(dirhomeAction);
}
void MainWindow::loadFile(QString filename){

    if(filename.contains(".gif",Qt::CaseInsensitive)){
       qDebug()<< "gif";
       QMovie *gif = new QMovie(filename);
       imgWin->setMovie(gif);
       gif->start();
}else{
       img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));
};
    imgWin->resize(QPixmap::fromImage(img).size());
    tree->setRootIndex(model->index(filename+"/.."));
    undoAction->setEnabled(true);
    redoAction->setEnabled(true);
    hFlipAction->setEnabled(true);
    vFlipAction->setEnabled(true);
    rotateAction->setEnabled(true);
    printAction->setEnabled(true);
    saveAction->setEnabled(true);
    saveAsAction->setEnabled(true);
    zoomInAction->setEnabled(true);
    zoomOutAction->setEnabled(true);
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

void MainWindow::threshold(){
  tempWin->setPixmap(imgWin->pixmap());
  Threshold *thresholdWin = new Threshold();
  connect(thresholdWin->slider,SIGNAL(valueChanged(int)), this, SLOT(updateimg(int)));
  connect(thresholdWin->okButton,SIGNAL(clicked()),this,SLOT(ok()));
  connect(thresholdWin->cancelButton,SIGNAL(clicked()),this,SLOT(cancel()));
  thresholdWin->setFixedSize(250,100);
  thresholdWin->setWindowTitle("Adjust Threshold");
  thresholdWin->show();
}
void MainWindow::histogram(){
  int top,i;
  unsigned int m =0;
  memset((void *) mtx,0,sizeof(int)*256);
  for(int i=0;i<imgWin->pixmap().toImage().height();i++){
      for(int j=0;j<imgWin->pixmap().toImage().width();j++){
          mtx[qGray(imgWin->pixmap().toImage().pixel(j,i))]++;
        }
    }
  histogramimg = QImage(QSize(256,256),QImage::Format_RGB32);
  histogramimg.fill(Qt::white);
  QPainter painter;
  for(m=0, i=0;i<256;i++){
    if(mtx[i]>m){
      m = mtx[i];
  }
    }
  painter.begin(&histogramimg);
  painter.setPen(Qt::black);
  for(int i=0;i<256;i++){
      top = 256-(mtx[i]*256)/m;
      painter.drawLine(i, top, i,256);
    }
  painter.end();
  histogramWin->setFixedSize(256,256);
  histogramWin->setPixmap(QPixmap::fromImage(histogramimg));
  histogramWin->setWindowTitle("Histogram");
  histogramWin->show();
}
void MainWindow::updateimg(int a){
  int tmp;
clipboard->setPixmap(tempWin->pixmap());
  result = QImage(QSize(tempWin->pixmap().toImage().width(),tempWin->pixmap().toImage().height()),QImage::Format_Mono);
  for(int j=0;j<tempWin->pixmap().toImage().height();j++){
      for(int i=0;i<tempWin->pixmap().toImage().width();i++){
          tmp = (qGray(tempWin->pixmap().toImage().pixel(i,j))>a)?1:0;
          result.setPixel(i,j,tmp);
        }
    }
  imgWin->setPixmap(QPixmap::fromImage(result));
}

void MainWindow::ok(){
  thresholdWin->close();
}

void MainWindow::cancel(){
  imgWin->setPixmap(tempWin->pixmap());
   thresholdWin->close();
}

void MainWindow::loadfileviatree(QModelIndex index){
  loadFile(model->filePath(index));
}

void MainWindow::alwaysontop(){
  if(alwaysontopAction->isChecked()){
              this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
      this->show();
  }
          else{
              this->setWindowFlags(this->windowFlags() & ~Qt::WindowStaysOnTopHint);
      this->show();
    }
}

void MainWindow::settingsMenu(){
  sWin->show();
}

void MainWindow::dirup(){
  tree->setRootIndex(tree->rootIndex().parent());
}

void MainWindow::dirhome(){
  tree->setRootIndex(model->index("/"));
}
