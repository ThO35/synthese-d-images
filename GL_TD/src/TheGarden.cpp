#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_texture.hpp"
#include "draw_scene.hpp"
#include "tools/shaders.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"
#include <iostream>
#include "draw_scene.hpp"
#include "init_terrain.hpp"

using namespace glbasimac;
using namespace STP3D;

GLBI_Texture myTexture;

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1200;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "The Garden";
static float aspectRatio = 1.0f;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* 3D Engine global variables */
StandardMesh *rectangle;
StandardMesh *a_frame;
IndexedMesh *circle;

/* Terrain properties */
unsigned char minVal = 255;
int length, width;
std::vector<char> donnes;
double scaling = 0.1;
bool is_ground_view = false;

/* Error handling function */
void onError(int error, const char *description)
{
	std::cout << "GLFW Error (" << error << ") : " << description << std::endl;
}

void onWindowResized(GLFWwindow * /*window*/, int width, int height)
{
	aspectRatio = width / (float)height;

	glViewport(0, 0, width, height);
	std::cerr << "Setting 3D projection" << std::endl;
	myEngine.set3DProjection(60.0, aspectRatio, Z_NEAR, Z_FAR);
}

void movement(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		angle_vertical += 1.0f * speed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		angle_vertical -= 1.0f * speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		angle_horizontal += 1.0f * speed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		angle_horizontal -= 1.0f * speed;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pos_camera[0] += cos(deg2rad(angle_horizontal)) * speed;
		pos_camera[1] += sin(deg2rad(angle_horizontal)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pos_camera[0] -= cos(deg2rad(angle_horizontal)) * speed;
		pos_camera[1] -= sin(deg2rad(angle_horizontal)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		pos_camera[0] -= sin(deg2rad(angle_horizontal)) * speed;
		pos_camera[1] += cos(deg2rad(angle_horizontal)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		pos_camera[0] += sin(deg2rad(angle_horizontal)) * speed;
		pos_camera[1] -= cos(deg2rad(angle_horizontal)) * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		pos_camera[2] -= 1.0 * speed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		pos_camera[2] += 1.0 * speed;
}

void onKey(GLFWwindow *window, int key, int /*scancode*/, int action, int /*mods*/)
{
	int is_pressed = (action == GLFW_PRESS);
	int is_repeat = (action == GLFW_REPEAT);
	if (is_pressed)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_L:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case GLFW_KEY_P:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case GLFW_KEY_F:
			is_ground_view = !is_ground_view;
			break;
		}
	}

	if (is_pressed || is_repeat)
	{
		switch (key)
		{
		case GLFW_KEY_E: // Speed up
			speed += 1;
			std::cout << "Speed  up  : " << speed << std::endl;
			break;
		case GLFW_KEY_Q: // Speed down
			speed = (speed <= 1) ? 1 : speed - 1;
			std::cout << "Speed down : " << speed << std::endl;
			break;
		}
	}
}

void onMouseButton(GLFWwindow *window, int button, int action, int /*mods*/)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "Pressed in " << xpos << " " << ypos << std::endl;
	}
}

int main(int argc, char **argv)
{

	if (argc > 1)
	{
		std::string file = argv[1];
		if (!read_file(file))
		{

			return 1;
		}
	}
	else
	{
		if (!read_file())
		{

			return 1;
		}
	}

	/* GLFW initialisation */
	GLFWwindow *window;
	if (!glfwInit())
		return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	std::cout << "Loading GL extension" << std::endl;
	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return -1;
	}

	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, onMouseButton);

	std::cout << "Engine init" << std::endl;
	myEngine.mode2D = false; // Set engine to 3D mode
	myEngine.initGL();
	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	CHECK_GL;

	initScene();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();
		movement(window);
		/* Render begins here */
		glClearColor(0.f, 0.0f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		/* Fix camera position */
		myEngine.mvMatrixStack.loadIdentity();

		if (is_ground_view)
			update_altitude();

		Vector3D viewed_point = Vector3D(pos_camera[0] + cos(deg2rad(angle_horizontal)) * cos(deg2rad(angle_vertical)),
										 pos_camera[1] + sin(deg2rad(angle_horizontal)) * cos(deg2rad(angle_vertical)),
										 pos_camera[2] + sin(deg2rad(angle_vertical)));

		Vector3D up_vector = Vector3D(0.0, 0.0, 1.0); // DO NOT TOUCH IT
		Matrix4D viewMatrix = Matrix4D::lookAt(pos_camera, viewed_point, up_vector);
		myEngine.setViewMatrix(viewMatrix);
		myEngine.updateMvMatrix();

		drawScene();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if (elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
		}
	}

	glfwTerminate();
	return 0;
}
