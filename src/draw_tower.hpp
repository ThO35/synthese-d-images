#pragma once
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "GLFW/glfw3.h"
#include "glbasimac/glbi_texture.hpp"
#include "tools/shaders.hpp"
#include "tools/stb_image.h"
#include "utils.hpp"
#include <array>
#include <unordered_map>
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

static float next_change = 0.0f;
static float angle = 0.0f;
static int random1 =0;
static int random2 =0;

void tour_de_sauron();