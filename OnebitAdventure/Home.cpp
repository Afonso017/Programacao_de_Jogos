// ------------------------------------------------------------------------------
// Inclusões

#include "Engine.h"
#include "Home.h"

// ------------------------------------------------------------------------------

Scene* Home::scene = nullptr;

// ------------------------------------------------------------------------------

void Home::Init() {

	scene = new Scene();

    backg = new Sprite("Resources/telainicio2.png");

	player = new Player();

    scene->Add(player, MOVING);
}

// ------------------------------------------------------------------------------

void Home::Update()
{
    // sai do jogo com a tecla ESC
    if (ctrlKeyESC && window->KeyDown(VK_ESCAPE)) // Se apertou esc, mas ctrlKeyESC é false, na próxima fecha.
    {
        ctrlKeyESC = false;
        window->Close();
    }
    else if (window->KeyUp(VK_ESCAPE))
    {
        ctrlKeyESC = true;
    }

    // atualiza cena do jogo
    scene->Update();

    // passa ao primeiro nível com ENTER
    /*if (window->KeyPress(VK_RETURN))
        Engine::Next<Level1>();*/
}

// ------------------------------------------------------------------------------

void Home::Finalize() {
    delete backg;
    delete scene;
}

// ------------------------------------------------------------------------------

void Home::Draw() {
    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
    scene->Draw();
}

// ------------------------------------------------------------------------------
