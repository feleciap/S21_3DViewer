#ifndef PARSER_H
#define PARSER_H

#define LINE_MAX_SIZE 1024
#define VERTEXES_MEMORY_SLOT 128
#define FACETS_MEMORY_SLOT 10
#define DEFINE_FACE_MEMORY_SLOT 100

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"

enum ERROR { OK, ERROR, BAD_ALLOC };

int open_file(char *filename, FILE **file);
void parser_choose(FILE **file, data_3d *data, int *err, max_min *max);
int file_parser(char *str, data_3d *data);
int parse_vertex(char *str, data_3d *data, long unsigned int *vertexes_memory,
                 max_min *max);
void data_free(data_3d *data);

#endif  // PARSER_H
