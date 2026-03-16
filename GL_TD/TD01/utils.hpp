#pragma once
#include <iostream>
#include <vector>

extern unsigned char minVal;
extern int length, width;
extern std::vector<char> donnes;
extern double scaling;
extern float Sp;

float hauteur(float charac);
float average(const std::vector<int> &point_adjacent);
float tree_hauteur(int i, int j);
void add_points(float x, float y, float h, float u, float v, std::vector<float> &points, std::vector<float> &colors, std::vector<float> &uvs, std::vector<float> &normals);
