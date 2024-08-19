// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Engine.h"
#include "Home.h"

// ------------------------------------------------------------------------------

void Level1::Init()
{
    
	backg = new Sprite("Resources/tam.png");
    player = new Player(backg->Width(), backg->Height());

    scene = new Scene();
    scene->Add(player, MOVING);
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
    // desenha cena
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    scene->Draw();
    // scene->CollisionDetection();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete scene;   
	delete backg;
}

// ------------------------------------------------------------------------------
