// ------------------------------------------------------------------------------
// Inclus�es

#include "Engine.h"
#include "Home.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
    // tela de fundo � uma anima��o de um tile set 1x2
    backg = new Animation(new TileSet("Resources/telainicio.png", 700, 1400, 2, 2), 1.0f, true);
}

// ------------------------------------------------------------------------------

void Home::Update()
{
    // sai do jogo com a tecla ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();
    
    // passa ao primeiro n�vel com ENTER
    if (window->KeyPress(VK_RETURN))
    {
        Engine::Next<Level1>();
        return;
    }

    backg->NextFrame();
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    backg->Draw(window->CenterX(), 2 * window->CenterY());
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete backg;
}

// ------------------------------------------------------------------------------
