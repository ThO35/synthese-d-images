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


extern std::unordered_map<std::string, GLBI_Texture> textures;
extern STP3D::IndexedMesh  *sphere;

void draw_sun();
void draw_moon();
void draw_skybox();