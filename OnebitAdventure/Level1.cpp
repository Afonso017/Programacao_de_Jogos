// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Engine.h"
#include "Select.h"
#include "Warrior.h"
#include "Ghost.h"

// ------------------------------------------------------------------------------

Character * Level1::player  = nullptr;
Enemy     * Level1::enemy   = nullptr;
Hud       * Level1::hud     = nullptr;
Scene     * Level1::scene   = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    // Background original tem 11.25 quadros de largura e 38.57 de altura
    float tileWidth = (window->Width() / 3.0f - 98.0f) / 11.0f;
    float tileHeight = window->Height() / 19.0f;

    hud = new Hud(tileWidth, tileHeight);
    player = new Warrior(tileWidth, tileHeight);
    enemy = new Ghost(tileWidth, tileHeight);

    scene = new Scene();
    scene->Add(hud, STATIC);
    scene->Add(player, MOVING);
	scene->Add(enemy, MOVING);
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
        viewBox = !viewBox;

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
