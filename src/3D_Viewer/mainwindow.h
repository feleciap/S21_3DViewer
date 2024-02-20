#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QTimer>

#include "gif/qgifimage_p.h"

#define ORGANIZATION_NAME "s21-school"
#define APPLICATION_NAME "3DViewer_v1.0"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QGifImage* gif;

 signals:
  void signalSetObj();

 private slots:
  void on_pushButton_Open_File_clicked();
  void on_pushButton_Screenshot_clicked();
  void on_radioButtonColorBG_clicked();
  void on_radioButtonColorL_clicked();
  void on_radioButtonColorP_clicked();
  void on_pushButton_Gif_clicked();
  void start_timer_gif();
  void record_gif();
  void setPr();
  void updateMainWindowMW();
  void updateInfoObj();
  void signalsMainWindow();
  void signalsPr();
  void signalsColor();
  void signalsMove();

 public slots:

 private:
  Ui::MainWindow* ui;
  QSystemTrayIcon* trayIcon;
  QString file_name;
  QTimer* timerGIF;  // идентификатор таймера
  int frame;
  QFile* ptr_save_file;
};

//};
#endif  // MAINWINDOW_H
