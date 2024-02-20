#ifndef AFFINE_H
#define AFFINE_H

#include <math.h>
#include <stdio.h>

#include "parser.h"

void move_x(data_3d *A, double a);
void move_y(data_3d *A, double a);
void move_z(data_3d *A, double a);
void rotation_by_ox(data_3d *A, double angle);
void rotation_by_oy(data_3d *A, double angle);
void rotation_by_oz(data_3d *A, double angle);
void scaling(data_3d *A, double scale);

#endif