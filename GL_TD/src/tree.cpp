#include "tree.hpp"

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