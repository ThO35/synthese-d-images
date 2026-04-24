#include <unordered_map>

#include "draw_scene.hpp"
#include "draw_sandBird.hpp"
#include "draw_pnj.hpp"
#include "spline.hpp"

// Order UVs
const float UVS[4][2] = {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};

// Camera parameters
Vector3D pos_camera = Vector3D(-30.0, 0.0, 0.0); // Position of the camera
float angle_horizontal{0.0};					 // Angle between x axis and viewpoint
float angle_vertical{0.0};						 // Angle between z axis and viewpoint
float speed{1.0};								 // Camera movement speed

std::vector<float> points{};
Spline trajectory({{0, 0, 20},
				   {100, 50, 25},
				   {0, 100, 30},
				   {-100, 50, 35},
				   {0, 0, 40},
				   {100, -50, 35},
				   {0, -100, 30},
				   {-100, -50, 25},
				   {0, 0, 20}});

GLBI_Engine myEngine;

std::unordered_map<std::string, GLBI_Texture> textures;

STP3D::StandardMesh *repere;
STP3D::IndexedMesh *cube;
STP3D::IndexedMesh *sphere;
STP3D::IndexedMesh *cylindre;
STP3D::StandardMesh *cone;
STP3D::StandardMesh grass;
GLBI_Convex_2D_Shape ground{3};

float Sp = 1.0f;

std::vector<std::array<float, 5>> zeroPosition = {};

void initTextures()
{
	glActiveTexture(GL_TEXTURE0);
	auto init_texture = [](const char *path, const char *name)
	{
		int width_texture, height_texture, n;
		GLBI_Texture tmp_texture;
		auto pixels = stbi_load(path, &width_texture, &height_texture, &n, 0);
		if (pixels == nullptr)
		{
			std::cout << "Debilus - " << name << std::endl;
		}
		tmp_texture.createTexture();
		tmp_texture.attachTexture();
		tmp_texture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		tmp_texture.loadImage(width_texture, height_texture, n, pixels);
		tmp_texture.detachTexture();
		stbi_image_free(pixels);
		textures[name] = std::move(tmp_texture);
	};
	init_texture("../assets/textures/herbe.png", "grass");
	init_texture("../assets/textures/leaf.jpg", "leaf");
	init_texture("../assets/textures/wood.jpg", "wood");
	init_texture("../assets/textures/moon.png", "liveStar");
	init_texture("../assets/textures/sand.png", "sand");
	init_texture("../assets/textures/sun.png", "sun");
	init_texture("../assets/textures/skybox.png", "skybox");
}

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
	myEngine.addALight(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 0.0f}, STP3D::Vector3D{100.0f, 100.0f, 100.0f});
	myEngine.addALight(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 0.0f}, STP3D::Vector3D{100.0f, 100.0f, 100.0f});
	myEngine.addALight(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 1.0f}, STP3D::Vector3D{100.0f, 100.0f, 100.0f});
	myEngine.addALight(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 1.0f}, STP3D::Vector3D{100.0f, 100.0f, 100.0f});
	myEngine.addALight(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 1.0f}, STP3D::Vector3D{100.0f, 100.0f, 100.0f});
	myEngine.addALight(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 1.0f}, STP3D::Vector3D{100.0f, 100.0f, 100.0f});
	myEngine.switchToFlatShading();
	initTextures();

	cone = basicCone(1, 1);
	cylindre = basicCylinder(1., .5, 100);
	cylindre->createVAO();
	sphere = basicSphere(1);
	sphere->createVAO();
	cube = basicCube(1.0);
	cube->createVAO();
	repere = createRepere(10);
	repere->createVAO();

	initTerrain();
}

void leaf_minecraf(int sizeTree, int seed)
{
	srand(seed);
	float cubeSize = 1.0f;
	float rayon = (sizeTree / 4.0f) + 1.0f;
	myEngine.setFlatColor(1, 0.0, 0.);
	myEngine.setShininess(25.0f);
	myEngine.setSpecularColor(STP3D::Vector3D(0.15f, 0.15f, 0.15f));
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
	textures["wood"].attachTexture();
	float cubeSize = 1.0f;
	myEngine.setFlatColor(0., 0., 1);

	myEngine.setShininess(5.0f);
	myEngine.setSpecularColor(STP3D::Vector3D(0.05f, 0.05f, 0.05f));

	for (int i = 0; i < hauteur; i++)
	{
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, i * cubeSize});
		myEngine.updateMvMatrix();
		cube->draw();
		myEngine.mvMatrixStack.popMatrix();
	}
	textures["wood"].detachTexture();
	myEngine.activateTexturing(false);
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.activateTexturing(true);
	textures["leaf"].attachTexture();
	leaf_minecraf(hauteur, seed);
	textures["leaf"].detachTexture();
	myEngine.activateTexturing(false);
	myEngine.mvMatrixStack.popMatrix();
}

void moon()
{
	myEngine.mvMatrixStack.pushMatrix();

	float angle = (((M_PI / 180.0) * glfwGetTime() * 15.0) + M_PI);

	myEngine.switchToPhongShading();

	float lightY = length * std::sin(-angle);
	float lightZ = length * std::cos(-angle);

	myEngine.setLightPosition(STP3D::Vector4D(0.0f, lightY, lightZ, 0.0f), 1);
	myEngine.setLightIntensity(STP3D::Vector3D(0.15f, 0.15f, 0.2f), 1);

	myEngine.switchToFlatShading();

	myEngine.setFlatColor(1.0f, 1.0f, 1.0f);
	myEngine.activateTexturing(true);
	textures["liveStar"].attachTexture();
	myEngine.mvMatrixStack.addRotation(angle, {1, 0, 0});
	myEngine.mvMatrixStack.addTranslation({1.0f, 1.0f, static_cast<float>(length)});
	myEngine.mvMatrixStack.addHomothety({5.0f, 5.0f, 5.0f});
	myEngine.updateMvMatrix();
	sphere->draw();
	textures["liveStar"].detachTexture();
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

	float intensity = std::sin(std::atan2(lightZ, lightY)) * 10;
	intensity = std::min(1.0f, std::max(0.0f, intensity));

	myEngine.setLightPosition(STP3D::Vector4D(0.0f, lightY, lightZ, 0.0f), 0);
	myEngine.setLightIntensity(STP3D::Vector3D(intensity, intensity, intensity), 0);

	myEngine.switchToFlatShading();

	myEngine.activateTexturing(true);
	textures["sun"].attachTexture();
	myEngine.mvMatrixStack.addRotation(angle, {1.0f, 0.0f, 0.0f});
	myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, static_cast<float>(length)});
	myEngine.mvMatrixStack.addHomothety({25.0f, 25.0f, 25.0f});
	myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, {0.0f, 1.0f, 0.0f});
	myEngine.updateMvMatrix();
	sphere->draw();
	textures["sun"].detachTexture();
	myEngine.activateTexturing(false);

	myEngine.mvMatrixStack.popMatrix();
}

void show_trajectory()
{
	for (; !trajectory.simule(0.05f);)
	{
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation(trajectory.getSimulPosition());
		myEngine.mvMatrixStack.addHomothety({0.2f, 0.2f, 0.2f});
		myEngine.updateMvMatrix();
		sphere->draw();
		myEngine.mvMatrixStack.popMatrix();
	}
}

void batton_de_papa()
{
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(M_PI / 2, Vector3D(1.0, 0.0, 0.0));
	myEngine.mvMatrixStack.addHomothety(Vector3D(0.1, 9, 0.1));
	myEngine.updateMvMatrix();
	cylindre->draw();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, 8.99f});
	myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, {1.0f, 0.0f, 0.0f});
	for (int i = 0; i < 24; i++)
	{
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addRotation((M_PI / 24 * 2), Vector3D(1.0, 0.0, 0.0));
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addHomothety({0.1, 0.20, 0.1});
		myEngine.updateMvMatrix();
		cylindre->draw();
		myEngine.mvMatrixStack.popMatrix();
		myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0.18, 0));
	}
	for (int i = 0; i < 24; i++)
	{
		myEngine.mvMatrixStack.popMatrix();
	}

	myEngine.mvMatrixStack.popMatrix();
}
void lantern()
{
	myEngine.switchToPhongShading();

	auto posX = 0.0f;
	auto posY = static_cast<float>(-(M_PI / 12.0 * 2.5) - 0.05);
	auto posZ = -10;

	for (auto i = 2; i < 6; i++)
	{

		auto offset = i * 2.3f;
		auto time = glfwGetTime() * 8.0f + offset;
		auto flicker = std::sin(time) + std::sin(time * 2.1f) * 0.5f + std::cos(time * 3.7f) * 0.25f;
		auto intensity = 1.0f + (flicker * 0.15f);

		auto r = 1.0f * intensity;
		auto g = (0.4f + flicker * 0.1f) * intensity;
		auto b = 0.05f * intensity;

		myEngine.setLightPosition(STP3D::Vector4D(posX, posY, posZ, 1.0f), i);
		myEngine.setLightIntensity(STP3D::Vector3D(r, g, b), i);
	}

	myEngine.switchToFlatShading();
	myEngine.mvMatrixStack.pushMatrix();

	myEngine.mvMatrixStack.addTranslation(STP3D::Vector3D(posX, posY, posZ));
	myEngine.setFlatColor(1, 1, 1);
	auto scaleFixe = 0.4f;
	myEngine.mvMatrixStack.addHomothety(scaleFixe);
	myEngine.updateMvMatrix();

	sphere->draw();

	myEngine.mvMatrixStack.popMatrix();
}
void drawScene()
{

	lantern();
	moon();
	sun();

	myEngine.activateTexturing(true);
	textures["skybox"].attachTexture();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addHomothety({length * 1.1f, length * 1.1f, length * 1.1f});
	myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, {0.0f, 1.0f, 0.0f});
	myEngine.updateMvMatrix();
	sphere->draw();
	myEngine.mvMatrixStack.popMatrix();
	textures["skybox"].detachTexture();
	myEngine.activateTexturing(false);

	myEngine.switchToPhongShading();

	batton_de_papa();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.activateTexturing(true);
	textures["grass"].attachTexture();

	myEngine.setShininess(2.0f);
	myEngine.setSpecularColor(STP3D::Vector3D(0.02f, 0.05f, 0.02f));

	myEngine.updateMvMatrix();
	grass.draw();
	textures["grass"].detachTexture();
	myEngine.activateTexturing(false);
	myEngine.mvMatrixStack.popMatrix();
	// sapin();

	for (const auto &zero : zeroPosition)
	{
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation(STP3D::Vector3D(zero[0], zero[1], zero[2]));
		myEngine.updateMvMatrix();
		tree_minecraft(static_cast<int>(zero[3]), static_cast<int>(zero[4]));
		myEngine.mvMatrixStack.popMatrix();
	}

	myEngine.mvMatrixStack.pushMatrix();
	trajectory.update(0.001f);
	myEngine.mvMatrixStack.addTranslation(trajectory.getPosition());
	myEngine.mvMatrixStack.addRotation(trajectory.getAzimuthal(), {0.0f, 0.0f, 1.0f});
	myEngine.mvMatrixStack.addRotation(-trajectory.getElevation(), {0.0f, 1.0f, 0.0f});
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.activateTexturing(true);
	textures["sand"].attachTexture();
	drawSandBird();
	textures["sand"].detachTexture();
	myEngine.activateTexturing(false);
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.switchToFlatShading();

	// show_trajectory();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, 25.0f});
	myEngine.updateMvMatrix();
	drawPNJ();
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
	pos_camera[2] = points[coord_a * 18 + 2] + 10;
}