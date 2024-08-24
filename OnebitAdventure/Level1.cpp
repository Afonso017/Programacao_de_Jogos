// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Engine.h"
#include "Select.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

Scene* Level1::scene = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    backg = new Background();

    consolas = new Font("Resources/consolas12.png");
    consolas->Spacing("Resources/consolas12.dat");

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

	string dano = "Dano: ";
	dano.append(std::to_string(warrior->GetDamage()));
	dano.append(" Vida: ");
	dano.append(std::to_string(ghost->GetVida()));
        
    consolas->Draw(975, 150, dano, Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.0f, 0.0f);
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete scene;
    delete consolas;
}

// ------------------------------------------------------------------------------
