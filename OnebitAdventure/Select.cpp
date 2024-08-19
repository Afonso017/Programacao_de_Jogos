// ------------------------------------------------------------------------------
// Inclus�es

#include "Engine.h"
#include "Sprite.h"
#include "Select.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

void Select::Init()
{
	backg = new Sprite("Resources/TelaEscolha5.png");
}

// ------------------------------------------------------------------------------

void Select::Update()
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
}

// ------------------------------------------------------------------------------

void Select::Draw()
{
	backg->Draw(window->CenterX(), window->CenterY());
}

// ------------------------------------------------------------------------------

void Select::Finalize()
{
	delete backg;
}

// ------------------------------------------------------------------------------
