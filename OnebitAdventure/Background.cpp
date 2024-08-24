#include "Background.h"

// ---------------------------------------------------------------------------------

Background::Background()
{
    MoveTo(window->CenterX(), 0, Layer::BACK);

	// Divide a largura da janela por 3 e multiplica a altura por 2
    width = window->Width() / 3;
    height = window->Height() * 2;

    backg = new Sprite(new Image("Resources/tam.png", width, height));
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    delete backg;
}

// -------------------------------------------------------------------------------

void Background::Update()
{
    // Mantém background dentro da janela
    if (y - backg->Height() / 2.0f > 0)
        MoveTo(x, window->Height() - 1.0f);
    else if (y + backg->Height() / 2.0f < window->Height())
        MoveTo(x, -backg->Height() / 2.0f);
}

// -------------------------------------------------------------------------------
