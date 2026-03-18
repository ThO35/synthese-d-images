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
using namespace glbasimac;

/* Camera parameters and functions */
static const float Z_NEAR{0.1f};
static const float Z_FAR{500.f};
extern Vector3D pos_camera;    // Position of the camera
extern float angle_horizontal; // Angle between x axis and viewpoint
extern float angle_vertical;   // Angle between z axis and viewpoint
extern float speed;            // Camera movement speed

/* OpenGL Engine */
extern GLBI_Engine myEngine;

/* Terrain parameters */
extern unsigned char minVal;
extern int length, width;
extern std::vector<char> donnes;
extern double scaling;

void initScene();

void drawScene();

void initTerrain();

void update_altitude();
