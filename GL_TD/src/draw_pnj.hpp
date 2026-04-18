#pragma once

#include "glbasimac/glbi_engine.hpp"
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

void drawPNJ();
