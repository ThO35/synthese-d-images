#include "draw_pnj.hpp"


void draw_lantern(int first_id_light, int nb_light)
{
	auto posX = 0.0f;
	auto posY = static_cast<float>(-(M_PI / 12.0 * 2.5) - 0.05);
	auto posZ = 8.9f;

	auto shading = myEngine.currentShader;
	if (shading == 1) {
		for (auto i = first_id_light; i < first_id_light + nb_light; i++)
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
	}
	
	myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation(STP3D::Vector3D(posX, posY, posZ));
		myEngine.setFlatColor(1, 1, 1);
		auto scaleFixe = 0.4f;
		myEngine.mvMatrixStack.addHomothety(scaleFixe);
		myEngine.updateMvMatrix();
		sphere->draw();
	myEngine.mvMatrixStack.popMatrix();

	if (shading == 1) myEngine.switchToPhongShading();
}

void draw_daddyStick()
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


void draw_sceptre(int first_id_light, int nb_light)
{
	myEngine.mvMatrixStack.pushMatrix();
		draw_daddyStick();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.pushMatrix();
		draw_lantern(first_id_light, nb_light);
	myEngine.mvMatrixStack.popMatrix();
}


void draw_torso()
{
    myEngine.setFlatColor(0.6f, 0.0f, 0.0f);
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, 1.0f});
        myEngine.mvMatrixStack.addHomothety({0.5f, 0.5f, 0.5f});
        myEngine.updateMvMatrix();
        sphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, {1.0f, 0.0f, 0.0f});
        myEngine.updateMvMatrix();
        cylindre->draw();
    myEngine.mvMatrixStack.popMatrix();

    myEngine.setFlatColor(0.1f, 0.1f, 0.1f);
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addHomothety({0.52f, 0.52f, 0.52f});
        myEngine.updateMvMatrix();
        sphere->draw();
    myEngine.mvMatrixStack.popMatrix();
}


void draw_arm()
{
    myEngine.setFlatColor(0.6f, 0.0f, 0.0f);
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addHomothety({0.1f, 0.1f, 0.1f});
        myEngine.updateMvMatrix();
        sphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, -1.5f});
        myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, {1.0f, 0.0f, 0.0f});
        myEngine.mvMatrixStack.addHomothety({0.1f, 1.5f, 0.1f});
        myEngine.updateMvMatrix();
        cylindre->draw();
    myEngine.mvMatrixStack.popMatrix();

    myEngine.setFlatColor(0.0f, 0.6f, 0.0f);
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, -1.5f});
        myEngine.mvMatrixStack.addHomothety({0.15f, 0.15f, 0.15f});
        myEngine.updateMvMatrix();
        sphere->draw();
    myEngine.mvMatrixStack.popMatrix();
}


void draw_leg()
{
    myEngine.setFlatColor(0.1f, 0.1f, 0.1f);
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addHomothety({0.1f, 0.1f, 0.1f});
        myEngine.updateMvMatrix();
        sphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, {1.0f, 0.0f, 0.0f});
        myEngine.mvMatrixStack.addHomothety({0.1f, 1.5f, 0.1f});
        myEngine.updateMvMatrix();
        cylindre->draw();
    myEngine.mvMatrixStack.popMatrix();
}


void drawPNJ(int first_id_light, int nb_light)
{
    myEngine.mvMatrixStack.pushMatrix();
        draw_torso();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.6f, 1.0f});
        if (false)
        {
            myEngine.mvMatrixStack.addRotation(std::cos(glfwGetTime() * 2) * M_PI / 6.0f, {0.0f, 1.0f, 0.0f});
            draw_arm();
        }
        else
        {
            myEngine.mvMatrixStack.addRotation(2.0f * M_PI / 3.0f, {0.0f, 1.0f, 0.0f});
            draw_arm();
            myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, -1.5f});
            myEngine.mvMatrixStack.addRotation(-2.0f * M_PI / 3.0f, {0.0f, 1.0f, 0.0f});
            draw_sceptre(first_id_light, nb_light);
        }
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, -0.6f, 1.0f});
        myEngine.mvMatrixStack.addRotation(-std::cos(glfwGetTime() * 2) * M_PI / 6.0f, {0.0f, 1.0f, 0.0f});
        draw_arm();
    myEngine.mvMatrixStack.popMatrix();

    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.3f, -0.4f});
        myEngine.mvMatrixStack.addRotation(-std::cos(glfwGetTime() * 2) * M_PI / 12.0f, {0.0f, 1.0f, 0.0f});
        draw_leg();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, -0.3f, -0.4f});
        myEngine.mvMatrixStack.addRotation(std::cos(glfwGetTime() * 2) * M_PI / 12.0f, {0.0f, 1.0f, 0.0f});
        draw_leg();
    myEngine.mvMatrixStack.popMatrix();
}
