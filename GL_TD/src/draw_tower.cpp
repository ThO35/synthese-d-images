#include"draw_tower.hpp"

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
	myEngine.setFlatColor(256,256,256);
	myEngine.mvMatrixStack.addRotation(M_PI/2,{1.0f,0.0f,0.0f});
	myEngine.mvMatrixStack.addTranslation({2.,0.,2.});
	myEngine.mvMatrixStack.addHomothety({4,1,4});
	myEngine.updateMvMatrix();
	cylindre->draw();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(0,256,0);
	myEngine.mvMatrixStack.addRotation(M_PI/2,{1.0f,0.0f,0.0f});
	myEngine.mvMatrixStack.addTranslation({2.,1.,2.});
	myEngine.mvMatrixStack.addHomothety({2.,0.01,2.});
	myEngine.updateMvMatrix();
	cone->draw();
	myEngine.mvMatrixStack.popMatrix();
}

void tour (float taille){
	base_tour();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(256,256,256);
	myEngine.mvMatrixStack.addRotation(M_PI/2,{1.0f,0.0f,0.0f});
	myEngine.mvMatrixStack.addTranslation({2.0f,1.0f,2.0f});
	myEngine.mvMatrixStack.addHomothety({2.0f,taille,2.0f});
	myEngine.updateMvMatrix();
	cylindre->draw();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
		myEngine.setFlatColor(0,0,256);
		myEngine.mvMatrixStack.addRotation(M_PI/2,{1.0f,0.0f,0.0f});
		myEngine.mvMatrixStack.addTranslation({2.,taille+1,2.});
		myEngine.mvMatrixStack.addHomothety({1.5f ,0.01f, 1.5f});
		myEngine.updateMvMatrix();
		cone->draw();
	myEngine.mvMatrixStack.popMatrix();

	
}

void tour_de_sauron() {
    rempart(5.,3);
	rempart(8.,1);
	pilier(5.75,3);
	tour (6);
}