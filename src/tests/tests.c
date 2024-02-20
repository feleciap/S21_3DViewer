#include "test.h"
#include <math.h>

START_TEST(file_parser_01) {
  char *file_name = "3d_models/cube.obj";
  data_3d data = {0};
  file_parser(file_name, &data);
  data_free (&data);
}
END_TEST

START_TEST(file_parser_02) {
  char *file_name = "3d_models/skull_1.obj";
  data_3d data = {0};
  file_parser(file_name, &data);
  data_free (&data);
}
END_TEST

START_TEST(file_parser_03) {
  char *file_name = "3d_models/err.obj";
  data_3d data = {0};
  file_parser(file_name, &data);
  data_free (&data);
}
END_TEST

START_TEST(file_parser_04) {
  char *file_name = "3d_models/err1.obj";
  data_3d data = {0};
  file_parser(file_name, &data);
  data_free (&data);
}
END_TEST

START_TEST(open_file_01) {
  char *file_name = "3d_models/cube.obj";
  FILE *file;
  size_t err = open_file(file_name, &file);
  ck_assert_uint_eq(err, OK);
}
END_TEST

START_TEST(open_file_02) {
  char *file_name = "3d_models/file.obj";
  FILE *file;
  int err = open_file(file_name, &file);
  ck_assert_int_eq(err, ERROR);
}
END_TEST

START_TEST(affine_move_x) {
  char *file_name = "3d_models/cube.obj";
  data_3d data = {0};
  file_parser(file_name, &data);
  double trueRes[8][3] = {{0.5, -0.5, 0.5},  {1.5, -0.5, 0.5}, {0.5, 0.5, 0.5},
                          {1.5, 0.5, 0.5},   {0.5, 0.5, -0.5}, {1.5, 0.5, -0.5},
                          {0.5, -0.5, -0.5}, {1.5, -0.5, -0.5}};
  move_x(&data, 1);
  for (size_t i = 0; i < data.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(data.vertexes[i].x, trueRes[i][0], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].y, trueRes[i][1], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].z, trueRes[i][2], 1e-6);
  }
  data_free (&data);
}
END_TEST

START_TEST(affine_move_y) {
  char *file_name = "3d_models/cube.obj";
  data_3d data = {0};
  file_parser(file_name, &data);
  double trueRes[8][3] = {
      {-0.5, 0.5, 0.5},  {0.5, 0.5, 0.5},  {-0.5, 1.5, 0.5},  {0.5, 1.5, 0.5},
      {-0.5, 1.5, -0.5}, {0.5, 1.5, -0.5}, {-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5}};
  move_y(&data, 1);
  for (size_t i = 0; i < data.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(data.vertexes[i].x, trueRes[i][0], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].y, trueRes[i][1], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].z, trueRes[i][2], 1e-6);
  }
  data_free (&data);
}
END_TEST

START_TEST(affine_move_z) {
  char *file_name = "3d_models/cube.obj";
  data_3d data = {0};
  file_parser(file_name, &data);
  double trueRes[8][3] = {{-0.5, -0.5, 1.5}, {0.5, -0.5, 1.5}, {-0.5, 0.5, 1.5},
                          {0.5, 0.5, 1.5},   {-0.5, 0.5, 0.5}, {0.5, 0.5, 0.5},
                          {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5}};
  move_z(&data, 1);
  for (size_t i = 0; i < data.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(data.vertexes[i].x, trueRes[i][0], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].y, trueRes[i][1], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].z, trueRes[i][2], 1e-6);
  }
  data_free (&data);
}
END_TEST

START_TEST(affine_rotation_x) {
  char *file_name = "3d_models/cube.obj";
  data_3d data = {0};
  file_parser(file_name, &data);
  double trueRes[8][3] = {{-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5},
                          {-0.5, -0.5, 0.5},  {0.5, -0.5, 0.5},
                          {-0.5, 0.5, 0.5},   {0.5, 0.5, 0.5},
                          {-0.5, 0.5, -0.5},  {0.5, 0.5, -0.5}};
  rotation_by_ox(&data, s21_PI / 2.0);
  for (size_t i = 0; i < data.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(data.vertexes[i].x, trueRes[i][0], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].y, trueRes[i][1], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].z, trueRes[i][2], 1e-6);
  }
  data_free (&data);
}
END_TEST

START_TEST(affine_rotation_y) {
  char *file_name = "3d_models/cube.obj";
  data_3d data = {0};
  file_parser(file_name, &data);
  double trueRes[8][3] = {{0.5, -0.5, 0.5},  {0.5, -0.5, -0.5},
                          {0.5, 0.5, 0.5},   {0.5, 0.5, -0.5},
                          {-0.5, 0.5, 0.5},  {-0.5, 0.5, -0.5},
                          {-0.5, -0.5, 0.5}, {-0.5, -0.5, -0.5}};
  rotation_by_oy(&data, s21_PI / 2.0);
  for (size_t i = 0; i < data.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(data.vertexes[i].x, trueRes[i][0], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].y, trueRes[i][1], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].z, trueRes[i][2], 1e-6);
  }
  data_free (&data);
}
END_TEST

START_TEST(affine_rotation_z) {
  char *file_name = "3d_models/cube.obj";
  data_3d data = {0};
  file_parser(file_name, &data);
  double trueRes[8][3] = {{0.5, -0.5, 0.5},   {0.5, 0.5, 0.5},
                          {-0.5, -0.5, 0.5},  {-0.5, 0.5, 0.5},
                          {-0.5, -0.5, -0.5}, {-0.5, 0.5, -0.5},
                          {0.5, -0.5, -0.5},  {0.5, 0.5, -0.5}};
  rotation_by_oz(&data, s21_PI / 2.0);
  for (size_t i = 0; i < data.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(data.vertexes[i].x, trueRes[i][0], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].y, trueRes[i][1], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].z, trueRes[i][2], 1e-6);
  }
  data_free (&data);
}
END_TEST

START_TEST(affine_scaling) {
  char *file_name = "3d_models/cube.obj";
  data_3d data = {0};
  file_parser(file_name, &data);
  double trueRes[8][3] = {{-0.25, -0.25, 0.25},  {0.25, -0.25, 0.25},
                          {-0.25, 0.25, 0.25},   {0.25, 0.25, 0.25},
                          {-0.25, 0.25, -0.25},  {0.25, 0.25, -0.25},
                          {-0.25, -0.25, -0.25}, {0.25, -0.25, -0.25}};
  scaling(&data, 0.5);
  for (size_t i = 0; i < data.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(data.vertexes[i].x, trueRes[i][0], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].y, trueRes[i][1], 1e-6);
    ck_assert_double_eq_tol(data.vertexes[i].z, trueRes[i][2], 1e-6);
  }
  data_free (&data);
}
END_TEST

START_TEST(max_min_init) {
  printf("max_min_init\n");
  char *file_name = "3d_models/object_1.obj";
  data_3d data1 = {0};
  file_parser(file_name, &data1);
  double trueRes[8][3] = {{0, -0.0625, 0.25},  {0.25, -0.0625, 0.25},
                          {0, 0.3125, 0.25},   {0.25, 0.1875, 0.50},
                          {0, 0.1875, 0.},  {0.25, 0.1875, 0},
                          {-0.25, -0.0625, 0}, {0.25, -0.3125, -0.50}};
  scaling(&data1, 1.0);
  for (size_t i = 0; i < data1.count_of_vertexes; i++) {
    ck_assert_double_eq_tol(data1.vertexes[i].x, trueRes[i][0], 1e-6);
    ck_assert_double_eq_tol(data1.vertexes[i].y, trueRes[i][1], 1e-6);
    ck_assert_double_eq_tol(data1.vertexes[i].z, trueRes[i][2], 1e-6);
  }
  data_free (&data1);
}
END_TEST

Suite *test_file_parser() {
  Suite *suite = suite_create("test_suite");
  TCase *tc = tcase_create("test");
  tcase_add_test(tc, file_parser_01);
  tcase_add_test(tc, file_parser_02);
  tcase_add_test(tc, file_parser_03);
  tcase_add_test(tc, file_parser_04);
  tcase_add_test(tc, open_file_01);
  tcase_add_test(tc, open_file_02);
  tcase_add_test(tc, affine_move_x);
  tcase_add_test(tc, affine_move_y);
  tcase_add_test(tc, affine_move_z);
  tcase_add_test(tc, affine_rotation_x);
  tcase_add_test(tc, affine_rotation_y);
  tcase_add_test(tc, affine_rotation_z);
  tcase_add_test(tc, affine_scaling);
  tcase_add_test(tc, max_min_init);
  suite_add_tcase(suite, tc);

  return suite;
}
