// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Engine.h"
#include "Home.h"

// ------------------------------------------------------------------------------

void Level1::Init()
{
    player = new Player();

    scene = new Scene();
    scene->Add(player, PLAYER);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{   
    // volta para a tela de inicio
    if (window->KeyPress(VK_ESCAPE))
    {
        Engine::Next<Home>();
        return;
    }

    scene->Update();
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    scene->Draw();
    // scene->CollisionDetection();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete scene;
}

// ------------------------------------------------------------------------------
