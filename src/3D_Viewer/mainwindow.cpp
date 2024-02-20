#include "mainwindow.h"

#include "glview.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setPr();
  signalsMainWindow();
  connect(ui->widget, &glView::updateMainWindowGl, this,
          &MainWindow::updateMainWindowMW);
  connect(this, &MainWindow::signalSetObj, ui->widget, &glView::slotSetObj);
  connect(ui->widget, &glView::signalUpdateInfoObj, this,
          &MainWindow::updateInfoObj);
}

MainWindow::~MainWindow() {
  if (ui->widget->obj_data.vertexes != NULL ||
      ui->widget->obj_data.facets != NULL)
    data_free(&ui->widget->obj_data);
  delete ui;
}

// выбор файла
void MainWindow::on_pushButton_Open_File_clicked() {
  QString qFileName = QFileDialog::getOpenFileName(
      this, "Open file",
      QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
      tr(" (*.obj)"));
  if (qFileName != "") {
    QByteArray array = qFileName.toLocal8Bit();
    ui->widget->name_file = array.data();
    emit signalSetObj();
  } else
    QMessageBox::critical(this, "Warning", "No file has been selected");
}

void MainWindow::updateMainWindowMW() {
  ui->spinBoxTL->setValue((int)(ui->widget->thickness) - 2);
  ui->horizontalSliderTL->setValue((int)(ui->widget->thickness) - 2);
  ui->spinBoxSP->setValue(ui->widget->sizeP);
  ui->horizontalSliderSP->setValue(ui->widget->sizeP);
  ui->horizontalScrollBarSc->setValue(ui->widget->scale);
  ui->spinBoxSc->setValue(ui->widget->scale);
  ui->horizontalScrollBarRotX->setValue(ui->widget->rotX);
  ui->spinBoxRotX->setValue(ui->widget->rotX);
  ui->horizontalScrollBarRotY->setValue(ui->widget->rotY);
  ui->spinBoxRotY->setValue(ui->widget->rotY);
  ui->horizontalScrollBarRotZ->setValue(ui->widget->rotZ);
  ui->spinBoxRotZ->setValue(ui->widget->rotZ);

  ui->horizontalScrollBarMovX->setValue(ui->widget->movX);
  ui->spinBoxMovX->setValue(ui->widget->movX);
  ui->horizontalScrollBarMovY->setValue(ui->widget->movY);
  ui->spinBoxMovY->setValue(ui->widget->movY);
  ui->horizontalScrollBarMovZ->setValue(ui->widget->movZ);
  ui->spinBoxMovZ->setValue(ui->widget->movZ);

  if (ui->radioButtonColorBG->isChecked()) {
    ui->horizontalSliderColorB->setValue(ui->widget->colorBB);
    ui->spinBoxColorB->setValue(ui->widget->colorBB);
    ui->horizontalSliderColorG->setValue(ui->widget->colorBG);
    ui->spinBoxColorG->setValue(ui->widget->colorBG);
    ui->horizontalSliderColorR->setValue(ui->widget->colorBR);
    ui->spinBoxColorR->setValue(ui->widget->colorBR);
  } else if (ui->radioButtonColorL->isChecked()) {
    ui->horizontalSliderColorB->setValue(ui->widget->colorLB);
    ui->spinBoxColorB->setValue(ui->widget->colorLB);
    ui->horizontalSliderColorG->setValue(ui->widget->colorLG);
    ui->spinBoxColorG->setValue(ui->widget->colorLG);
    ui->horizontalSliderColorR->setValue(ui->widget->colorLR);
    ui->spinBoxColorR->setValue(ui->widget->colorLR);
  } else {
    ui->horizontalSliderColorB->setValue(ui->widget->colorPB);
    ui->spinBoxColorB->setValue(ui->widget->colorPB);
    ui->horizontalSliderColorG->setValue(ui->widget->colorPG);
    ui->spinBoxColorG->setValue(ui->widget->colorPG);
    ui->horizontalSliderColorR->setValue(ui->widget->colorPR);
    ui->spinBoxColorR->setValue(ui->widget->colorPR);
  }
}

void MainWindow::updateInfoObj() {
  ui->StatusBar->setText(ui->widget->name_file);
  ui->labelNumF->setText(QString::number(ui->widget->obj_data.count_of_facets));
  ui->labelNumV->setText(
      QString::number(ui->widget->obj_data.count_of_vertexes));
}

void MainWindow::signalsMainWindow() {
  signalsPr();
  signalsColor();
  signalsMove();
}

void MainWindow::signalsPr() {
  connect(ui->radioButtonVertexS, &QRadioButton::clicked, ui->widget,
          &glView::radioButtonVertexSF);
  connect(ui->radioButtonVertexC, &QRadioButton::clicked, ui->widget,
          &glView::radioButtonVertexCF);
  connect(ui->radioButtonVertexN, &QRadioButton::clicked, ui->widget,
          &glView::radioButtonVertexNF);
  connect(ui->radioButtonLineD, &QRadioButton::clicked, ui->widget,
          &glView::radioButtonLineDF);
  connect(ui->radioButtonLineS, &QRadioButton::clicked, ui->widget,
          &glView::radioButtonLineSF);
  connect(ui->radioButtonPrP, &QRadioButton::clicked, ui->widget,
          &glView::radioButtonPrPF);
  connect(ui->radioButtonPrC, &QRadioButton::clicked, ui->widget,
          &glView::radioButtonPrCF);
  connect(ui->horizontalSliderTL, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeLineThickness(int)));
  connect(ui->spinBoxTL, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeLineThickness(int)));
  connect(ui->spinBoxSP, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeVertexSize(int)));
  connect(ui->horizontalSliderSP, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeVertexSize(int)));
}

void MainWindow::signalsColor() {
  connect(ui->spinBoxColorB, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeColorB(int)));  //
  connect(ui->horizontalSliderColorB, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeColorB(int)));  //
  connect(ui->horizontalSliderColorG, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeColorG(int)));  //
  connect(ui->spinBoxColorG, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeColorG(int)));  //
  connect(ui->horizontalSliderColorR, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeColorR(int)));  //
  connect(ui->spinBoxColorR, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeColorR(int)));  //
}

void MainWindow::signalsMove() {
  connect(ui->horizontalScrollBarSc, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeSc(int)));
  connect(ui->spinBoxSc, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeSc(int)));
  connect(ui->horizontalScrollBarRotX, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeRotX(int)));
  connect(ui->spinBoxRotX, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeRotX(int)));
  connect(ui->horizontalScrollBarRotY, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeRotY(int)));
  connect(ui->spinBoxRotY, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeRotY(int)));
  connect(ui->horizontalScrollBarRotZ, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeRotZ(int)));
  connect(ui->spinBoxRotZ, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeRotZ(int)));
  connect(ui->horizontalScrollBarMovX, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeMovX(int)));
  connect(ui->spinBoxMovX, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeMovX(int)));
  connect(ui->horizontalScrollBarMovY, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeMovY(int)));
  connect(ui->spinBoxMovY, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeMovY(int)));
  connect(ui->horizontalScrollBarMovZ, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeMovZ(int)));
  connect(ui->spinBoxMovZ, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(changeMovZ(int)));
}

void MainWindow::on_radioButtonColorBG_clicked() {
  ui->widget->choiceColor = 0;
  ui->spinBoxColorR->setValue(ui->widget->colorBR);
  ui->horizontalSliderColorR->setValue(ui->widget->colorBR);
  ui->spinBoxColorG->setValue(ui->widget->colorBG);
  ui->horizontalSliderColorG->setValue(ui->widget->colorBG);
  ui->spinBoxColorB->setValue(ui->widget->colorBB);
  ui->horizontalSliderColorB->setValue(ui->widget->colorBB);
}

void MainWindow::on_radioButtonColorL_clicked() {
  ui->widget->choiceColor = 1;
  ui->spinBoxColorR->setValue(ui->widget->colorLR);
  ui->horizontalSliderColorR->setValue(ui->widget->colorLR);
  ui->spinBoxColorG->setValue(ui->widget->colorLG);
  ui->horizontalSliderColorG->setValue(ui->widget->colorLG);
  ui->spinBoxColorB->setValue(ui->widget->colorLB);
  ui->horizontalSliderColorB->setValue(ui->widget->colorLB);
}

void MainWindow::on_radioButtonColorP_clicked() {
  ui->widget->choiceColor = 2;
  ui->spinBoxColorR->setValue(ui->widget->colorPR);
  ui->horizontalSliderColorR->setValue(ui->widget->colorPR);
  ui->spinBoxColorG->setValue(ui->widget->colorPG);
  ui->horizontalSliderColorG->setValue(ui->widget->colorPG);
  ui->spinBoxColorB->setValue(ui->widget->colorPB);
  ui->horizontalSliderColorB->setValue(ui->widget->colorPB);
}

// скриншот
void MainWindow::on_pushButton_Screenshot_clicked() {
  QFileDialog dialog(this);
  QString screenshot_filename = dialog.getSaveFileName(
      this, "Save screenshot as...",
      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
      "BMP (*.bmp);; JPEG (*.jpeg)");

  if (!(new QFile(screenshot_filename))->open(QIODevice::WriteOnly)) {
    QMessageBox::critical(this, "Warning", "No file has been selected");
  } else {
    QPixmap screenshot = ui->widget->grab();
    screenshot.save(screenshot_filename);
  }
}

void MainWindow::on_pushButton_Gif_clicked() {
  file_name = "/0";
  file_name = QFileDialog::getSaveFileName(
      this, "Save GIF",
      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
      "*.gif");

  ptr_save_file = new QFile(file_name);
  if (!ptr_save_file->open(QIODevice::WriteOnly)) {
    QMessageBox::critical(this, "Warning", "Failed to write file");
  } else {
    start_timer_gif();
  }
}

void MainWindow::start_timer_gif() {
  gif = new QGifImage(QSize(640, 480));
  timerGIF = new QTimer(this);
  connect(timerGIF, &QTimer::timeout, this, &MainWindow::record_gif);
  timerGIF->start(100);
  frame = 0;
}

void MainWindow::record_gif() {
  const QRect rect(0, 0, ui->widget->width(), ui->widget->height());
  QPixmap pixmap = ui->widget->grab(rect);
  ui->pushButton_Gif->setText("Recording Gif (" + QString::number(frame / 10) +
                              " / 5 sec)");
  QImage myImage = pixmap.scaled(640, 480).toImage();
  frame++;
  gif->addFrame(myImage, 100);
  if (frame == 50) {
    timerGIF->stop();
    gif->save(ptr_save_file);
    ptr_save_file->close();
    delete ptr_save_file;
    ptr_save_file = nullptr;
    delete gif;
    gif = nullptr;
    QMessageBox::about(this, "Status", "GIF saved");
    ui->pushButton_Gif->setText("Gif");
    ui->pushButton_Gif->setEnabled(1);
  }
}

void MainWindow::setPr() {
  ui->radioButtonColorBG->setChecked(true);
  if (ui->widget->lineDashed) {
    ui->radioButtonLineS->setChecked(false);
    ui->radioButtonLineD->setChecked(true);
  } else {
    ui->radioButtonLineS->setChecked(true);
    ui->radioButtonLineD->setChecked(false);
  }
  if (ui->widget->parallelPr) {
    ui->radioButtonPrP->setChecked(true);
    ui->radioButtonPrC->setChecked(false);
  } else {
    ui->radioButtonPrC->setChecked(true);
    ui->radioButtonPrP->setChecked(false);
  }
  if ((ui->widget->typeV) == 0) {
    ui->radioButtonVertexN->setChecked(true);
    ui->radioButtonVertexC->setChecked(false);
    ui->radioButtonVertexS->setChecked(false);
  } else if ((ui->widget->typeV) == 1) {
    ui->radioButtonVertexN->setChecked(false);
    ui->radioButtonVertexC->setChecked(true);
    ui->radioButtonVertexS->setChecked(false);
  } else {
    ui->radioButtonVertexN->setChecked(false);
    ui->radioButtonVertexC->setChecked(false);
    ui->radioButtonVertexS->setChecked(true);
  }
  ui->spinBoxColorR->setValue(ui->widget->colorBR);
  ui->horizontalSliderColorR->setValue(ui->widget->colorBR);
  ui->spinBoxColorG->setValue(ui->widget->colorBG);
  ui->horizontalSliderColorG->setValue(ui->widget->colorBG);
  ui->spinBoxColorB->setValue(ui->widget->colorBB);
  ui->horizontalSliderColorB->setValue(ui->widget->colorBB);
  ui->spinBoxSP->setValue(ui->widget->sizeP);
  ui->horizontalSliderSP->setValue(ui->widget->sizeP);
  ui->spinBoxTL->setValue((int)(ui->widget->thickness) - 2);
  ui->horizontalSliderTL->setValue((int)(ui->widget->thickness) - 2);
}
