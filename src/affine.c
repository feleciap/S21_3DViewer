#include "affine.h"

void move_x(data_3d *A, double a) {
  for (size_t i = 0; i < A->count_of_vertexes; i++) A->vertexes[i].x += a;
}

void move_y(data_3d *A, double a) {
  for (size_t i = 0; i < A->count_of_vertexes; i++) A->vertexes[i].y += a;
}

void move_z(data_3d *A, double a) {
  for (size_t i = 0; i < A->count_of_vertexes; i++) A->vertexes[i].z += a;
}

void rotation_by_ox(data_3d *A, double angle) {
  for (size_t i = 0; i < A->count_of_vertexes; i++) {
    double temp_y = A->vertexes[i].y;
    double temp_z = A->vertexes[i].z;
    A->vertexes[i].y = cos(angle) * temp_y - sin(angle) * temp_z;
    A->vertexes[i].z = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void rotation_by_oy(data_3d *A, double angle) {
  for (size_t i = 0; i < A->count_of_vertexes; i++) {
    double temp_x = A->vertexes[i].x;
    double temp_z = A->vertexes[i].z;
    A->vertexes[i].x = cos(angle) * temp_x + sin(angle) * temp_z;
    A->vertexes[i].z = -sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

void rotation_by_oz(data_3d *A, double angle) {
  for (size_t i = 0; i < A->count_of_vertexes; i++) {
    double temp_x = A->vertexes[i].x;
    double temp_y = A->vertexes[i].y;
    A->vertexes[i].x = cos(angle) * temp_x - sin(angle) * temp_y;
    A->vertexes[i].y = sin(angle) * temp_x + cos(angle) * temp_y;
  }
}

void scaling(data_3d *A, double scale) {
  // printf("original\n"); //
  // for (size_t i = 0; i < A->count_of_vertexes; i++) printf("%f, %f, %f\n",
  // A->vertexes[i].x, A->vertexes[i].y, A->vertexes[i].z); //
  for (size_t i = 0; i < A->count_of_vertexes; i++) {
    A->vertexes[i].x *= scale;
    A->vertexes[i].y *= scale;
    A->vertexes[i].z *= scale;
  }
  // printf("transformed\n");
  // for (size_t i = 0; i < A->count_of_vertexes; i++) printf("%f, %f, %f\n",
  // A->vertexes[i].x, A->vertexes[i].y, A->vertexes[i].z); //
}
