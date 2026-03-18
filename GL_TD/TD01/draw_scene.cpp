#include "draw_scene.hpp"

// Order UVs
const float UVS[4][2] = {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};

// Camera parameters
Vector3D pos_camera = Vector3D(-30.0, 0.0, 0.0);	// Position of the camera
float angle_horizontal{0.0}; 						// Angle between x axis and viewpoint
float angle_vertical{0.0};	 						// Angle between z axis and viewpoint
float speed{5.0};									// Camera movement speed

std::vector<float> points{};

GLBI_Engine myEngine;
STP3D::StandardMesh grass;
GLBI_Convex_2D_Shape ground{3};
GLBI_Set_Of_Points base{3};
STP3D::IndexedMesh *cube;

GLBI_Texture herbeTexture;
float Sp = 1.0f;

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
			add_points(i,     j,     h_A, UVS[value][0],           UVS[value][1],           points, colors, uvs, normals);
			add_points(i,     j + 1, h_B, UVS[(value + 1) % 4][0], UVS[(value + 1) % 4][1], points, colors, uvs, normals);
			add_points(i + 1, j + 1, h_D, UVS[(value + 2) % 4][0], UVS[(value + 2) % 4][1], points, colors, uvs, normals);

			// Triangle 2 (A, C, D)
			add_points(i,     j,     h_A, UVS[value][0],           UVS[value][1],           points, colors, uvs, normals);
			add_points(i + 1, j,     h_C, UVS[(value + 3) % 4][0], UVS[(value + 3) % 4][1], points, colors, uvs, normals);
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
}

void drawFrame()
{
	base.drawSet();
}

void leaf_minecraf(int taille)
{

	int rayonMax = (taille / 6) + 1;
	int leaf_start = taille / 2;
	myEngine.setFlatColor(0.0, 0.0, 1.);
	for (auto z = leaf_start; z <= taille + 2; z++)
	{

		auto couche = (taille + 2) - z;
		auto rayonCouche = (couche < 2) ? (rayonMax - 1) : rayonMax;

		if (z == taille + 2)
			rayonCouche = 0;

		for (auto x = -rayonCouche; x <= rayonCouche; x++)
		{
			for (auto y = -rayonCouche; y <= rayonCouche; y++)
			{
				if (x == 0 && y == 0 && z < taille)
					continue;
				myEngine.mvMatrixStack.pushMatrix();
				myEngine.mvMatrixStack.addTranslation({x * 0.5f, y * 0.5f, z * 0.5f});
				myEngine.updateMvMatrix();
				cube->draw();
				myEngine.mvMatrixStack.popMatrix();
			}
		}
	}
}

void tree_minecraft(int taille)
{

	myEngine.setFlatColor(1, 0.0, 0.0);
	for (auto i = 0; i < taille; i++)
	{
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation({0., 0., 0.5f});
		myEngine.updateMvMatrix();
		cube->draw();
	}

	for (auto i = 0; i < taille; i++)
	{
		myEngine.mvMatrixStack.popMatrix();
	}
	leaf_minecraf(taille);
}

void drawScene()
{
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.activateTexturing(true);
	herbeTexture.attachTexture();
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

	tree_minecraft(10);
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