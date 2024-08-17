// ------------------------------------------------------------------------------
// Inclusões

#include "Player.h"

// ------------------------------------------------------------------------------

Player::Player()
{
	walking = new TileSet("Resources/WizardSprite.png", 70, 70, 4, 8);
	anim = new Animation(walking, 0.125f, true);

	uint SeqRight[4] = { 0,1,2,3 };
	uint SeqLeft[4] = { 4,5,6,7 };

	anim->Add(WALKRIGHT, SeqRight, 4);
	anim->Add(WALKLEFT, SeqLeft, 4);

	state = WALKLEFT;
	speed = 70.0f; // player se move de 70 em 70 pixels
	// 700 (tamanho da janela) / 70 (tamanho do player) = 10 (tamanho do quadro)
	// a janela tem 70 quadros de dimensão 10x10

	MoveTo(window->CenterX(), window->CenterY(), Layer::FRONT);

	timer = new Timer();
	timer->Start();

	moved = true;
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete walking;
	delete anim;
	delete timer;
}

// ---------------------------------------------------------------------------------

void Player::Move()
{
	// anda para cima
	if (window->KeyDown(VK_UP))
	{
		MoveTo(X(), Y() - speed);
	}
	else if (window->KeyDown(VK_DOWN))
	{
		// anda para baixo
		MoveTo(X(), Y() + speed);
	}
	else if (window->KeyDown(VK_LEFT))
	{
		// anda para esquerda
		state = WALKLEFT;
		MoveTo(X() - speed, Y());
	}
	else if (window->KeyDown(VK_RIGHT))
	{
		// anda para direita
		state = WALKRIGHT;
		MoveTo(X() + speed, Y());
	}
}

void Player::MoveTo(float px, float py, float layer)
{
	Object::MoveTo(px, py, layer);
	moved = true;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	// atualiza a cena caso player tenha movido e tenha se passado 200 ms
	if (timer->Elapsed(0.375f)) {
		Move();
		timer->Reset();
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
