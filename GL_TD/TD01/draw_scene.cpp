#include "draw_scene.hpp"
#include "spline.hpp"

// Order UVs
const float UVS[4][2] = {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};

// Camera parameters
Vector3D pos_camera = Vector3D(-30.0, 0.0, 0.0); // Position of the camera
float angle_horizontal{0.0};					 // Angle between x axis and viewpoint
float angle_vertical{0.0};						 // Angle between z axis and viewpoint
float speed{1.0};								 // Camera movement speed

std::vector<float> points{};
Spline trajectory({
		{0, 0, 50},
		{50, 50, 100},
		{0, 100, 150},
		{-50, 50, 200},
		{0, 0, 50}
	});

GLBI_Engine myEngine;
STP3D::StandardMesh grass;
GLBI_Convex_2D_Shape ground{3};
GLBI_Set_Of_Points base{3};
STP3D::IndexedMesh *cube;
STP3D::IndexedMesh *sphere;
STP3D::IndexedMesh *cylindre;
STP3D::StandardMesh *cone;

GLBI_Texture herbeTexture;
GLBI_Texture leaf;
GLBI_Texture wood;
GLBI_Texture liveStar;
float Sp = 1.0f;

std::vector<std::array<float, 5>> zeroPosition = {};

void initTerrain()
{
	std::vector<float> colors{}, uvs{}, normals{};
	srand(time(NULL));

	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < width - 1; j++)
		{
			int coord_A = (i * 256) + j;
			int coord_B = (i * 256) + (j + 1);
			int coord_C = ((i + 1) * 256) + j;
			int coord_D = ((i + 1) * 256) + (j + 1);

			float h_A = donnes[coord_A] == 0 ? tree_hauteur(i, j) : static_cast<float>(static_cast<unsigned char>(donnes[coord_A]));
			float h_B = donnes[coord_B] == 0 ? tree_hauteur(i, j + 1) : static_cast<float>(static_cast<unsigned char>(donnes[coord_B]));
			float h_C = donnes[coord_C] == 0 ? tree_hauteur(i + 1, j) : static_cast<float>(static_cast<unsigned char>(donnes[coord_C]));
			float h_D = donnes[coord_D] == 0 ? tree_hauteur(i + 1, j + 1) : static_cast<float>(static_cast<unsigned char>(donnes[coord_D]));

			int value = rand() % 4;
			// Triangle 1 (A, B, D)
			if (donnes[coord_A] == 0)
			{
				add_points(i, j, h_A, UVS[value][0], UVS[value][1], points, colors, uvs, normals, true);
			}
			else
			{
				add_points(i, j, h_A, UVS[value][0], UVS[value][1], points, colors, uvs, normals);
			}
			add_points(i, j + 1, h_B, UVS[(value + 1) % 4][0], UVS[(value + 1) % 4][1], points, colors, uvs, normals);
			add_points(i + 1, j + 1, h_D, UVS[(value + 2) % 4][0], UVS[(value + 2) % 4][1], points, colors, uvs, normals);

			// Triangle 2 (A, C, D)
			add_points(i, j, h_A, UVS[value][0], UVS[value][1], points, colors, uvs, normals);
			add_points(i + 1, j, h_C, UVS[(value + 3) % 4][0], UVS[(value + 3) % 4][1], points, colors, uvs, normals);
			add_points(i + 1, j + 1, h_D, UVS[(value + 2) % 4][0], UVS[(value + 2) % 4][1], points, colors, uvs, normals);
		}
	}

	// --- CONFIGURATION DU StandardMesh ---
	grass.setNbElt(points.size() / 3);
	grass.addOneBuffer(0, 3, points.data(), "Coordinates", true);
	grass.addOneBuffer(1, 3, normals.data(), "Normals", true);
	grass.addOneBuffer(2, 2, uvs.data(), "UVs", true);
	grass.addOneBuffer(3, 3, colors.data(), "Colors", true);
	grass.createVAO(); // Enregistrement OpenGL
}

void initScene()
{

	myEngine.switchToPhongShading();
	myEngine.setLightPosition(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 1.0f}, 0);
	myEngine.setLightIntensity(STP3D::Vector3D{100.0f, 100.0f, 100.0f}, 0);
	myEngine.addALight(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 1.0f}, STP3D::Vector3D{100.0f, 100.0f, 100.0f});
	myEngine.switchToFlatShading();

	cone = basicCone(1, 1);
	cylindre = basicCylinder(1., .5, 100);
	cylindre->createVAO();
	sphere = basicSphere(1);
	sphere->createVAO();
	cube = basicCube(0.5);
	cube->createVAO();
	std::vector<float> baseCarre{-10.0, -10.0, 0.0,
								 10.0, -10.0, 0.0,
								 10.0, 10.0, 0.0,
								 -10.0, 10.0, 0.0};
	ground.initShape(baseCarre);
	ground.changeNature(GL_TRIANGLE_FAN);

	std::vector<float> pointsBase{0.0, 0.0, 0.0,
								  10.0, 0.0, 0.0,
								  0.0, 0.0, 0.0,
								  0.0, 10.0, 0.0,
								  0.0, 0.0, 0.0,
								  0.0, 0.0, 10.0};
	std::vector<float> color{1.0, 0.0, 0.0,
							 1.0, 0.0, 0.0,
							 0.0, 1.0, 0.0,
							 0.0, 1.0, 0.0,
							 0.0, 0.0, 1.0,
							 0.0, 0.0, 1.0};

	base.initSet(pointsBase, color);
	base.changeNature(GL_LINES);

	initTerrain();

	glActiveTexture(GL_TEXTURE0);

	int width_texture, height_texture, n;

	auto pixels = stbi_load("../assets/textures/herbe.png", &width_texture, &height_texture, &n, 0);
	if (pixels == nullptr)
	{
		std::cout << "Debilus" << std::endl;
	}
	herbeTexture.createTexture();
	herbeTexture.attachTexture();
	herbeTexture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	herbeTexture.loadImage(width_texture, height_texture, n, pixels);
	herbeTexture.detachTexture();
	stbi_image_free(pixels);

	pixels = stbi_load("../assets/textures/images.jpg", &width_texture, &height_texture, &n, 0);
	if (pixels == nullptr)
	{
		std::cout << "Debilus" << std::endl;
	}
	leaf.createTexture();
	leaf.attachTexture();
	leaf.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	leaf.loadImage(width_texture, height_texture, n, pixels);
	leaf.detachTexture();
	stbi_image_free(pixels);

	pixels = stbi_load("../assets/textures/wood.jpg", &width_texture, &height_texture, &n, 0);
	if (pixels == nullptr)
	{
		std::cout << "Debilus" << std::endl;
	}
	wood.createTexture();
	wood.attachTexture();
	wood.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	wood.loadImage(width_texture, height_texture, n, pixels);
	wood.detachTexture();
	stbi_image_free(pixels);

	pixels = stbi_load("../assets/textures/moon.png", &width_texture, &height_texture, &n, 0);
	if (pixels == nullptr)
	{
		std::cout << "Debilus" << std::endl;
	}
	liveStar.createTexture();
	liveStar.attachTexture();
	liveStar.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	liveStar.loadImage(width_texture, height_texture, n, pixels);
	liveStar.detachTexture();
	stbi_image_free(pixels);
}

void drawFrame()
{
	base.drawSet();
}

void leaf_minecraf(int sizeTree, int seed)
{
	srand(seed);
	float cubeSize = 0.5f;
	float rayon = (sizeTree / 4.0f) + 1.0f;
	myEngine.setFlatColor(1, 0.0, 0.);
	for (int z = -rayon; z <= rayon; z++)
	{
		for (int x = -rayon; x <= rayon; x++)
		{
			for (int y = -rayon; y <= rayon; y++)
			{
				float distSq = x * x + y * y + z * z;

				if (distSq < rayon * rayon)
				{
					if (rand() % 15 > 5)
					{
						myEngine.mvMatrixStack.pushMatrix();
						myEngine.mvMatrixStack.addTranslation({x * cubeSize,
															   y * cubeSize,
															   (sizeTree + z) * cubeSize});
						myEngine.updateMvMatrix();
						cube->draw();
						myEngine.mvMatrixStack.popMatrix();
					}
				}
			}
		}
	}
}

void tree_minecraft(int hauteur, int seed)
{
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.activateTexturing(true);
	wood.attachTexture();
	float cubeSize = 0.5f;
	myEngine.setFlatColor(0., 0., 1);
	for (int i = 0; i < hauteur; i++)
	{
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, i * cubeSize});
		myEngine.updateMvMatrix();
		cube->draw();
		myEngine.mvMatrixStack.popMatrix();
	}
	wood.detachTexture();
	myEngine.activateTexturing(false);
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.activateTexturing(true);
	leaf.attachTexture();
	leaf_minecraf(hauteur, seed);
	leaf.detachTexture();
	myEngine.activateTexturing(false);
	myEngine.mvMatrixStack.popMatrix();
}

void moon()
{
	myEngine.mvMatrixStack.pushMatrix();

	auto angle = ((M_PI / 180.0f) * glfwGetTime() * 15) + M_PI;

	myEngine.switchToPhongShading();

	auto lightY = length * std::sin(-angle);
	auto lightZ = length * std::cos(-angle);

	myEngine.setLightPosition(STP3D::Vector4D(0.0f, lightY, lightZ, 0.0f), 1);
	myEngine.setLightIntensity(STP3D::Vector3D(0.25f, 0.25f, 0.113f), 1);

	myEngine.switchToFlatShading();

	myEngine.activateTexturing(true);
	liveStar.attachTexture();
	myEngine.mvMatrixStack.addRotation(angle, {1, 0, 0});
	myEngine.mvMatrixStack.addTranslation({1.0f, 1.0f, -length});
	myEngine.updateMvMatrix();
	sphere->draw();
	liveStar.detachTexture();
	myEngine.activateTexturing(false);
	myEngine.mvMatrixStack.popMatrix();
}

void sun()
{
	myEngine.mvMatrixStack.pushMatrix();

	float angle = (M_PI / 180.0f) * glfwGetTime() * 15;

	myEngine.switchToPhongShading();

	float lightY = length * std::sin(-angle);
	float lightZ = length * std::cos(-angle);

	myEngine.setLightPosition(STP3D::Vector4D(0.0f, lightY, lightZ, 0.0f), 0);
	myEngine.setLightIntensity(STP3D::Vector3D(1.0f, 1.0f, 1.0f), 0);

	myEngine.switchToFlatShading();

	myEngine.setFlatColor(1.0f, 1.0f, 0.0f);
	myEngine.mvMatrixStack.addRotation(angle, {1.0f, 0.0f, 0.0f});
	myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, length});
	myEngine.updateMvMatrix();
	sphere->draw();

	myEngine.mvMatrixStack.popMatrix();
}

void sapin()
{

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(0., 0., 1);
	myEngine.mvMatrixStack.addRotation(M_PI / 2, {1., 0., 0.});
	myEngine.mvMatrixStack.addHomothety({1., 3., 1.});
	myEngine.updateMvMatrix();
	cylindre->draw();
	cone->draw();
	myEngine.mvMatrixStack.popMatrix();

	// myEngine.mvMatrixStack.pushMatrix();
	// myEngine.setFlatColor(1., 0, 0);
	// myEngine.mvMatrixStack.addTranslation({0., 0., 3.});
	// myEngine.mvMatrixStack.addHomothety(0.5);
	// myEngine.updateMvMatrix();
	// sphere->draw();
	// myEngine.mvMatrixStack.popMatrix();

	// auto j = 0.25;
	//  for (int i = 0; i < 5; i++)
	//  {
	//  	myEngine.setFlatColor(1., 0., 1);
	//  	myEngine.mvMatrixStack.pushMatrix();
	//  	myEngine.mvMatrixStack.addTranslation({1., 1., float(1 - j)});
	//  	myEngine.mvMatrixStack.addHomothety({1. * j, 1. * j, 0.5});
	//  	myEngine.updateMvMatrix();
	//  	sphere->draw();
	//  	myEngine.mvMatrixStack.popMatrix();
	//  	j += 0.5;
	//  }
}


void draw_tmp()
{
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.pushMatrix();
			myEngine.mvMatrixStack.addTranslation({0.0f, 10.f, 0.f});
			myEngine.setFlatColor(0.0f, 1.0f, 0.0f);
			myEngine.updateMvMatrix();
			sphere->draw();
		myEngine.mvMatrixStack.popMatrix();
		myEngine.setFlatColor(0.0f, 1.0f, 1.0f);
		myEngine.updateMvMatrix();
		sphere->draw();
		myEngine.mvMatrixStack.pushMatrix();
			myEngine.mvMatrixStack.addTranslation({0.0f, -10.f, 0.f});
			myEngine.setFlatColor(0.0f, 0.0f, 1.0f);
			myEngine.updateMvMatrix();
			sphere->draw();
		myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();
}


void show_trajectory()
{
	for (; !trajectory.simule(0.01f); )
	{
		myEngine.mvMatrixStack.pushMatrix();
			myEngine.mvMatrixStack.addTranslation(trajectory.getSimulPosition());
			myEngine.mvMatrixStack.addHomothety({0.2f, 0.2f, 0.2f});
			myEngine.updateMvMatrix();
			sphere->draw();
			// sapin();
		myEngine.mvMatrixStack.popMatrix();
	}
}

void drawScene()
{

	moon();
	sun();
	myEngine.switchToPhongShading();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.activateTexturing(true);
	herbeTexture.attachTexture();
	myEngine.updateMvMatrix();
	grass.draw();
	herbeTexture.detachTexture();
	myEngine.activateTexturing(false);
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.updateMvMatrix();
	drawFrame();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(0.2, 0.0, 0.0);

	myEngine.activateTexturing(true);
	herbeTexture.attachTexture();
	myEngine.updateMvMatrix();
	ground.drawShape();
	herbeTexture.detachTexture();
	myEngine.activateTexturing(false);
	myEngine.mvMatrixStack.popMatrix();
	//sapin();

	for (const auto &zero : zeroPosition)
	{
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation(STP3D::Vector3D(zero[0], zero[1], zero[2]));

		myEngine.updateMvMatrix();
		tree_minecraft(static_cast<int>(zero[3]), static_cast<int>(zero[4]));
		myEngine.mvMatrixStack.popMatrix();
	}

	myEngine.switchToFlatShading();

	show_trajectory();

	myEngine.mvMatrixStack.pushMatrix();
		trajectory.update(0.01f);
		myEngine.mvMatrixStack.addTranslation(trajectory.getPosition());
		myEngine.mvMatrixStack.addRotation(trajectory.getYaw(), {0.0f, 1.0f, 0.0f});
		myEngine.mvMatrixStack.addRotation(trajectory.getPitch(), {1.0f, 0.0f, 0.0f});
		myEngine.updateMvMatrix();
		draw_tmp();
	myEngine.mvMatrixStack.popMatrix();
}

void update_altitude()
{
	// Born to map
	if (pos_camera[0] <= -(length / 2))
		pos_camera[0] = -(length / 2);
	if (pos_camera[0] >= length / 2 - 1)
		pos_camera[0] = length / 2 - 1;
	if (pos_camera[1] <= -(width / 2))
		pos_camera[1] = -(width / 2);
	if (pos_camera[1] >= width / 2 - 1)
		pos_camera[1] = width / 2 - 1;
	int x = length / 2 + pos_camera[0];
	int y = width / 2 + pos_camera[1];
	int coord_a = x * (length - 1) + y;
	pos_camera[2] = points[coord_a * 18 + 2] + 1;
}