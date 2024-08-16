// ------------------------------------------------------------------------------
// Inclusões

#include "Engine.h"
#include "Home.h"

// ------------------------------------------------------------------------------

void Home::Init() {

    backg = new Sprite("Resources/telainicio.png");

	player = new Player();

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

	player->Update();

    // passa ao primeiro nível com ENTER
    /*if (window->KeyPress(VK_RETURN))
        Engine::Next<Level1>();*/
}

// ------------------------------------------------------------------------------

void Home::Finalize() {
    delete backg;
    delete player;
}

// ------------------------------------------------------------------------------

void Home::Draw() {
    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
	player->Draw();
}

// ------------------------------------------------------------------------------
