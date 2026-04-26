#include"draw_tower.hpp"

float next_change = 0.0f;
float angle = 0.0f;
int random1 = 0;
int random2 = 0;

void pilier_arc(float debut, float fin, float rayon){
	for (float j = 0; j <= 100; j++) {
		auto t = j / 100;
		
		auto courbe = std::pow(t, 5.0f);;
		auto ecartement = courbe * 0.8f; 
		
		auto y = rayon + (ecartement / 2.0f);
		auto z = debut - t * (debut - fin);

		myEngine.mvMatrixStack.pushMatrix();
		
		if (j == 100) {

			myEngine.setFlatColor(0, 0, 1);
			myEngine.mvMatrixStack.addTranslation({0.0f, y, z - 0.2f});
			myEngine.mvMatrixStack.addHomothety(0.5f);
			myEngine.mvMatrixStack.addHomothety({1.0f, (ecartement * 2.02f) + 1.0f, 1.8f});
		} else {
			myEngine.setFlatColor(0, 1, 0);
			myEngine.mvMatrixStack.addTranslation({0.0f, y, z});
			myEngine.mvMatrixStack.addHomothety(0.5f); 
			myEngine.mvMatrixStack.addHomothety({1.0f, (ecartement * 2.0f) + 1.0f, 1.0f}); 
		
		}

		myEngine.updateMvMatrix();
		cube->draw();
		myEngine.mvMatrixStack.popMatrix();
    }
}


void iris() {
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation({-0.9f, 0.0f, 0.0f});
    myEngine.updateMvMatrix();
    myEngine.switchToPhongShading();
    myEngine.setFlatColor(0.0f, 0.0f, 0.0f); 
    myEngine.mvMatrixStack.addHomothety( 0.17f);
    myEngine.mvMatrixStack.addHomothety({1.0f, 1.0f, 4.5f});
    myEngine.updateMvMatrix();
    sphere->draw();
    myEngine.switchToFlatShading();
    myEngine.mvMatrixStack.popMatrix();
}

void eye (){
	auto shading = myEngine.currentShader;
	if (shading == 1)
	{
		auto currentMatrix = myEngine.mvMatrixStack.stack.back(); 
		auto localOrigin = STP3D::Vector4D(0.0f, 0.0f, 0.0f, 1.0f);
		

		auto view = currentMatrix * localOrigin;
		auto lightPos = relative_2_absolute(myEngine.viewMatrix, view, 0, 0, 0); 
		myEngine.setLightPosition(lightPos, 5);
		myEngine.setLightIntensity({1000.0f, 0.0f, 0.0f}, 5);
		myEngine.switchToFlatShading();
	}
	
	myEngine.activateTexturing(true);
	textures["feu"].attachTexture();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.0f, 0.5, 0.0f});
	myEngine.mvMatrixStack.addHomothety({0.86f, 1, 0.86f});
	myEngine.updateMvMatrix();
	myEngine.setFlatColor(0, 0, 1);
	cone->draw();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation((M_PI),{1.0,0.0,0.0});
	myEngine.mvMatrixStack.addTranslation({0.0f, 0.5, 0.0f});
	myEngine.mvMatrixStack.addHomothety({0.86f, 1, 0.86f});
	myEngine.updateMvMatrix();
	myEngine.setFlatColor(1, 0, 0);
	cone->draw();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.activateTexturing(false);
	textures["feu"].attachTexture();




	myEngine.mvMatrixStack.pushMatrix();



		myEngine.mvMatrixStack.pushMatrix();
			myEngine.activateTexturing(true);
			textures["feu"].attachTexture();
			myEngine.mvMatrixStack.addTranslation({0.0f, 0.0, 0.0f});
			myEngine.updateMvMatrix();
			myEngine.setFlatColor(0, 1, 0);
			sphere->draw();
			myEngine.activateTexturing(false);
			textures["feu"].attachTexture();
		myEngine.mvMatrixStack.popMatrix();
	
		
	myEngine.mvMatrixStack.popMatrix();
	iris();
	if (shading == 1) myEngine.switchToPhongShading();
}

void pilier(float rayon, float hauteur) {
    auto nb_piliers = 12; 
    
    for (auto i = 0; i < nb_piliers; i++) {
        myEngine.mvMatrixStack.pushMatrix();
        
        auto angle = i * (2.0f * M_PI / nb_piliers);
        myEngine.mvMatrixStack.addRotation(angle, {0.0f, 0.0f, 1.0f});
        
        auto z = hauteur * 1.5f; 
        auto hauteur_finale = z * 0.5f;
        

        myEngine.mvMatrixStack.pushMatrix();
        myEngine.setFlatColor(1, 0, 0);
        myEngine.mvMatrixStack.addTranslation({0.0f, rayon, hauteur_finale / 2.0f});
        myEngine.mvMatrixStack.addHomothety(0.5f);
        myEngine.mvMatrixStack.addHomothety({1.0f, 1.0f, z});  
        myEngine.updateMvMatrix();
        cube->draw();    
        myEngine.mvMatrixStack.popMatrix();

        auto debut = hauteur_finale * 0.85f; 
        auto fin = hauteur_finale * 0.30f; 
        
		pilier_arc(debut, fin, rayon);
        
        
        myEngine.mvMatrixStack.popMatrix();
    }
}

void rempart(float rayon, int taille) {
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.setFlatColor(0,0,0);
    int nb_segments = 90; 
    for (int i = 0; i < nb_segments; i++) {
        myEngine.mvMatrixStack.pushMatrix();
        
        auto angle = i * (2.0f * M_PI / nb_segments);
        myEngine.mvMatrixStack.addRotation(angle, {0.0f, 0.0f, 1.0f});
        myEngine.mvMatrixStack.addTranslation({0.0f, rayon, (float)taille / 2.0f});
        myEngine.mvMatrixStack.addHomothety({1.0f, 1.0f, (float)taille});
        myEngine.updateMvMatrix();
        cube->draw();    
        myEngine.mvMatrixStack.popMatrix();
    }
    myEngine.mvMatrixStack.popMatrix();
}

void base_tour(){
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.activateTexturing(true);
		textures["mur"].attachTexture();
		myEngine.setFlatColor(256,256,256);
		myEngine.mvMatrixStack.addRotation(M_PI/2,{1.0f,0.0f,0.0f});
		myEngine.mvMatrixStack.addTranslation({2.,0.,2.});
		myEngine.mvMatrixStack.addHomothety({4,1,4});
		myEngine.updateMvMatrix();
		cylindre->draw();
		myEngine.activateTexturing(false);
		textures["mur"].attachTexture();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
		myEngine.activateTexturing(true);
		textures["marbre"].attachTexture();
		auto shading = myEngine.currentShader;
		if (shading == 1)
		{
			myEngine.setShininess(80.0f); 
			myEngine.setSpecularColor(STP3D::Vector3D(0.6f, 0.6f, 0.6f));
		}
		myEngine.setFlatColor(0,256,0);
		myEngine.mvMatrixStack.addRotation(M_PI/2,{1.0f,0.0f,0.0f});
		myEngine.mvMatrixStack.addTranslation({2.,1.,2.});
		myEngine.mvMatrixStack.addHomothety({2.,0.01,2.});
		myEngine.updateMvMatrix();
		cone->draw();
		myEngine.activateTexturing(false);
		textures["marbre"].attachTexture();
	myEngine.mvMatrixStack.popMatrix();
}

void tour (float taille){
	base_tour();
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.activateTexturing(true);
		textures["mur"].attachTexture();
		myEngine.setFlatColor(256,256,256);
		myEngine.mvMatrixStack.addRotation(M_PI/2,{1.0f,0.0f,0.0f});
		myEngine.mvMatrixStack.addTranslation({2.0f,1.0f,2.0f});
		myEngine.mvMatrixStack.addHomothety({2.0f,taille,2.0f});
		myEngine.updateMvMatrix();
		cylindre->draw();
		myEngine.activateTexturing(false);
		textures["mur"].attachTexture();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
		myEngine.activateTexturing(true);
		textures["marbre"].attachTexture();
		auto shading = myEngine.currentShader;
		if (shading == 1)
		{
			myEngine.setShininess(80.0f); 
			myEngine.setSpecularColor(STP3D::Vector3D(0.6f, 0.6f, 0.6f));
		}
		myEngine.mvMatrixStack.addRotation(M_PI/2,{1.0f,0.0f,0.0f});
		myEngine.mvMatrixStack.addTranslation({2.,taille+1,2.});
		myEngine.mvMatrixStack.addHomothety({1.5f ,0.01f, 1.5f});
		myEngine.updateMvMatrix();
		cone->draw();
		myEngine.activateTexturing(false);
		textures["marbre"].attachTexture();
	myEngine.mvMatrixStack.popMatrix();


	myEngine.mvMatrixStack.pushMatrix();
		myEngine.activateTexturing(true);
			textures["mur"].attachTexture();
		myEngine.mvMatrixStack.addRotation(M_PI/2,{1.0f,0.0f,0.0f});
		myEngine.mvMatrixStack.addTranslation({1.0f,0.0f,0.2f});
		myEngine.mvMatrixStack.addHomothety({0.5f ,1.0f, 0.5f});
		myEngine.updateMvMatrix();
		cylindre->draw();
			myEngine.activateTexturing(false);
			textures["mur"].attachTexture();
		myEngine.mvMatrixStack.pushMatrix();
			myEngine.activateTexturing(true);
			textures["toi"].attachTexture();
			myEngine.setFlatColor(256,0,0);
			myEngine.mvMatrixStack.addTranslation({0.0f,0.9f,0.0f});
			myEngine.mvMatrixStack.addHomothety({0.6f ,0.8f, 0.6f});
			myEngine.updateMvMatrix();
			cone->draw();
			myEngine.activateTexturing(false);
			textures["toi"].attachTexture();
		myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();


	myEngine.mvMatrixStack.pushMatrix();
			myEngine.setFlatColor(0,0,256);
				myEngine.activateTexturing(true);
			textures["mur"].attachTexture();
		myEngine.mvMatrixStack.addRotation(M_PI/2,{1.0f,0.0f,0.0f});
		myEngine.mvMatrixStack.addTranslation({0.2f,0.0f,1.0f});
		myEngine.mvMatrixStack.addHomothety({0.5f ,1.0f, 0.5f});
		myEngine.updateMvMatrix();
		cylindre->draw();
			myEngine.activateTexturing(false);
			textures["mur"].attachTexture();
		myEngine.mvMatrixStack.pushMatrix();
			myEngine.activateTexturing(true);
			textures["toi"].attachTexture();
			myEngine.setFlatColor(256,0,0);
			myEngine.mvMatrixStack.addTranslation({0.0f,0.9f,0.0f});
			myEngine.mvMatrixStack.addHomothety({0.6f ,0.8f, 0.6f});
			myEngine.updateMvMatrix();
			cone->draw();
			myEngine.activateTexturing(false);
			textures["toi"].attachTexture();
		myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();
	
}


void tour_de_sauron() {

	myEngine.activateTexturing(true);
	textures["rempart"].attachTexture();
    rempart(5.,3);
	rempart(8.,1);
	pilier(5.75,3);
	myEngine.activateTexturing(false);
	textures["rempart"].attachTexture();
	tour (6);

	float current = glfwGetTime();



	if (current >= next_change) {
		angle = current;
        float delay = 2.0f + static_cast<float>(rand()) / RAND_MAX * 3.0f;
        next_change = current + delay;
        random1 = (int)rand();
        random2 = (int)rand();
    }

	myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({2.0f, -2.0, 9.0f});

        float vitesse = 50.0f; 
        myEngine.mvMatrixStack.addRotation((M_PI / 180.0f) * (random1 + angle * vitesse), {0.0f, 0.0f, 1.0f});
        myEngine.mvMatrixStack.addRotation((M_PI / 180.0f) * (random2 + angle * vitesse), {0.0f, 1.0f, 0.0f});
        
        eye();
    myEngine.mvMatrixStack.popMatrix();
}