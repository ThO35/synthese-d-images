#include "draw_scene.hpp"

/// Camera parameters
float angle_theta {45.0};      // Angle between x axis and viewpoint
float angle_phy {30.0};      // Angle between z axis and viewpoint
float dist_zoom {30.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;
STP3D::StandardMesh grass;
GLBI_Convex_2D_Shape ground{3};
GLBI_Set_Of_Points base{3};


GLBI_Texture herbeTexture;



float hauteur (float charac)
{
	return (charac*scaling)-minVal;
}

float average (const std::vector<int>& point_adjacent)
{
	if (point_adjacent.empty())
	{
		return 0.;
	}
	float summ = 0.;
	for (auto i : point_adjacent)
	{
		summ+=i;
	}
	return summ/point_adjacent.size();
}


float tree_hauteur (int i, int j)
{
	
	std::vector<int> point_adjacent = {};

	if (i-1 >=0){
		int nord = ((i-1)*256)+j;
		if (static_cast<float> (static_cast<unsigned char>(donnes[nord]))!= 0){
			point_adjacent.push_back(static_cast<float> (static_cast<unsigned char>(donnes[nord])));
		}
	}
	if (j-1>=0)
	{
		int ouest = (i*256)+(j-1);
		if (static_cast<float> (static_cast<unsigned char>(donnes[ouest]))!= 0){
			point_adjacent.push_back(static_cast<float> (static_cast<unsigned char>(donnes[ouest])));
		}
	}

	if (i+1 <=length){
		int sud = ((i+1)*256)+j;
		if (static_cast<float> (static_cast<unsigned char>(donnes[sud]))!= 0){
			point_adjacent.push_back(static_cast<float> (static_cast<unsigned char>(donnes[sud])));
		}
	}
	if (j+1<= width)
	{
		int est = (i*256)+(j+1);
		if (static_cast<float> (static_cast<unsigned char>(donnes[est]))!= 0){
			point_adjacent.push_back(static_cast<float> (static_cast<unsigned char>(donnes[est])));
		}
	}
	return average(point_adjacent);
}


void initTerrain() {
    std::vector<float> points{}, colors{}, uvs{}, normals{};
    float Sp = 1.0f; // Facteur Sp du sujet [cite: 40]

    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < width - 1; j++) {
            // --- TA LOGIQUE DE COORDONNÉES ---
            int coord_A = (i * 256) + j;
            int coord_B = (i * 256) + (j + 1);
            int coord_C = ((i + 1) * 256) + j;
            int coord_D = ((i + 1) * 256) + (j + 1);

            float h_A = donnes[coord_A] == 0 ? tree_hauteur(i, j) : static_cast<float>(static_cast<unsigned char>(donnes[coord_A]));
            float h_B = donnes[coord_B] == 0 ? tree_hauteur(i, j + 1) : static_cast<float>(static_cast<unsigned char>(donnes[coord_B]));
            float h_C = donnes[coord_C] == 0 ? tree_hauteur(i + 1, j) : static_cast<float>(static_cast<unsigned char>(donnes[coord_C]));
            float h_D = donnes[coord_D] == 0 ? tree_hauteur(i + 1, j + 1) : static_cast<float>(static_cast<unsigned char>(donnes[coord_D]));

            // --- FONCTION POUR AJOUTER UN POINT (Avec tes calculs) ---
            auto add_p = [&](float x, float y, float h, float u, float v) {
                // Positions (Index 0)
                points.insert(points.end(), { (x - length/2.0f)*Sp, (y - width/2.0f)*Sp, hauteur(h) });
                
                // Normales (Index 1) : Formule de la page 3 [cite: 48]
                float nx = ((tree_hauteur(x-1, y) - tree_hauteur(x+1, y)) * scaling) / (2.0f * Sp);
                float ny = ((tree_hauteur(x, y-1) - tree_hauteur(x, y+1)) * scaling) / (Sp * 2.0f);
                normals.insert(normals.end(), { nx, ny, 1.0f });

                // UV (Index 2) : De 0 à 1 pour chaque case
				
                uvs.insert(uvs.end(), { u, v });

                // Couleurs (Index 3) : Blanc pour ne pas teinter la texture
                colors.insert(colors.end(), { 1.0f, 1.0f, 1.0f });
            };

			float u_low  = i / (float)(length - 1);
			float u_high = (i + 1) / (float)(length - 1);
			float v_low  = j / (float)(width - 1);
			float v_high = (j + 1) / (float)(width - 1);

            // Triangle 1 (A, B, D)
            add_p(i, j, h_A, 0.0f, 0.0f);
            add_p(i, j+1, h_B, 0.0f, 1.0f);
            add_p(i+1, j+1, h_D, 1.0f, 1.0f);

            // Triangle 2 (A, C, D)
            add_p(i, j, h_A, 0.0f, 0.0f);
            add_p(i+1, j, h_C, 1.0f, 0.0f);
            add_p(i+1, j+1, h_D, 1.0f, 1.0f);
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

void initScene() {

	std::vector<float> baseCarre{-10.0,-10.0,0.0,
								 10.0,-10.0,0.0,
								 10.0,10.0,0.0,
								 -10.0,10.0,0.0};
	ground.initShape(baseCarre);
	ground.changeNature(GL_TRIANGLE_FAN);



	std::vector<float> pointsBase {0.0,0.0,0.0,
							 	10.0,0.0,0.0,
								0.0,0.0,0.0,
								0.0,10.0,0.0,
								0.0,0.0,0.0,
							 	0.0,0.0,10.0};
	std::vector<float> color{1.0,0.0,0.0,
							 1.0,0.0,0.0,
							 0.0,1.0,0.0,
							 0.0,1.0,0.0,
							 0.0,0.0,1.0,
							 0.0,0.0,1.0};
	
	base.initSet(pointsBase, color);
	base.changeNature(GL_LINES);

	initTerrain();

	glActiveTexture(GL_TEXTURE0);


	int width_texture, height_texture, n;


	auto pixels = stbi_load("../assets/textures/herbe.png",&width_texture,&height_texture,&n,0);
	if (pixels == nullptr){
		std::cout<<"Debilus"<<std::endl;
	}
	herbeTexture.createTexture();
	herbeTexture.attachTexture();
	herbeTexture.setParameters(GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	herbeTexture.loadImage(width_texture,height_texture,n,pixels );
	herbeTexture.detachTexture();
	stbi_image_free(pixels);
	

}

void drawFrame() {
	base.drawSet();
	
}






void drawScene() {

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
		myEngine.setFlatColor(0.2,0.0,0.0);
		myEngine.activateTexturing(true);
		herbeTexture.attachTexture();
		myEngine.updateMvMatrix();
		ground.drawShape();
			herbeTexture.detachTexture();
		myEngine.activateTexturing(false);
	myEngine.mvMatrixStack.popMatrix();
	
}



