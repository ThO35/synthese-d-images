#pragma once
#include <iostream>
#include <vector>
#include <array>
#include "glbasimac/glbi_engine.hpp"
#include "tools/vector3d.hpp"
#include "tools/vector4d.hpp"

extern unsigned char minVal;
extern int length, width;
extern std::vector<char> donnes;
extern double scaling;
extern float Sp;
extern std::vector<std::array<float, 5>> zeroPosition;

float hauteur(float charac);

float average(const std::vector<int> &point_adjacent);

float tree_hauteur(int i, int j);

void add_points(float x, float y, float h, float u, float v, std::vector<float> &points, std::vector<float> &colors, std::vector<float> &uvs, std::vector<float> &normals, bool isTree = false);

STP3D::Vector4D relative_2_absolute(const STP3D::Matrix4D& viewMatrix, const STP3D::Vector4D& viewPos, float posX, float posY, float posZ);
