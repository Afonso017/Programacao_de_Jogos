// ------------------------------------------------------------------------------
// Inclusões

#include "Engine.h"
#include "Sprite.h"
#include "Select.h"
#include "Home.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

void Select::Init()
{
	backg = new Sprite(new Image("Resources/TelaEscolha5.png", window->Width(), window->Height()));
}

// ------------------------------------------------------------------------------

void Select::Update()
{
	// volta para a tela inicial
	if (window->KeyPress(VK_ESCAPE))
	{
		Engine::Next<Home>();
		return;
	}

	// passa ao primeiro nível com ENTER
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
