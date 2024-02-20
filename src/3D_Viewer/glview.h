#ifndef GLVIEW_H
#define GLVIEW_H

#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QWidget>
#include <QtOpenGL>

#define ORGANIZATION_NAME "s21-school"
#define APPLICATION_NAME "3DViewer_v1.0"

extern "C" {
#include "../affine.h"
#include "../parser.h"
#include "../struct.h"
}

class glView : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  glView(QWidget* parent = nullptr);
  data_3d obj_data = {0, 0, NULL, 0, NULL};
  double colorBR;
  double colorBG;
  double colorBB;
  double colorLR;
  double colorLG;
  double colorLB;
  double colorPR;
  double colorPG;
  double colorPB;
  double thickness;
  double sizeP;
  bool lineDashed;
  bool parallelPr;
  short typeV;
  short choiceColor;
  double scale;
  double rotX, rotY, rotZ, movX, movY, movZ;
  char* name_file;

 public slots:
  void radioButtonVertexSF();
  void radioButtonVertexCF();
  void radioButtonVertexNF();
  void radioButtonLineDF();
  void radioButtonLineSF();
  void changeLineThickness(int value);
  void changeVertexSize(int value);
  void changeColorR(int value);
  void changeColorG(int value);
  void changeColorB(int value);
  void radioButtonPrPF();
  void radioButtonPrCF();
  void updateW();
  void changeSc(int value);
  void slotSetObj();
  void changeRotX(int value);
  void changeRotY(int value);
  void changeRotZ(int value);
  void changeMovX(int value);
  void changeMovY(int value);
  void changeMovZ(int value);

 signals:
  void updateMainWindowGl();
  void signalUpdateInfoObj();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void setupView();
  void paintVertexes();
  void paintFacets();
  double calculateAspectRatio();
  double aspect_ratio;
};
#endif  // GLVIEW_H
