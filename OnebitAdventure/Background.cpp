#include "Background.h"

// ---------------------------------------------------------------------------------

Background::Background()
{
    MoveTo(window->CenterX(), window->CenterY(), Layer::BACK);

    uint w = window->Width() / 3;
    uint h = window->Height() * 2;
    //backg = new TileSet(new Image("Resources/tam.png", w, h), w, h / 2, 2, 1);

    backg = new Sprite(new Image("Resources/tam.png", w, h));
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    delete backg;
}

// -------------------------------------------------------------------------------

void Background::Update()
{

}

// -------------------------------------------------------------------------------

void Background::Draw()
{
    // desenha pano de fundo (corrigir a posição de desenho)
    backg->Draw(window->CenterX(), backg->Height() / 2.0f, Layer::BACK);
}

// -------------------------------------------------------------------------------
