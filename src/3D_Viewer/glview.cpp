#include "glview.h"

glView::glView(QWidget *parent) : QOpenGLWidget{parent} {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

  colorBR = (settings.value("settings/colorBR", 255).toDouble());
  colorBG = (settings.value("settings/colorBG", 255).toDouble());
  colorBB = (settings.value("settings/colorBB", 255).toDouble());
  colorLR = (settings.value("settings/colorLR", 0).toDouble());
  colorLG = (settings.value("settings/colorLG", 0).toDouble());
  colorLB = (settings.value("settings/colorLB", 0).toDouble());
  colorPR = (settings.value("settings/colorPR", 0).toDouble());
  colorPG = (settings.value("settings/colorPG", 0).toDouble());
  colorPB = (settings.value("settings/colorPB", 0).toDouble());
  thickness = (settings.value("settings/thickness", 3).toDouble());
  sizeP = (settings.value("settings/sizeP", 1).toDouble());
  lineDashed = (settings.value("settings/lineDashed", 0).toBool());
  parallelPr = (settings.value("settings/parallelPr", 0).toBool());
  typeV = (settings.value("settings/typeV", 0).toInt());
  choiceColor = (settings.value("settings/choiceColor", 0).toInt());
  scale = 50.0;
  rotX = 0, rotY = 0, rotZ = 0;
  movX = 0, movY = 0, movZ = 0;

  setWindowTitle("");
  setGeometry(400, 200, 800, 600);
}

void glView::radioButtonVertexSF() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  typeV = 2;
  update();
  settings.setValue("settings/typeV", typeV);
}

void glView::radioButtonVertexCF() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  typeV = 1;
  update();
  settings.setValue("settings/typeV", typeV);
}

void glView::radioButtonVertexNF() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  typeV = 0;
  update();
  settings.setValue("settings/typeV", typeV);
}

void glView::radioButtonLineDF() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  lineDashed = 1;
  update();
  settings.setValue("settings/lineDashed", lineDashed);
}

void glView::radioButtonLineSF() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  lineDashed = 0;
  update();
  settings.setValue("settings/lineDashed", lineDashed);
}

void glView::changeLineThickness(int value) {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  thickness = (double)value + 2;
  emit updateMainWindowGl();
  update();
  settings.setValue("settings/thickness", thickness);
}

void glView::changeVertexSize(int value) {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  sizeP = (double)value;
  emit updateMainWindowGl();
  update();
  settings.setValue("settings/sizeP", sizeP);
}

void glView::changeColorR(int value) {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  if (choiceColor == 0) {
    colorBR = (double)value;
    settings.setValue("settings/colorBR", colorBR);
  } else if (choiceColor == 1) {
    colorLR = (double)value;
    settings.setValue("settings/colorLR", colorLR);
  } else {
    colorPR = (double)value;
    settings.setValue("settings/colorPR", colorPR);
  }
  emit updateMainWindowGl();
  update();
}

void glView::changeColorG(int value) {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  if (choiceColor == 0) {
    colorBG = (double)value;
    settings.setValue("settings/colorBG", colorBG);
  } else if (choiceColor == 1) {
    colorLG = (double)value;
    settings.setValue("settings/colorLG", colorLG);
  } else {
    colorPG = (double)value;
    settings.setValue("settings/colorPG", colorPG);
  }
  emit updateMainWindowGl();
  update();
}

void glView::changeColorB(int value) {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  if (choiceColor == 0) {
    colorBB = (double)value;
    settings.setValue("settings/colorBB", colorBB);
  } else if (choiceColor == 1) {
    colorLB = (double)value;
    settings.setValue("settings/colorLB", colorLB);
  } else {
    colorPB = (double)value;
    settings.setValue("settings/colorPB", colorPB);
  }
  emit updateMainWindowGl();
  update();
}

void glView::radioButtonPrPF() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  parallelPr = 1;
  update();
  settings.setValue("settings/parallelPr", parallelPr);
}

void glView::radioButtonPrCF() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  parallelPr = 0;
  update();
  settings.setValue("settings/parallelPr", parallelPr);
}

void glView::updateW() { update(); }

void glView::changeSc(int value) {
  scaling(&obj_data, (double)value / scale);
  scale = (double)value;
  emit updateMainWindowGl();
  update();
}

void glView::slotSetObj() {
  if (obj_data.vertexes != NULL || obj_data.facets != NULL)
    data_free(&obj_data);
  obj_data.max_coord = 1;
  int err = file_parser(name_file, &obj_data);
  if (!err) emit signalUpdateInfoObj();
  update();
}

void glView::changeRotX(int value) {
  rotation_by_ox(&obj_data, ((double)value - rotX) * M_PI / 180.0);
  rotX = (double)value;
  emit updateMainWindowGl();
  update();
}

void glView::changeRotY(int value) {
  rotation_by_oy(&obj_data, ((double)value - rotY) * M_PI / 180.0);
  rotY = (double)value;
  emit updateMainWindowGl();
  update();
}

void glView::changeRotZ(int value) {
  rotation_by_oz(&obj_data, ((double)value - rotZ) * M_PI / 180.0);
  rotZ = (double)value;
  emit updateMainWindowGl();
  update();
}

void glView::changeMovX(int value) {
  move_x(&obj_data, ((double)value - movX) / 50.0);
  movX = (double)value;
  emit updateMainWindowGl();
  update();
}

void glView::changeMovY(int value) {
  move_y(&obj_data, ((double)value - movY) / 50.0);
  movY = (double)value;
  emit updateMainWindowGl();
  update();
}

void glView::changeMovZ(int value) {
  move_z(&obj_data, ((double)value - movZ) / 50.0);
  movZ = (double)value;
  emit updateMainWindowGl();
  update();
}

void glView::initializeGL() {
  initializeOpenGLFunctions();
  obj_data.max_coord = 1;  // TODO parse value in to parser
}

void glView::resizeGL(int w, int h) {
  aspect_ratio = calculateAspectRatio();
  setupView();
  glViewport(0, 0, w, h);  // base point
  glLoadIdentity();        // i don't know
}

void glView::paintGL() {
  glLoadIdentity();
  setupView();
  paintVertexes();
  paintFacets();
}

void glView::setupView() {
  glClearColor(colorBR / 255.0, colorBG / 255.0, colorBB / 255.0,
               1);  // background color
  double distance = obj_data.max_coord * 1.5;
  GLdouble z_near = 0.01;  //ближнее расстояние отсечения
  GLdouble z_far = distance * 10;  //дальнее расстояние отсечения

  if (distance < 1) {
    distance = 2;
  }
  if (!parallelPr) {
    GLdouble fovY = 90;  // Поле зрения в градусах по оси y
    GLdouble fH = tan(fovY / 360 * M_PI) * z_near;
    GLdouble fW = fH * aspect_ratio;
    glFrustum(-fW, fW, -fH, fH, z_near,
              z_far);  // Устанавливает усеченный конус в режим перспективы
    glTranslatef(0, 0, -distance);
  } else {
    glOrtho(-distance * aspect_ratio, distance * aspect_ratio, -distance,
            distance, -distance, z_far);
  }
}

void glView::paintVertexes() {
  if (typeV != 0) {
    glColor3d(colorPR / 255.0, colorPG / 255.0, colorPB / 255.0);  // draw color
    glPointSize(sizeP * 5);
    if (typeV == 1)
      glEnable(GL_POINT_SMOOTH);
    else
      glDisable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);  // start draw
    for (size_t i = 0; i < obj_data.count_of_vertexes;
         ++i) {  //посмотреть i=0 или i=1
      glVertex3d(obj_data.vertexes[i].x, obj_data.vertexes[i].y,
                 obj_data.vertexes[i].z);
    }
    glEnd();
  }
}

void glView::paintFacets() {
  glColor3d(colorLR / 255.0, colorLG / 255.0, colorLB / 255.0);
  glLineWidth(thickness);
  if (lineDashed) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(5, 0x00FF);
  }
  for (size_t i = 0; i < obj_data.count_of_facets; ++i) {
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < obj_data.facets[i].num_vertices; ++j) {
      glVertex3d(obj_data.vertexes[obj_data.facets[i].index_arr[j]].x,
                 obj_data.vertexes[obj_data.facets[i].index_arr[j]].y,
                 obj_data.vertexes[obj_data.facets[i].index_arr[j]].z);
    }
    glEnd();
  }
  if (lineDashed) glDisable(GL_LINE_STIPPLE);
}

double glView::calculateAspectRatio() {
  return static_cast<double>(geometry().width()) /
         static_cast<double>(geometry().height());
}
