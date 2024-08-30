// ------------------------------------------------------------------------------
// Inclus�es

#include "Engine.h"
#include "Home.h"
#include "Select.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
	// carrega o tile set do fundo
	Image* img = new Image("Resources/TitleScreen.png");
    tileBackg = new TileSet(img, 3840 / 2.0f, 1080, 2, 2);

    // tela de fundo � uma anima��o de um tile set 1x2
    backg = new Animation(tileBackg, 0.6f, true);
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
        Engine::Next<Select>();
        return;
    }

    backg->NextFrame();
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY());
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete backg;
	delete tileBackg; // libera mem�ria do tile set e da imagem
}

// ------------------------------------------------------------------------------
