#ifndef STRUCT_H
#define STRUCT_H

#include <stddef.h>  //для size_t

typedef struct dots {
  double x, y, z;
} vertex_3d;

typedef struct facet {
  int *index_arr;
  int num_vertices;
} facet_3d;

typedef struct max_min_coordinate {
  double max_x, max_y, max_z;
  double min_x, min_y, min_z;
} max_min;

typedef struct data {
  size_t count_of_vertexes;
  size_t count_of_facets;
  vertex_3d *vertexes;
  double max_coord;
  facet_3d *facets;
} data_3d;

#endif  // STRUCT_H
