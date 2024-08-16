// ------------------------------------------------------------------------------
// Inclusões

#include "Engine.h"
#include "Home.h"

// ------------------------------------------------------------------------------

Scene* Home::scene = nullptr;

// ------------------------------------------------------------------------------

void Home::Init()
{
	scene = new Scene();

    backg = new Animation(new TileSet("Resources/telainicio.png", 700, 1400, 2, 2), 1.0f, true);

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

    backg->NextFrame();

    // atualiza cena do jogo
    scene->Update();

    // passa ao primeiro nível com ENTER
    /*if (window->KeyPress(VK_RETURN))
        Engine::Next<Level1>();*/
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete backg;
    delete scene;
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    backg->Draw(window->CenterX(), 2 * window->CenterY());
    scene->Draw();
}

// ------------------------------------------------------------------------------
