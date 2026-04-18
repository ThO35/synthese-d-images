#include "draw_sandBird.hpp"

double angle_wing = 0.0f;
double angle_tail = 0.0f;

void drawPart(STP3D::Vector3D matrix)
{
    auto gap = 0.02f;
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addHomothety({matrix.x - gap, matrix.y - gap, matrix.z - gap});
        myEngine.updateMvMatrix();
        cube->draw();
    myEngine.mvMatrixStack.popMatrix();
}


void drawWingEnd1()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, 1.0f / 3.0f});
        drawPart({1.0f, 2.0f, 1.0f / 3.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.0f, 1.0f / 3.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.5f, 0.0f});
        drawPart({1.0f, 1.0f, 1.0f / 3.0f});
    myEngine.mvMatrixStack.popMatrix();
}


void drawWingEnd2()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, 1.0f / 3.0f});
        drawPart({1.0f, 2.0f, 1.0f / 3.0f});
    myEngine.mvMatrixStack.popMatrix();
}


void drawWingSection7()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({2.0f, 0.0f, 0.0f});
        drawPart({1.0f, 2.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.5f, 0.0f, 0.0f});
        drawPart({2.0f, 2.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-1.0f, -0.5f, 0.0f});
        drawPart({1.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();

    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({2.0f, 1.5f, 1.0f / 6.0f});
        drawPart({1.0f, 1.0f, 2.0f / 3.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.0f, 1.5f, 1.0f / 6.0f});
        drawPart({1.0f, 1.0f, 2.0f / 3.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.5f, 1.0f / 6.0f});
        drawPart({1.0f, 1.0f, 2.0f / 3.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-1.0f, 0.5f, 1.0f / 6.0f});
        drawPart({1.0f, 1.0f, 2.0f / 3.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-2.0f, -0.5f, 1.0f / 6.0f});
        drawPart({1.0f, 1.0f, 2.0f / 3.0f});
    myEngine.mvMatrixStack.popMatrix();
    
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({2.0f, 2.0f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.0f, 0.0f});
        drawWingEnd1();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.0f, 2.0f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.0f, 0.0f});
        drawWingEnd2();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 2.0f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.0f, 0.0f});
        drawWingEnd2();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-1.0f, 1.0f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.0f, 0.0f});
        drawWingEnd2();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-2.0f, 0.0f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.0f, 0.0f});
        drawWingEnd2();
    myEngine.mvMatrixStack.popMatrix();
}


void drawWingSection6()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({2.0f, 0.0f, 0.0f});
        drawPart({1.0f, 2.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.5f, 0.0f, 0.0f});
        drawPart({2.0f, 2.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-1.0f, 0.0f, 0.0f});
        drawPart({1.0f, 2.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-2.0f, 0.0f, 0.0f});
        drawPart({1.0f, 2.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.0f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.0f, 0.0f});
        drawWingSection7();
    myEngine.mvMatrixStack.popMatrix();
}


void drawWingSection5()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.0f, 0.0f, 0.75f});
        drawPart({1.0f, 1.0f, 0.5f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.0f, 0.0f, 0.0f});
        drawPart({1.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-0.5f, 0.0f, 0.0f});
        drawPart({2.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-2.5f, 0.0f, 0.0f});
        drawPart({2.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.5f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.0f, 0.0f});
        drawWingSection6();
    myEngine.mvMatrixStack.popMatrix();
}


void drawWingSection4()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.0f, 0.0f, 0.0f});
        drawPart({1.0f, 2.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-0.5f, 0.0f, 0.0f});
        drawPart({2.0f, 2.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-2.5f, 0.0f, 0.0f});
        drawPart({2.0f, 2.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.0f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.5f, 0.0f});
        drawWingSection5();
    myEngine.mvMatrixStack.popMatrix();
}


void drawWingSection3()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.0f, 0.0f, 0.0f});
        drawPart({1.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-0.5f, 0.0f, 0.0f});
        drawPart({2.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-2.0f, 0.0f, 0.0f});
        drawPart({1.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.5f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 1.0f, 0.0f});
        drawWingSection4();
    myEngine.mvMatrixStack.popMatrix();
}


void drawWingSection2()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.0f, 0.0f, 0.0f});
        drawPart({1.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-0.5f, 0.0f, 0.0f});
        drawPart({2.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.5f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.5f, 0.0f});
        drawWingSection3();
    myEngine.mvMatrixStack.popMatrix();
}


void drawWingSection1()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.0f, 0.0f, 0.0f});
        drawPart({1.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-0.5f, 0.0f, 0.0f});
        drawPart({2.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.5f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.5f, 0.0f});
        drawWingSection2();
    myEngine.mvMatrixStack.popMatrix();
}


void drawWing()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addRotation(angle_wing, {1.0f, 0.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.5f, 0.0f});
        drawWingSection1();
    myEngine.mvMatrixStack.popMatrix();
}





void drawTailEnd()
{
    for (int i = 0; i < 9; i++) {
        auto size = 1.0f + i / 27.0f;
        myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({-size / 2.0f, 0.0f, 0.0f});
            drawPart({size, size, 1.0f});
        myEngine.mvMatrixStack.popMatrix();
        myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({-size, 0.0f, 0.0f});
            myEngine.mvMatrixStack.addRotation(angle_tail, {0.0f, 1.0f, 0.0f});
    }
    
    for (int i = 0; i < 9; i++) myEngine.mvMatrixStack.popMatrix();
}

void drawTailSection3()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, -(0.5f + 4.0f / 3.0f), 0.0f});
        drawPart({1.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 0.5f + 4.0f / 3.0f, 0.0f});
        drawPart({1.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-1.0f / 6.0f, 0.0f, 0.0f});
        drawPart({4.0f / 3.0f, 1.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-0.5f - 1.0f / 3.0f, 0.0f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_tail, {0.0f, 1.0f, 0.0f});
        drawTailEnd();
    myEngine.mvMatrixStack.popMatrix();
}


void drawTailSection2()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 2.0f / 3.0f, 0.0f});
        drawPart({4.0f / 3.0f, 4.0f / 3.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, -2.0f / 3.0f, 0.0f});
        drawPart({4.0f / 3.0f, 4.0f / 3.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-2.0f / 3.0f, 0.0f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_tail, {0.0f, 1.0f, 0.0f});
        myEngine.mvMatrixStack.addTranslation({-0.5f, 0.0f, 0.0f});
        drawTailSection3();
    myEngine.mvMatrixStack.popMatrix();
}

void drawTailSection1()
{
    myEngine.mvMatrixStack.pushMatrix();
        drawPart({1.0f, 2.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-0.5f, 0.0f, 0.0f});
        myEngine.mvMatrixStack.addRotation(angle_tail, {0.0f, 1.0f, 0.0f});
        myEngine.mvMatrixStack.addTranslation({-2.0f / 3.0f, 0.0f, 0.0f});
        drawTailSection2();
    myEngine.mvMatrixStack.popMatrix();
}

void drawTail()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addRotation(angle_tail, {0.0f, 1.0f, 0.0});
        myEngine.mvMatrixStack.addTranslation({-0.5f, 0.0f, 0.0f});
        drawTailSection1();
    myEngine.mvMatrixStack.popMatrix();
}




void drawHeadSection()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.25f / 2.0f, 0.0f, 0.0f});
        drawPart({1.25f, 1.25f, 1.25f});
        myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({0.0f, 0.0f, 1.55f / 2.0f});
            drawPart({0.7f, 0.7f, 0.3f});
        myEngine.mvMatrixStack.popMatrix();
        myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({3.75f / 2.0f, 0.0f, 0.1f});
            drawPart({2.5f, 1.0f, 0.3f});
        myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.popMatrix();
}

void drawNeckSection()
{
    for (int i = 0; i < 4; i++) {
        myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({0.5f, 0.0f, 0.0f});
            drawPart({1.0f, 1.0f, 1.0f});
        myEngine.mvMatrixStack.popMatrix();
        myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({1.0f, 0.0f, 0.0f});
            myEngine.mvMatrixStack.addRotation(angle_wing, {0.0f, 1.0f, 0.0});
            if (i == 3) drawHeadSection();
    }

    for (int i = 0; i < 4; i++) myEngine.mvMatrixStack.popMatrix();
}

void drawHead()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addRotation(angle_wing, {0.0f, 1.0f, 0.0});
        drawNeckSection();
    myEngine.mvMatrixStack.popMatrix();
}




void drawTorso()
{
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.0f, 2.0f / 3.0f, 0.0f});
        drawPart({1.0f, 4.0f / 3.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.0f, -2.0f / 3.0f, 0.0f});
        drawPart({1.0f, 4.0f / 3.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 2.0f / 3.0f, 0.0f});
        drawPart({1.0f, 4.0f / 3.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, -2.0f / 3.0f, 0.0f});
        drawPart({1.0f, 4.0f / 3.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-1.0f, 2.0f / 3.0f, 0.0f});
        drawPart({1.0f, 4.0f / 3.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-1.0f, -2.0f / 3.0f, 0.0f});
        drawPart({1.0f, 4.0f / 3.0f, 1.0f});
    myEngine.mvMatrixStack.popMatrix();
}



void drawSandBird()
{
    angle_wing = (M_PI / 180.0) * std::sin(glfwGetTime());
    angle_tail = (M_PI / 180.0) * std::sin(glfwGetTime() * M_PI / 2.5f);
    drawTorso();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, 4.0f / 3.0f, 0.0f});
        drawWing();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({0.0f, -4.0f / 3.0f, 0.0f});
        myEngine.mvMatrixStack.addHomothety({1.0f, -1.0f, 1.0f});
        drawWing();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({-1.5f, 0.0f, 0.0f});
        drawTail();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation({1.5f, 0.0f, 0.0f});
    drawHead();
    myEngine.mvMatrixStack.popMatrix();
}


