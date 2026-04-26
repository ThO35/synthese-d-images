#include <unordered_map>

#include "draw_scene.hpp"
#include "spline.hpp"
#include "draw_sandBird.hpp"
#include "draw_tower.hpp"
#include "draw_pnj.hpp"
#include "tree.hpp"


// Order UVs
const float UVS[4][2] = {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};

// Camera parameters
Vector3D pos_camera = Vector3D(-30.0, 0.0, 0.0); // Position of the camera
float angle_horizontal{0.0};					 // Angle between x axis and viewpoint
float angle_vertical{0.0};						 // Angle between z axis and viewpoint
float speed{1.0};								 // Camera movement speed
Vector3D pos_pnj = Vector3D(0.0f, 0.0f, 0.0f);
float angle_pnj{0.0f};

std::vector<float> points{};
Spline trajectory({{0,    0,    20, 0},
				   {100,  50,   25, 0},
				   {50,   100,  30, 0},
				   {-50,  100,  30, 1},
				   {-100, 50,   35, 0},
				   {0,    0,    40, 0},
				   {100,  -50,  35, 0},
				   {50,   -100, 30, 0},
				   {-50,  -100, 30, 1},
				   {-100, -50,  25, 0},
				   {0,    0,    20, 0}});

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

void update_bounded_coord(Vector3D& vec)
{
	// Born to map
	if (vec[0] <= -(length / 2))
		vec[0] = -(length / 2);
	if (vec[0] >= length / 2 - 1)
		vec[0] = length / 2 - 1;
	if (vec[1] <= -(width / 2))
		vec[1] = -(width / 2);
	if (vec[1] >= width / 2 - 1)
		vec[1] = width / 2 - 1;
	int x = length / 2 + vec[0];
	int y = width / 2 + vec[1];
	int coord_a = x * (length - 1) + y;
	vec[2] = points[coord_a * 18 + 2] + 4;
}

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

	init_texture("../assets/textures/rempart.jpg", "rempart");
	init_texture("../assets/textures/feux.jpg", "feu");
	init_texture("../assets/textures/toi.jpg", "toi");
	init_texture("../assets/textures/marbre.jpg", "marbre");
	init_texture("../assets/textures/mur.jpg", "mur");
}

void initTerrain()
{
	std::vector<float> colors{}, uvs{}, normals{};
	srand(time(NULL));

	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < width - 1; j++)
		{
			int coord_A = (i * width) + j;
			int coord_B = (i * width) + (j + 1);
			int coord_C = ((i + 1) * width) + j;
			int coord_D = ((i + 1) * width) + (j + 1);

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
	myEngine.addALight(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 1.0f}, STP3D::Vector3D{0.0f, 0.0f, 0.0f});
	myEngine.addALight(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 1.0f}, STP3D::Vector3D{0.0f, 0.0f, 0.0f});
	myEngine.addALight(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 1.0f}, STP3D::Vector3D{0.0f, 0.0f, 0.0f});
	myEngine.addALight(STP3D::Vector4D{0.0f, 0.0f, 0.0f, 0.0f}, STP3D::Vector3D{0.0f, 0.0f, 0.0f});
	myEngine.switchToFlatShading();
	initTextures();

	cone = basicCone(1, 1);
	cone->createVAO();
	cylindre = basicCylinder(1., .5, 100);
	cylindre->createVAO();
	sphere = basicSphere(1);
	sphere->createVAO();
	cube = basicCube(1.0);
	cube->createVAO();
	repere = createRepere(10);
	repere->createVAO();

	initTerrain();

	update_bounded_coord(pos_pnj);
}



void draw_moon()
{
	float angle = (((M_PI / 180.0) * glfwGetTime() * 15.0) + M_PI);

	float lightY = length * std::sin(-angle);
	float lightZ = length * std::cos(-angle);

	auto shading = myEngine.currentShader;
	if (shading == 1) 
	{
		myEngine.setLightPosition(STP3D::Vector4D(0.0f, lightY, lightZ, 0.0f), 1);
		myEngine.setLightIntensity(STP3D::Vector3D(0.15f, 0.15f, 0.2f), 1);
		myEngine.switchToFlatShading();
	}

	myEngine.mvMatrixStack.pushMatrix();
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
	
	if (shading == 1) myEngine.switchToPhongShading();
}




void draw_sun()
{

	float angle = (M_PI / 180.0f) * glfwGetTime() * 15;

	float lightY = length * std::sin(-angle);
	float lightZ = length * std::cos(-angle);

	auto shading = myEngine.currentShader;
	if (shading == 1) {
		float intensity = std::sin(std::atan2(lightZ, lightY)) * 10 + 1;
		intensity = std::min(1.0f, std::max(0.0f, intensity));
		myEngine.setLightPosition(STP3D::Vector4D(0.0f, lightY, lightZ, 0.0f), 0);
		myEngine.setLightIntensity(STP3D::Vector3D(intensity, intensity, intensity), 0);
		myEngine.switchToFlatShading();
	}

	myEngine.mvMatrixStack.pushMatrix();
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

	if (shading == 1) myEngine.switchToPhongShading();
}


void draw_skybox()
{
	auto shading = myEngine.currentShader;
	if (shading == 1) myEngine.switchToFlatShading();

	myEngine.activateTexturing(true);
	textures["skybox"].attachTexture();
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, {0.0f, 1.0f, 0.0f});
		myEngine.updateMvMatrix();
		sphere->draw();
	myEngine.mvMatrixStack.popMatrix();
	textures["skybox"].detachTexture();
	myEngine.activateTexturing(false);

	if (shading == 1) myEngine.switchToPhongShading();
}

void show_trajectory()
{
	myEngine.setFlatColor(0.8f, 0.0f, 0.0f);
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


void draw_terrain()
{
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.activateTexturing(true);
		textures["grass"].attachTexture();

		auto shading = myEngine.currentShader;
		if (shading == 1)
		{
			myEngine.setShininess(2.0f);
			myEngine.setSpecularColor(STP3D::Vector3D(0.02f, 0.05f, 0.02f));
		}
		
		myEngine.updateMvMatrix();
		grass.draw();
		textures["grass"].detachTexture();
		myEngine.activateTexturing(false);
	myEngine.mvMatrixStack.popMatrix();
}


void drawScene()
{
	if (is_ground_view)
	{
		pos_pnj = pos_camera;
		angle_pnj = angle_horizontal + 180.0f;
		std::cout << angle_pnj << std::endl;
	}
	if (activeShader) myEngine.switchToPhongShading();

	myEngine.mvMatrixStack.pushMatrix();
		std::cout << pos_pnj << std::endl;
		myEngine.mvMatrixStack.addTranslation({pos_pnj[0], pos_pnj[1], pos_pnj[2] - 1.9f});
		myEngine.mvMatrixStack.addRotation(M_PI / 180.f * angle_pnj, {0.0f, 0.0f, 1.0f});
		myEngine.updateMvMatrix();
		drawPNJ(2, 3, !is_ground_view);
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addHomothety({length * 1.1f, length * 1.1f, length * 1.1f});
		draw_skybox();
	myEngine.mvMatrixStack.popMatrix();

	draw_sun();
	draw_moon();
	draw_terrain();
	
	

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

	myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation({-50.0f, 75.0f, -19.0f});
		myEngine.mvMatrixStack.addRotation(M_PI, {0.0f, 0.0f, 1.0f});
		myEngine.mvMatrixStack.addHomothety({5.0f, 5.0f, 5.0f});
		tour_de_sauron();
	myEngine.mvMatrixStack.popMatrix();
	
	if (activeShader) myEngine.switchToFlatShading();

	if (detail_mod) show_trajectory();
}
