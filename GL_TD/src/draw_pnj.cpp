#include "draw_pnj.hpp"

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


void drawPNJ()
{
    myEngine.mvMatrixStack.pushMatrix();
        draw_torso();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.6f, 1.0f});
        myEngine.mvMatrixStack.addRotation(std::cos(glfwGetTime() * 2) * M_PI / 6.0f, {0.0f, 1.0f, 0.0f});
        // myEngine.mvMatrixStack.addRotation(2.0f * M_PI / 3.0f, {0.0f, 1.0f, 0.0f}); Lantern
        draw_arm();
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
