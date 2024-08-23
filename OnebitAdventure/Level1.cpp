// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Engine.h"
#include "Select.h"

// ------------------------------------------------------------------------------

void Level1::Init()
{
    backg = new Background();

    // Background original tem 11.25 quadros de largura e 38.57 de altura
    warrior = new Warrior((backg->Width() - backg->Width() * 0.13f) / 11.25f, backg->Height() / 38.57f, backg);
	

    scene = new Scene();
    scene->Add(warrior, MOVING);

    ghost = new Ghost((backg->Width() - backg->Width() * 0.13f) / 11.25f, backg->Height() / 38.57f, backg, warrior);

	scene->Add(ghost, MOVING);
    scene->Add(backg, STATIC);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{   
    // volta para a tela de inicio
    if (window->KeyPress(VK_ESCAPE))
    {
        Engine::Next<Select>();
        return;
    }

    if (window->KeyPress('B'))
        viewBox = ~viewBox;

    scene->Update();

	scene->CollisionDetection();
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    // desenha cena
    scene->Draw();
    // scene->CollisionDetection();

    if (viewBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete scene;
}

// ------------------------------------------------------------------------------
