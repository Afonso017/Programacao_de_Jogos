// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Engine.h"
#include "Select.h"
#include "Warrior.h"
#include "Ghost.h"

// ------------------------------------------------------------------------------

Character * Level1::player  = nullptr;
Hud       * Level1::hud     = nullptr;
Scene     * Level1::scene   = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    // Background original tem 11 quadros de largura e 19 de altura
    float width = window->Width() / 2.5f;
    float tileWidth = (width - width * 0.12f) / 11.25f;
    float tileHeight = window->Height() / 19.0f;

    scene = new Scene();

    hud = new Hud(tileWidth, tileHeight);
    player = new Warrior(tileWidth, tileHeight);

    // Inicializa a posição do Ghost 1
    float col = hud->Col(5);
    float line = hud->Line(11);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(hud, STATIC);
    scene->Add(player, MOVING);
    scene->Add(enemy, MOVING);

    col = hud->Col(2);
    line = hud->Line(15);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(enemy, MOVING);

    col = hud->Col(4);
    line = hud->Line(16);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(enemy, MOVING);

    col = hud->Col(5);
    line = hud->Line(9);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(enemy, MOVING);

    col = hud->Col(8);
    line = hud->Line(10);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(enemy, MOVING);

    col = hud->Col(9);
    line = hud->Line(17);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(enemy, MOVING);

    col = hud->Col(10);
    line = hud->Line(1);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

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
