// ------------------------------------------------------------------------------
// Inclusões

#include "Engine.h"
#include "Home.h"
#include "Select.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
    // Carrega a imagem e redimensiona conforme o tamanho da janela
    Image* img = new Image("Resources/TitleScreen.png", window->Width() * 2.0f, window->Height());

    TileSet* tileBackg = new TileSet(img, img->Width() / 2.0f, img->Height(), 2, 2);

    // tela de fundo é uma animação de um tile set 1x2
    backg = new Animation(tileBackg, 0.6f, true);
}

// ------------------------------------------------------------------------------

void Home::Update()
{
    // sai do jogo com a tecla ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // passa ao primeiro nível com ENTER
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
}

// ------------------------------------------------------------------------------
