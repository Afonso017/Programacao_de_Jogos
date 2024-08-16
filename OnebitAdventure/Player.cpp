// ------------------------------------------------------------------------------
// Inclusões

#include "Player.h"

// ------------------------------------------------------------------------------

Player::Player()
{
	walking = new TileSet("Resources/WarriorSprite.png", 64, 64, 4, 8);
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
	// atualiza animação
	anim->Select(state);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------