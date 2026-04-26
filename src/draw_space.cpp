#include "draw_space.hpp"


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
