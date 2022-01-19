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
  fWin = new Fileinfo();
  adWin = new Adjustment();
  cWin = new Camera();
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
  cameraAction = new QAction(tr("Capture Photo"));
  connect(cameraAction,SIGNAL(triggered()),this,SLOT(camera()));
  fileinfoAction = new QAction(tr("File Info"));
  connect(fileinfoAction,SIGNAL(triggered()),this,SLOT(fileinfo()));
  adjustmentAction = new QAction(tr("Image Adjustment"));
  connect(adjustmentAction,SIGNAL(triggered()),this,SLOT(adjustment()));
  invertAction = new QAction(tr("Invert"));
  connect(invertAction,SIGNAL(triggered()),this,SLOT(invert()));
  grayscaleAction = new QAction(tr("Grayscale"));
  connect(grayscaleAction,SIGNAL(triggered()),this,SLOT(grayscale()));
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
  alwaysontopAction->setCheckable(true);
  connect(alwaysontopAction,SIGNAL(triggered()),this,SLOT(alwaysontop()));
  histogramAction = new QAction(tr("Show Histrogram"));
  connect(histogramAction,SIGNAL(triggered()),this,SLOT(histogram()));
  thresholdAction = new QAction(tr("Threshold..."));
  connect(thresholdAction,SIGNAL(triggered()),this,SLOT(threshold()));
  printAction = new QAction(tr("Print"));
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
  settingAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/setting.png")));
  connect(settingAction,SIGNAL(triggered()),this,SLOT(settingsMenu()));
  rotateAction = new QAction(tr("Rotate"));
  rotateAction->setIcon(QIcon(QDir().absoluteFilePath(":/main/resources/icon/rotate.png")));
  rotateAction->setDisabled(true);
  connect(rotateAction,SIGNAL(triggered()),this,SLOT(rotate()));
  fullscreenAction=new QAction(tr("Fullscreen"));
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
  editMenu->addAction(undoAction);
  editMenu->addAction(redoAction);
  editMenu->addAction(adjustmentAction);
  editMenu->addAction(thresholdAction);
  editMenu->addAction(grayscaleAction);
  editMenu->addAction(invertAction);
  viewMenu = menuBar()->addMenu(tr("&View"));
  viewMenu->addAction(histogramAction);
  viewMenu->addAction(hFlipAction);
  viewMenu->addAction(vFlipAction);
  viewMenu->addAction(zoomInAction);
  viewMenu->addAction(zoomOutAction);
  viewMenu->addAction(fullscreenAction);
  viewMenu->addAction(alwaysontopAction);
  toolsMenu =menuBar()->addMenu(tr("&Tools"));
  shareMenu = toolsMenu->addMenu(tr("Share"));
  toolsMenu->addAction(settingAction);
  shareMenu->addAction(imgurAction);
  shareMenu->addAction(imgbbAction);
  shareMenu->addAction(imageshackAction);
  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(checkupdateAction);
}
void MainWindow::createToolbars(){
  fileTool = addToolBar(tr("File"));
  fileTool->addAction(zoomInAction);
  fileTool->addAction(zoomOutAction);
  fileTool->addAction(clipboardAction);
  ImageTool = addToolBar(tr("Image"));
  ImageTool->addAction(undoAction);
  ImageTool->addAction(redoAction);
  ImageTool->addAction(penAction);
  ImageTool->addAction(colorpickerAction);
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
      qDebug()<< img.load(filename);
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
  qDebug() << "imgur";
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
  connect(adWin->brightness_slider,SIGNAL(valueChanged(int)), this, SLOT(brightness(int)));
  connect(adWin->contrast_slider,SIGNAL(valueChanged(int)), this, SLOT(contrast(int)));
  connect(adWin->saturation_slider,SIGNAL(valueChanged(int)), this, SLOT(saturation(int)));
}

void MainWindow::fileinfo(){
  fWin->show();
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
  msgBox.exec();
}

void MainWindow::saturation(int value){

}

void MainWindow::contrast(int value){
  result = QImage(QSize(tempWin->pixmap().toImage().width(),tempWin->pixmap().toImage().height()),QImage::Format_RGB16);
  float v =(255.0+value)/(255.0-value);
  for(int j=0;j<tempWin->pixmap().toImage().height();j++){
      for(int i=0;i<tempWin->pixmap().toImage().width();i++){
          QColor color=tempWin->pixmap().toImage().pixelColor(i,j);
          result.setPixelColor(i, j, qRgb(qMin(255, qMax(0,qRound(v*(color.red()-b+b)))), qMin(255, qMax(0,qRound(v*(color.green()-b+b)))), qMin(255, qMax(0,qRound(v*(color.blue()-b+b))))));
        }
    }

  imgWin->setPixmap(QPixmap::fromImage(result));
}
/*https://towardsdatascience.com/image-processing-and-pixel-manipulation-photo-filters-5d37a2f992fa*/
void MainWindow::brightness(int value){
  /*result = QImage(QSize(tempWin->pixmap().toImage().width(),tempWin->pixmap().toImage().height()),QImage::Format_RGB16);
  for(int j=0;j<tempWin->pixmap().toImage().height();j++){
      for(int i=0;i<tempWin->pixmap().toImage().width();i++){
          QColor color=tempWin->pixmap().toImage().pixelColor(i,j).convertTo(QColor::Hsv);
          color.setHsv(color.hue(),color.saturation(),value);
          result.setPixelColor(i, j, color);
        }
    }
  imgWin->setPixmap(QPixmap::fromImage(result));*/
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
  cWin->show();
  connect(cWin->capture,SIGNAL(triggered()), this, SLOT(imagefromcamera());
}

void MainWindow::imagefromcamera(){
  cWin->close();
  imgWin->setPixmap(QPixmap::fromImage(cWin->img));
  imgWin->resize(QPixmap::fromImage(cWin->img).size());
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
