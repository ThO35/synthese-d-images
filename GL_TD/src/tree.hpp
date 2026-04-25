#pragma once
#include <unordered_map>
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_texture.hpp"
#include "tools/basic_mesh.hpp"
#include "GLFW/glfw3.h"
using namespace glbasimac;

/* OpenGL Engine */
extern GLBI_Engine myEngine;

/* Basic shape */
extern STP3D::StandardMesh *repere;
extern STP3D::IndexedMesh  *cube;
extern STP3D::IndexedMesh  *sphere;
extern STP3D::IndexedMesh  *cylindre;
extern STP3D::StandardMesh *cone;
extern std::unordered_map<std::string, GLBI_Texture> textures;

void tree_minecraft(int hauteur, int seed);
