/*TODO: update all the Signal Slot syntax to new ones
https://wiki.qt.io/New_Signal_Slot_Syntax
Next Previous Image
Hide treeview
switch label to graphicview
*/
#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QInputDialog>
#include <QPainter>
#include <QMessageBox>
#include <QtNetwork>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
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
  adWin = new Adjustment();
  bWin = new Brightness();
  coWin = new Contrast();
  hWin = new Hue();
  wWin = new Warmth();
  saWin = new Saturation();
  thresholdWin = new Threshold();
  imgWin->resize(500,300);
  imgWin->setScaledContents(true);
  QScrollArea *imageScrollArea = new QScrollArea();
  imageScrollArea->setAlignment(Qt::AlignCenter);
  imageScrollArea->setFrameShape(QFrame::NoFrame);
  imageScrollArea->setWidget(imgWin);
  mainLayout->addWidget(imageScrollArea);
  imageside->setLayout(mainLayout);
  treeviewTool = addToolBar(tr("Tree View"));
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
  warmthAction = new QAction(tr("Warmth"));
  warmthAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/warmth.png")));
  connect(warmthAction,SIGNAL(triggered()),this,SLOT(warmthWin()));
  brightnessAction = new QAction(tr("Brightness"));
  brightnessAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/brightness.png")));
  connect(brightnessAction,SIGNAL(triggered()),this,SLOT(brightnessWin()));
  contrastAction = new QAction(tr("Contrast"));
  contrastAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/contrast.png")));
  connect(contrastAction,SIGNAL(triggered()),this,SLOT(contrastWin()));
  hueAction = new QAction(tr("Hue"));
  hueAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/hue.png")));
  connect(hueAction,SIGNAL(triggered()),this,SLOT(hueWin()));
  saturationAction = new QAction(tr("Saturation"));
  saturationAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/saturation.png")));
  connect(saturationAction,SIGNAL(triggered()),this,SLOT(saturationWin()));
  cameraAction = new QAction(tr("Capture Photo"));
  cameraAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/webcam.png")));
  connect(cameraAction,SIGNAL(triggered()),this,SLOT(camera()));
  fileinfoAction = new QAction(tr("File Info"));
  fileinfoAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/about.png")));
  connect(fileinfoAction,SIGNAL(triggered()),this,SLOT(fileinfo()));
  adjustmentAction = new QAction(tr("Image Adjustment"));
  adjustmentAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/adjustment.png")));
  connect(adjustmentAction,SIGNAL(triggered()),this,SLOT(adjustment()));
  invertAction = new QAction(tr("Invert"));
  invertAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/invert.png")));
  connect(invertAction,SIGNAL(triggered()),this,SLOT(invert()));
  grayscaleAction = new QAction(tr("Grayscale"));
  grayscaleAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/grayscale.png")));
  connect(grayscaleAction,SIGNAL(triggered()),this,SLOT(grayscale()));
  sepiaAction = new QAction(tr("Sepia"));
  sepiaAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/sepia.png")));
  connect(sepiaAction,SIGNAL(triggered()),this,SLOT(sepia()));
  colorpickerAction = new QAction(tr("Color picker"));
  colorpickerAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/up.png")));
  connect(colorpickerAction,SIGNAL(triggered()),this,SLOT(colorpicker()));
  dirupAction = new QAction(tr("Up to parent directory"));
  dirupAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/up.png")));
  connect(dirupAction,SIGNAL(triggered()),this,SLOT(dirup()));
  dirhomeAction = new QAction(tr("Back to home directory"));
  dirhomeAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/home.png")));
  connect(dirhomeAction,SIGNAL(triggered()),this,SLOT(dirhome()));
  alwaysontopAction = new QAction(tr("Always on top"));
  alwaysontopAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/pin.png")));
  alwaysontopAction->setCheckable(true);
  connect(alwaysontopAction,SIGNAL(triggered()),this,SLOT(alwaysontop()));
  histogramAction = new QAction(tr("Show Histrogram"));
  connect(histogramAction,SIGNAL(triggered()),this,SLOT(histogram()));
  thresholdAction = new QAction(tr("Threshold..."));
  connect(thresholdAction,SIGNAL(triggered()),this,SLOT(threshold()));
  printAction = new QAction(tr("Print"));
  printAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/print.png")));
  printAction->setDisabled(true);
  connect(printAction,SIGNAL(triggered()),this,SLOT(print()));
  newWindowAction = new QAction(tr("Open New Window"));
  connect(newWindowAction,SIGNAL(triggered()),this,SLOT(newWindow()));
  redoAction = new QAction(tr("Redo"));
  redoAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/redo.png")));
  redoAction->setDisabled(true);
  undoAction = new QAction(tr("Undo"));
  undoAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/undo.png")));
  undoAction->setDisabled(true);
  imgurAction = new QAction(tr("Upload to Imgur"));
  connect(imgurAction,SIGNAL(triggered()),this,SLOT(imgur()));
  imgbbAction = new QAction(tr("Upload to ImgBB"));
  connect(imgbbAction,SIGNAL(triggered()),this,SLOT(imgbb()));
  imageshackAction = new QAction(tr("Upload to ImageShack"));
  clipboardAction = new QAction(tr("Copy to Clipboard"));
  clipboardAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/clipboard.png")));
  connect(clipboardAction,SIGNAL(triggered()),this,SLOT(copytoclipboard()));
  saveAction = new QAction(tr("Save"));
  saveAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/save.png")));
  saveAction->setDisabled(true);
  connect(saveAction,SIGNAL(triggered()),this,SLOT(save()));
  saveAsAction = new QAction(tr("Save as PNG file"));
  saveAsAction->setDisabled(true);
  saveAsJPGAction = new QAction(tr("Save as JPG file"));
  saveAsJPGAction->setDisabled(true);
  saveAsBMPAction = new QAction(tr("Save as BMP file"));
  saveAsAction->setDisabled(true);
  connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));
  connect(saveAsBMPAction,SIGNAL(triggered()),this,SLOT(saveAsBMP()));
  connect(saveAsJPGAction,SIGNAL(triggered()),this,SLOT(saveAsJPG()));
  settingAction = new QAction(tr("Settings"));
  settingAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/settings.png")));
  connect(settingAction,SIGNAL(triggered()),this,SLOT(settingsMenu()));
  rotateAction = new QAction(tr("Rotate"));
  rotateAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/rotate.png")));
  rotateAction->setDisabled(true);
  connect(rotateAction,SIGNAL(triggered()),this,SLOT(rotate()));
  fullscreenAction=new QAction(tr("Fullscreen"));
  fullscreenAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/fullscreen.png")));
  connect(fullscreenAction,SIGNAL(triggered()),this,SLOT(fullscreen()));
  aboutAction = new QAction(tr("About"));
  connect(aboutAction,SIGNAL(triggered()),this,SLOT(aboutMenu()));
  checkupdateAction = new QAction(tr("Check for Updates"));
  penAction = new QAction(tr("Pen"));
  penAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/pen.png")));
  penAction->setCheckable(true);
  hFlipAction = new QAction(tr("Horizontal Flip"));
  hFlipAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/hflip.png")));
  hFlipAction->setDisabled(true);
  connect(hFlipAction,SIGNAL(triggered()),this,SLOT(hflip()));
  vFlipAction = new QAction(tr("Vertical Flip"));
  vFlipAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/vflip.png")));
  vFlipAction->setDisabled(true);
  connect(vFlipAction,SIGNAL(triggered()),this,SLOT(vflip()));
  openFileAction = new QAction(tr("&Open File"),this);
  openFileAction->setShortcut(tr("Ctrl+O"));
  openFileAction->setStatusTip(tr("Open Image File"));
  openFileAction->setIcon(QIcon(":/main/resources/icon/openfile.png"));
  openFromUrlAction= new QAction(tr("Open From Url..."),this);
  openFromUrlAction->setStatusTip(tr("Open Image File from Url"));
  openFromUrlAction->setIcon(QIcon(":/main/resources/icon/link.png"));
  connect(openFileAction,SIGNAL(triggered()),this,SLOT(showOpenFile()));
  connect(openFromUrlAction,SIGNAL(triggered()),this,SLOT(showOpenUrl()));
  exitAction = new QAction(tr("&Quit"),this);
  exitAction->setShortcut(tr("Ctrl+Q"));
  exitAction->setStatusTip(tr("Quit Application"));
  connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
  zoomInAction = new QAction(tr("Zoom &In"),this);
  zoomInAction->setShortcut(tr("Ctrl++"));
  zoomInAction->setIcon(QIcon(":/main/resources/icon/zoomin.png"));
  zoomInAction->setDisabled(true);
  connect(zoomInAction,SIGNAL(triggered()),this,SLOT(zoomIn()));
  zoomOutAction = new QAction(tr("Zoom O&ut"),this);
  zoomOutAction->setShortcut(tr("Ctrl+-"));
  zoomOutAction->setIcon(QIcon(":/main/resources/icon/zoomout.png"));
  zoomOutAction->setDisabled(true);
  connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(zoomOut()));
  connect(exitAction,SIGNAL(triggered()),imgWin,SLOT(close()));
}

void MainWindow::createMenus(){
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openFileAction);
  fileMenu->addAction(openFromUrlAction);
  fileMenu->addAction(cameraAction);
  fileMenu->addAction(newWindowAction);
  saveMenu = fileMenu->addMenu(tr("Save As..."));
  saveMenu->addAction(saveAsAction);
  saveMenu->addAction(saveAsBMPAction);
  saveMenu->addAction(saveAsJPGAction);
  fileMenu->addAction(saveAction);
  fileMenu->addAction(fileinfoAction);
  fileMenu->addAction(printAction);
  fileMenu->addAction(exitAction);
  editMenu = menuBar()->addMenu(tr("&Edit"));
  adjustmentMenu = editMenu->addMenu(tr("Image Adjustment"));
  adjustmentMenu->addAction(brightnessAction);
  adjustmentMenu->addAction(contrastAction);
  adjustmentMenu->addAction(saturationAction);
  adjustmentMenu->addAction(hueAction);
  adjustmentMenu->addAction(warmthAction);
  editMenu->addAction(thresholdAction);
  editMenu->addAction(grayscaleAction);
  editMenu->addAction(invertAction);
  editMenu->addAction(sepiaAction);
  viewMenu = menuBar()->addMenu(tr("&View"));
  viewMenu->addAction(histogramAction);
  viewMenu->addAction(hFlipAction);
  viewMenu->addAction(vFlipAction);
  viewMenu->addAction(rotateAction);
  viewMenu->addAction(zoomInAction);
  viewMenu->addAction(zoomOutAction);
  viewMenu->addAction(fullscreenAction);
  viewMenu->addAction(alwaysontopAction);
  toolsMenu =menuBar()->addMenu(tr("&Tools"));
  shareMenu = toolsMenu->addMenu(tr("Share"));
  toolsMenu->addAction(settingAction);
  toolsMenu->addAction(clipboardAction);
  shareMenu->addAction(imgurAction);
  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(checkupdateAction);
}
void MainWindow::createToolbars(){
  fileTool = addToolBar(tr("File"));
  fileTool->addAction(fullscreenAction);
  fileTool->addAction(alwaysontopAction);
  fileTool->addAction(zoomInAction);
  fileTool->addAction(zoomOutAction);
  fileTool->addAction(clipboardAction);
  ImageTool = addToolBar(tr("Image"));
  ImageTool->addAction(brightnessAction);
  ImageTool->addAction(contrastAction);
  ImageTool->addAction(saturationAction);
  ImageTool->addAction(hueAction);
  ImageTool->addAction(warmthAction);
  ImageTool->addAction(grayscaleAction);
  ImageTool->addAction(invertAction);
  ImageTool->addAction(sepiaAction);
  ImageTool->addAction(vFlipAction);
  ImageTool->addAction(hFlipAction);
  ImageTool->addAction(rotateAction);
  treeviewTool->addAction(openFileAction);
  treeviewTool->addAction(dirupAction);
  treeviewTool->addAction(dirhomeAction);

}
void MainWindow::loadFile(QString filename){

  if(filename.contains(".gif",Qt::CaseInsensitive)){
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

void MainWindow::grayscale(){
  tempWin->setPixmap(imgWin->pixmap());
  result = tempWin->pixmap().toImage().convertToFormat(QImage::Format_Grayscale16);
  imgWin->setPixmap(QPixmap::fromImage(result));
}

void MainWindow::invert(){
  tempWin->setPixmap(imgWin->pixmap());
  result = tempWin->pixmap().toImage();
  result.invertPixels(QImage::InvertRgba);
  imgWin->setPixmap(QPixmap::fromImage(result));
}

void MainWindow::saveAsBMP(){
  filename = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                          QString(),
                                          tr("Images (*.bmp)"));
  if (!filename.isEmpty())
    {
      imgWin->pixmap().save(filename, "BMP");
    }
}
void MainWindow::saveAsJPG(){
  filename = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                          QString(),
                                          tr("Images (*.jpg)"));
  if (!filename.isEmpty())
    {
      imgWin->pixmap().save(filename, "JPG");
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
  imgurupload = new QNetworkAccessManager(this);
  connect(imgurupload,
          SIGNAL(finished(QNetworkReply*)),
          this,SLOT(handleReply(QNetworkReply*)));
  QByteArray byteArray;
  QBuffer buffer(&byteArray);
  imgWin->pixmap().save(&buffer, "PNG");
  QUrl url(("https://api.imgur.com/3/image"));
  QNetworkRequest request(url);
  request.setRawHeader(
        "Authorization",
        ("Client-ID bc7f6d29d2cf7d6"));

  imgurupload->post(request, byteArray);
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
  connect(thresholdWin->slider,SIGNAL(valueChanged(int)), this, SLOT(updateimg(int)));
  thresholdWin->setFixedSize(250,100);
  thresholdWin->setWindowTitle(tr("Adjust Threshold"));
  thresholdWin->setAttribute(Qt::WA_DeleteOnClose);
  thresholdWin->show();
}

void MainWindow::warmthWin(){
  tempWin->setPixmap(imgWin->pixmap());
  connect(wWin->slider,SIGNAL(valueChanged(int)), this, SLOT(warmth(int)));
  wWin->setFixedSize(250,100);
  wWin->setWindowTitle(tr("Adjust Warmth"));
  wWin->setAttribute(Qt::WA_DeleteOnClose);
  wWin->show();
}

void MainWindow::saturationWin(){
  tempWin->setPixmap(imgWin->pixmap());
  connect(saWin->slider,SIGNAL(valueChanged(int)), this, SLOT(saturation(int)));
  saWin->setFixedSize(250,100);
  saWin->setWindowTitle(tr("Adjust Saturation"));
  saWin->setAttribute(Qt::WA_DeleteOnClose);
  saWin->show();
}

void MainWindow::brightnessWin(){
  tempWin->setPixmap(imgWin->pixmap());
  connect(bWin->slider,SIGNAL(valueChanged(int)), this, SLOT(brightness(int)));
  bWin->setFixedSize(250,100);
  bWin->setWindowTitle(tr("Adjust Brightness"));
  bWin->setAttribute(Qt::WA_DeleteOnClose);
  bWin->show();
}

void MainWindow::hueWin(){
  tempWin->setPixmap(imgWin->pixmap());
  connect(hWin->slider,SIGNAL(valueChanged(int)), this, SLOT(hue(int)));
  hWin->setFixedSize(250,100);
  hWin->setWindowTitle(tr("Adjust Hue"));
  hWin->setAttribute(Qt::WA_DeleteOnClose);
  hWin->show();
}

void MainWindow::contrastWin(){
  tempWin->setPixmap(imgWin->pixmap());
  for(int i=0;i<imgWin->pixmap().toImage().height();i++){
      for(int j=0;j<imgWin->pixmap().toImage().width();j++){
          b += imgWin->pixmap().toImage().pixelColor(j,i).red() * 0.299 + imgWin->pixmap().toImage().pixelColor(j,i).green() * 0.587+imgWin->pixmap().toImage().pixelColor(j,i).blue() * 0.144;
        }
    }
  b/=(imgWin->pixmap().toImage().height() * imgWin->pixmap().toImage().width());
  connect(coWin->slider,SIGNAL(valueChanged(int)), this, SLOT(contrast(int)));
  coWin->setFixedSize(250,100);
  coWin->setWindowTitle(tr("Adjust Contrast"));
  coWin->setAttribute(Qt::WA_DeleteOnClose);
  coWin->show();
}

void MainWindow::adjustment(){
  adWin->show();
  tempWin->setPixmap(imgWin->pixmap());
  /*https://stackoverflow.com/questions/4876315/determining-image-luminance-brightness*/
  for(int i=0;i<imgWin->pixmap().toImage().height();i++){
      for(int j=0;j<imgWin->pixmap().toImage().width();j++){
          b += imgWin->pixmap().toImage().pixelColor(j,i).red() * 0.299 + imgWin->pixmap().toImage().pixelColor(j,i).green() * 0.587+imgWin->pixmap().toImage().pixelColor(j,i).blue() * 0.144;
        }
    }
  b/=(imgWin->pixmap().toImage().height() * imgWin->pixmap().toImage().width());
  result = QImage(QSize(tempWin->pixmap().toImage().width(),tempWin->pixmap().toImage().height()),QImage::Format_RGB16);
  connect(adWin->brightness_slider,SIGNAL(valueChanged(int)), this, SLOT(brightness(int)));
  connect(adWin->contrast_slider,SIGNAL(valueChanged(int)), this, SLOT(contrast(int)));
  connect(adWin->saturation_slider,SIGNAL(valueChanged(int)), this, SLOT(saturation(int)));
  connect(adWin->warmth_slider,SIGNAL(valueChanged(int)), this, SLOT(warmth(int)));
  connect(adWin->hue_slider,SIGNAL(valueChanged(int)), this, SLOT(hue(int)));
}

void MainWindow::fileinfo(){
  fWin = new Fileinfo();
  fWin->img = QFileInfo(filename);
  fWin->show();
  fWin->fileNameLabel->setText(tr("File Name: %1").arg(fWin->img.fileName()));
  fWin->pathLabel->setText(tr("Path: %1").arg(fWin->img.path()));
  fWin->sizeLabel->setText(tr("File Size: %1 Bytes").arg(fWin->img.size()));
  fWin->lastReadLabel->setText(tr("Last Read: %1").arg(fWin->img.lastRead().toString("yyyy/MM/dd hh:mm:ss")));
  fWin->lastModLabel->setText(tr("Last Modified: %1").arg(fWin->img.lastModified().toString("yyyy/MM/dd hh:mm:ss")));
  fWin->widthLabel->setText(tr("Width: %1").arg(imgWin->pixmap().toImage().width()));
  fWin->heightLabel->setText(tr("Height: %1").arg(imgWin->pixmap().toImage().height()));
  fWin->megapixelLabel->setText(tr("Megapixels: %1 MP").arg(imgWin->pixmap().toImage().width()*imgWin->pixmap().toImage().height()/1000000.0));
  int gcd = this->gcd(imgWin->pixmap().toImage().width(), imgWin->pixmap().toImage().height());
  fWin->ratioLabel->setText(tr("Ratio: %1:%2").arg(QString::number(imgWin->pixmap().toImage().width()/gcd),QString::number(imgWin->pixmap().toImage().height()/gcd)));
}

int MainWindow::gcd(int a, int b){
  return (b == 0) ? a :gcd(b, a%b);
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
  histogramWin->setWindowTitle(tr("Histogram"));
  histogramWin->show();
}

void MainWindow::updateimg(int a){
  int tmp;
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


void MainWindow::colorpicker(){
  clipboard->setText("#-0000");
}

void MainWindow::openUrl(QUrl &url){
  QNetworkAccessManager *nam = new QNetworkAccessManager(this);
  connect(nam, &QNetworkAccessManager::finished, this, &MainWindow::downloadFinished);
  QNetworkRequest request(url);
  nam->get(request);
}

void MainWindow::downloadFinished(QNetworkReply *reply)
{
  QPixmap pm;
  pm.loadFromData(reply->readAll());
  imgWin->setPixmap(pm);
  imgWin->resize(pm.size());
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

void MainWindow::showOpenUrl(){
  auto inputDialog = new QInputDialog(this);
  inputDialog->setWindowTitle(tr("Open URL..."));
  inputDialog->setLabelText(tr("URL of a supported image file:"));
  inputDialog->resize(350, inputDialog->height());
  inputDialog->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
  connect(inputDialog, &QInputDialog::finished, this, [inputDialog, this](int result) {
      auto url = QUrl(inputDialog->textValue());
      openUrl(url);
    });
  inputDialog->open();
}

void MainWindow::handleReply(QNetworkReply *reply){
  QString answer = reply->readAll();

  QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
  QJsonObject jsonObject = jsonResponse.object();
  QJsonObject data = jsonObject["data"].toObject();
  QMessageBox msgBox;
  msgBox.setText(tr("%1. Link copied to the clipboard.").arg(data["link"].toString()));
  clipboard->setText(data["link"].toString());
  msgBox.exec();
}

void MainWindow::handleimgbbReply(QNetworkReply *reply){
  QString answer = reply->readAll();
  qDebug() << answer;
  QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
  QJsonObject jsonObject = jsonResponse.object();
  QJsonObject data = jsonObject["data"].toObject();
  QMessageBox msgBox;
  msgBox.setText(tr("%1. Link copied to the clipboard.").arg(data["url"].toString()));
  clipboard->setText(data["url"].toString());
  msgBox.exec();
}

void MainWindow::saturation(int value){
  result = QImage(QSize(tempWin->pixmap().toImage().width(),tempWin->pixmap().toImage().height()),QImage::Format_RGB16);
  float v =(255.0+value)/(255.0-value);
  for(int j=0;j<tempWin->pixmap().toImage().height();j++){
      for(int i=0;i<tempWin->pixmap().toImage().width();i++){
          QColor color=tempWin->pixmap().toImage().pixelColor(i,j);
          float b = (color.red() + color.green() + color.blue())/3;
          result.setPixelColor(i, j, qRgb(qMin(255, qMax(0,qRound(v*(color.red()-b)+b))), qMin(255, qMax(0,qRound(v*(color.green()-b)+b))), qMin(255, qMax(0,qRound(v*(color.blue()-b)+b)))));
        }
    }

  imgWin->setPixmap(QPixmap::fromImage(result));
}

void MainWindow::contrast(int value){
  result = QImage(QSize(tempWin->pixmap().toImage().width(),tempWin->pixmap().toImage().height()),QImage::Format_RGB16);
  float v =(255.0+value)/(255.0-value);
  for(int j=0;j<tempWin->pixmap().toImage().height();j++){
      for(int i=0;i<tempWin->pixmap().toImage().width();i++){
          QColor color=tempWin->pixmap().toImage().pixelColor(i,j);
          result.setPixelColor(i, j, qRgb(qMin(255, qMax(0,qRound(v*(color.red()-b)+b))), qMin(255, qMax(0,qRound(v*(color.green()-b)+b))), qMin(255, qMax(0,qRound(v*(color.blue()-b)+b)))));
        }
    }

  imgWin->setPixmap(QPixmap::fromImage(result));
}
/*https://towardsdatascience.com/image-processing-and-pixel-manipulation-photo-filters-5d37a2f992fa*/
void MainWindow::brightness(int value){
  result = QImage(QSize(tempWin->pixmap().toImage().width(),tempWin->pixmap().toImage().height()),QImage::Format_RGB16);
  for(int j=0;j<tempWin->pixmap().toImage().height();j++){
      for(int i=0;i<tempWin->pixmap().toImage().width();i++){
          QColor color=tempWin->pixmap().toImage().pixelColor(i,j);
          result.setPixelColor(i, j, qRgb(qMin(255, qMax(0,color.red()+value)), qMin(255, qMax(0,color.green()+value)), qMin(255, qMax(0,color.blue()+value))));
        }
    }
  imgWin->setPixmap(QPixmap::fromImage(result));
}

void MainWindow::camera(){
  cWin = new Camera();
  cWin->show();
  connect(cWin->capture,SIGNAL(clicked()), this, SLOT(imagefromcamera()));
}

void MainWindow::imagefromcamera(){
  connect(cWin->imgcapture,SIGNAL(imageCaptured(int, QImage)),this,SLOT(cameraimage(int, QImage)));
  cWin->imgcapture->capture();
}

void MainWindow::cameraimage(int v, QImage i){
  cWin->close();
  imgWin->setPixmap(QPixmap::fromImage(i));
  imgWin->resize((QPixmap::fromImage(i)).size());
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

void MainWindow::sepia(){
  tempWin->setPixmap(imgWin->pixmap());
  result = tempWin->pixmap().toImage();
  for(int j=0;j<tempWin->pixmap().toImage().height();j++){
      for(int i=0;i<tempWin->pixmap().toImage().width();i++){
          QColor color=tempWin->pixmap().toImage().pixelColor(i,j);
          result.setPixelColor(i, j, qRgb(qMin(255, qMax(0,qRound(color.red()*0.393+color.green()*0.769+color.blue()*0.189))),qMin(255, qMax(0,qRound(color.red()*0.349+color.green()*0.686+color.blue()*0.168))), qMin(255, qMax(0,qRound(color.red()*0.272+color.green()*0.534+color.blue()*0.131)))));
        }
    }
  imgWin->setPixmap(QPixmap::fromImage(result));
}
/*https://stackoverflow.com/questions/40292484/how-to-pass-several-parameters-when-uploading-image-to-imgur*/
void MainWindow::imgbb(){
  imgurupload = new QNetworkAccessManager(this);
  connect(imgurupload,
          SIGNAL(finished(QNetworkReply*)),
          this,SLOT(handleimgbbReply(QNetworkReply*)));
  QByteArray byteArray;
  QBuffer buffer(&byteArray);
  imgWin->pixmap().save(&buffer, "PNG");
  QUrl url("https://api.imgbb.com/1/upload?key=8f8f3f2e90faa757dfa41c398a98b59c");
  QNetworkRequest request(url);
  imgurupload->post(request, byteArray);
}

void MainWindow::warmth(int v){
  result = QImage(QSize(tempWin->pixmap().toImage().width(),tempWin->pixmap().toImage().height()),QImage::Format_RGB16);
  for(int j=0;j<tempWin->pixmap().toImage().height();j++){
      for(int i=0;i<tempWin->pixmap().toImage().width();i++){
          QColor color=tempWin->pixmap().toImage().pixelColor(i,j);
          result.setPixelColor(i, j, qRgb(color.red(), color.green(), qMin(255, qMax(0,color.blue()+v))));
        }
    }
  imgWin->setPixmap(QPixmap::fromImage(result));
}

void MainWindow::hue(int v){
  result = QImage(QSize(tempWin->pixmap().toImage().width(),tempWin->pixmap().toImage().height()),QImage::Format_RGB16);
  for(int j=0;j<tempWin->pixmap().toImage().height();j++){
      for(int i=0;i<tempWin->pixmap().toImage().width();i++){
          QColor color=tempWin->pixmap().toImage().pixelColor(i,j).convertTo(QColor::Hsv);
          color.setHsv(color.hue()+v,color.saturation(),color.value());
          result.setPixelColor(i, j, color);
        }
    }
  imgWin->setPixmap(QPixmap::fromImage(result));
}
