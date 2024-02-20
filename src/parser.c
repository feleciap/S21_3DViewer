#include "parser.h"

#include <ctype.h>

#include "affine.h"

void data_free(data_3d *data) {
  if (data->vertexes != NULL && data->count_of_vertexes) {
    free(data->vertexes);
    data->vertexes = NULL;
  }
  if (data->facets != NULL) {
    for (size_t i = 0; i < data->count_of_facets; ++i) {
      free(data->facets[i].index_arr);
      data->facets[i].index_arr = NULL;
    }
    free(data->facets);
    data->facets = NULL;
  }
  data->count_of_facets = 0;
  data->count_of_vertexes = 0;
  data->max_coord = 0;
}

int open_file(char *filename, FILE **file) {
  int err = ERROR;
  *file = fopen(filename, "r");
  if (*file == NULL) {
    fprintf(stderr, "\x1b[32m%s: No such file\x1b[0m\n", filename);
  } else {
    err = OK;
  }
  return err;
}

int index_convertion(int index, int count_vert) {
  return index < 0 ? count_vert + index : index - 1;
}

void max_min_init(data_3d *data, vertex_3d *vertex, max_min *max_min) {
  if (data->count_of_vertexes == 0) {
    max_min->max_x = max_min->min_x = vertex->x;
    max_min->max_y = max_min->min_y = vertex->y;
    max_min->max_z = max_min->min_z = vertex->z;
  } else {
    if (vertex->x < max_min->min_x) {
      max_min->min_x = vertex->x;
    }
    if (vertex->y < max_min->min_y) {
      max_min->min_y = vertex->y;
    }
    if (vertex->z < max_min->min_z) {
      max_min->min_z = vertex->z;
    }
    if (vertex->x > max_min->max_x) {
      max_min->max_x = vertex->x;
    }
    if (vertex->y > max_min->max_y) {
      max_min->max_y = vertex->y;
    }
    if (vertex->z > max_min->max_z) {
      max_min->max_z = vertex->z;
    }
  }
}

void alignment(data_3d *data, max_min *max_min) {
  move_x(data, -(max_min->min_x + (max_min->max_x - max_min->min_x) / 2));
  move_y(data, -(max_min->min_y + (max_min->max_y - max_min->min_y) / 2));
  move_z(data, -(max_min->min_z + (max_min->max_z - max_min->min_z) / 2));
  double sk = max_min->max_x - max_min->min_x;
  if (sk < (max_min->max_y - max_min->min_y)) {
    sk = (max_min->max_y - max_min->min_y);
    if (sk < (max_min->max_z - max_min->min_z))
      sk = (max_min->max_z - max_min->min_z);
  }
  scaling(data, 1.0 / sk);
}

int parse_vertex(char *str, data_3d *data, long unsigned int *vertexes_memory,
                 max_min *max_min) {
  int err = OK;
  vertex_3d vertex = {0};
  if (sscanf(&str[2], "%lf %lf %lf", &vertex.x, &vertex.y, &vertex.z) == 3) {
    max_min_init(data, &vertex, max_min);
    data->count_of_vertexes++;
    if (data->vertexes == NULL) {
      data->vertexes = malloc(*vertexes_memory * sizeof(vertex_3d));
      if (data->vertexes == NULL) {
        err = BAD_ALLOC;  // добавить в parse_facets
      }
    } else if (data->count_of_vertexes > *vertexes_memory) {
      *vertexes_memory += VERTEXES_MEMORY_SLOT;
      vertex_3d *tmp =
          realloc(data->vertexes, (*vertexes_memory * sizeof(vertex_3d)));
      if (tmp == NULL) {  //добавил проверку
        err = BAD_ALLOC;
        data->count_of_vertexes--;
        data_free(data);
      } else {
        data->vertexes = tmp;
        tmp = NULL;
      }
    }
    if (err == OK) {
      data->vertexes[data->count_of_vertexes - 1].x = vertex.x;  //добавил -1
      data->vertexes[data->count_of_vertexes - 1].y = vertex.y;
      data->vertexes[data->count_of_vertexes - 1].z = vertex.z;
    }
  } else {
    err = ERROR;
    data_free(data);
  }
  return err;
}

int facets_realloc(data_3d *data, size_t *facets_memory) {
  int err = OK;
  if (*facets_memory < data->count_of_facets) {
    *facets_memory += FACETS_MEMORY_SLOT;
    facet_3d *tmp_ptr =
        realloc(data->facets, *facets_memory * sizeof(facet_3d));
    if (tmp_ptr == NULL) {
      err = BAD_ALLOC;
      data->count_of_facets--;
      data_free(data);
    } else {
      data->facets = tmp_ptr;
      tmp_ptr = NULL;
    }
  }
  return err;
}

int index_arr_realloc(data_3d *data, int *index_memory) {
  int err = OK;
  *index_memory = DEFINE_FACE_MEMORY_SLOT;
  if (data->facets[data->count_of_facets - 1].num_vertices > *index_memory) {
    *index_memory *= 2;
    int *temp_ptr = realloc(data->facets[data->count_of_facets - 1].index_arr,
                            (*index_memory * sizeof(int)));
    if (temp_ptr == NULL) {
      err = ERROR;
      free(data->facets[data->count_of_facets - 1].index_arr);
    } else {
      data->facets[data->count_of_facets - 1].index_arr = temp_ptr;
      temp_ptr = NULL;
    }
  }
  return err;
}

int parse_facets(char *str, data_3d *data, size_t *facets_memory) {
  int err = OK;
  int index_value = 0;
  int index_memory = DEFINE_FACE_MEMORY_SLOT;
  data->count_of_facets++;
  if (data->facets == NULL) {
    data->facets = malloc(sizeof(facet_3d) * *facets_memory);
  }
  err = facets_realloc(data, facets_memory);
  data->facets[data->count_of_facets - 1].index_arr =
      malloc(sizeof(int) * index_memory);
  int i = 0;
  data->facets[data->count_of_facets - 1].num_vertices = 0;

  while (*str != 0x00 && !err) {
    if (*str == ' ' && (isdigit(str[1]) || *(str + 1) == '-')) {
      if (sscanf(str, " %d", &index_value) == 1) {
        if (index_value <= (int)data->count_of_vertexes) {
          data->facets[data->count_of_facets - 1].num_vertices++;
          err = index_arr_realloc(data, &index_memory);
          data->facets[data->count_of_facets - 1].index_arr[i] =
              index_convertion(index_value, data->count_of_vertexes);

          ++i;
        } else {
          err = ERROR;
        }
      } else if (str[1] != 0x00) {
        err = ERROR;
      }
    }
    str++;
  }
  return err;
}

void parser_choose(FILE **file, data_3d *data, int *err, max_min *max) {
  long unsigned int vertexes_memory = VERTEXES_MEMORY_SLOT;
  long unsigned int facets_memory = FACETS_MEMORY_SLOT;
  char buffer_line[LINE_MAX_SIZE];
  while (fgets(buffer_line, LINE_MAX_SIZE, *file) != NULL && *err == OK) {
    if (buffer_line[0] == 'v' && buffer_line[1] == ' ') {
      parse_vertex(buffer_line, data, &vertexes_memory, max);
    } else if (buffer_line[0] == 'f' && buffer_line[1] == ' ') {
      *err = parse_facets(buffer_line, data, &facets_memory);
    }
  }
}

int file_parser(char *str, data_3d *data) {
  FILE *file;
  max_min max_min;
  int err = open_file(str, &file);
  if (err == OK) {
    parser_choose(&file, data, &err, &max_min);
  }
  alignment(data, &max_min);
  fclose(file);
  return err;
}
