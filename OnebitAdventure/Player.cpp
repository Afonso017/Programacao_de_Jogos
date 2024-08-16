// ------------------------------------------------------------------------------
// Inclusões

#include "Player.h"

// ------------------------------------------------------------------------------

Player::Player()
{
	walking = new TileSet("Resources/WizardSprite2.png", 64, 64, 4, 8);
	anim = new Animation(walking, 0.070f, true);

	uint SeqRight[8] = { 0,1,2,3};
	uint SeqLeft[8] = { 4,5,6,7 };

	anim->Add(WALKRIGHT, SeqRight, 4);
	anim->Add(WALKLEFT, SeqLeft, 4);

	state = WALKLEFT;
	speed = 300.0f;
	MoveTo(window->CenterX(), window->CenterY(), Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete walking;
	delete anim;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	// anda para cima
	if (window->KeyDown(VK_UP))
	{
		Translate(0, -speed * gameTime);
	}

	// anda para baixo
	if (window->KeyDown(VK_DOWN))
	{
		Translate(0, speed * gameTime);
	}

	// anda para esquerda
	if (window->KeyDown(VK_LEFT))
	{
		state = WALKLEFT;
		Translate(-speed * gameTime, 0);
	}

	// anda para direita
	if (window->KeyDown(VK_RIGHT))
	{
		state = WALKRIGHT;
		Translate(speed * gameTime, 0);
	}

	// atualiza animação
	anim->Select(state);
	anim->NextFrame();

	// mantém personagem dentro da tela
	if (x + walking->TileWidth() / 2.0f > window->Width())
		MoveTo(window->Width() - walking->TileWidth() / 2.0f, y);

	if (x - walking->TileWidth() / 2.0f < 0)
		MoveTo(walking->TileWidth() / 2.0f, y);

	if (y + walking->TileHeight() / 2.0f > window->Height())
		MoveTo(x, window->Height() - walking->TileHeight() / 2.0f);

	if (y - walking->TileHeight() / 2.0f < 0)
		MoveTo(x, walking->TileHeight() / 2.0f);
}

// ---------------------------------------------------------------------------------