#include <stdio.h>
#include <stdlib.h>

#ifndef __CUBE_SOLVER_H__
#define __CUBE_SOLVER_H__

char edges[24];
char corners[24]; 
void solve_cube(char*, char*);
void solve_corner(char*);
void solve_edge(char*);
int find_target_corner();

#endif
