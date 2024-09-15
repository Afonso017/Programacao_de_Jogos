// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Select.h"
#include "Warrior.h"
#include "Ghost.h"
#include "Engine.h"

// ------------------------------------------------------------------------------

Scene     * Level1::scene   = nullptr;
Hud       * Level1::hud     = nullptr;
Map       * Level1::map     = nullptr;
Character * Level1::player  = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    scene = new Scene();
    hud = new Hud();
    map = new Map(50);
    player = new Warrior(5, 7);
    
    scene->Add(hud, STATIC);
    scene->Add(player, MOVING);
    scene->Add(new Ghost(8, 12), MOVING);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{   
    // volta para a tela de inicio
    if (window->KeyPress(VK_ESCAPE))
    {
        Engine::Next<Select>();
    }
    else if (window->KeyPress('B'))
    {
        viewBox = !viewBox;
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    // desenha cena
    scene->Draw();

    if (viewBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete scene;
}

// ------------------------------------------------------------------------------
