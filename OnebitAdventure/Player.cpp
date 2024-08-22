// ------------------------------------------------------------------------------
// Inclusões

#include "OneBitAdventure.h"
#include "Player.h"
#include <iostream>

// ------------------------------------------------------------------------------

Player::Player(float width, float height, Background * backg) : width((uint) width), height((uint) height), backg(backg)
{
	Image * img = new Image("Resources/WizardSprite.png", this->width * 4, this->height * 2); // carrega sprite sheet do player
	walking = new TileSet(img, this->width, this->height, 4, 8);		// 2x4 sprites
	anim = new Animation(walking, 0.125f, true);						// 0.125f é o tempo de troca de frames

	uint SeqRight[4] = { 0,1,2,3 }; // sequência de sprites para andar para a direita
	uint SeqLeft[4] = { 4,5,6,7 };  // sequência de sprites para andar para a esquerda
	anim->Add(WALKRIGHT, SeqRight, 4); // adiciona a sequência de sprites para andar para a direita
	anim->Add(WALKLEFT, SeqLeft, 4);   // adiciona a sequência de sprites para andar para a esquerda

	// Bounding Box do player (posição x e y começa no meio do sprite)
	BBox(new Rect(x - walking->TileWidth() / 2.0f, y - walking->TileHeight() / 2.0f, x + walking->TileWidth() / 2.0f, y + walking->TileHeight() / 2.0f));

	state = WALKLEFT;   // estado inicial do jogador
	type = PLAYER;      // tipo do jogador

	// Player se movimenta a cada quadro
	VelX = width;
	VelY = height;

	MoveTo(window->CenterX(), window->CenterY(), Layer::FRONT);

	targetX = X();
	targetY = Y();
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete walking;
	delete anim;
	delete timer;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{

}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	// Verifica se uma tecla de movimento foi pressionada e define o alvo
	if (window->KeyDown(VK_UP) && Y() == targetY) {
		targetY = Y() - VelY - 1;
	}
	else if (window->KeyDown(VK_DOWN) && Y() == targetY) {
		targetY = Y() + VelY + 1;
	}
	else if (window->KeyDown(VK_LEFT) && X() == targetX) {
		state = WALKLEFT;
		targetX = X() - VelX - 1;
	}
	else if (window->KeyDown(VK_RIGHT) && X() == targetX) {
		state = WALKRIGHT;
		targetX = X() + VelX + 1;
	}

	// Interpolação linear para suavizar o movimento
	float newX = X() + (targetX - X()) * interpolationSpeed * gameTime;
	float newY = Y() + (targetY - Y()) * interpolationSpeed * gameTime;

	// Garante que o personagem não ultrapasse o alvo, corrigindo a posição caso necessário
	if (abs(targetX - newX) < 0.5f) newX = targetX;
	if (abs(targetY - newY) < 0.5f) newY = targetY;

	// Move o personagem para a nova posição interpolada
	MoveTo(newX, newY);

	// Atualiza a animação
	anim->Select(state);
	anim->NextFrame();

	// Move background se o player passar da metade da tela para cima
	if (y < window->CenterY())
	{
		// Translate não é ideal
		backg->Translate(0, 1);
	}

	// Mantém personagem dentro da tela
	float diff = 0.067f * backg->Width();	// 49 pixels / largura do background = 0.067 de proporção
	if (x + width / 2.0f > window->CenterX() + backg->Width() / 2.0f - diff + 8.0f)
	{
		Translate(-4, 0);
		targetX = newX = window->CenterX() + backg->Width() / 2.0f - diff - width / 2.0f;
	}
	else if (x - width / 2.0f < window->CenterX() - backg->Width() / 2.0f + diff - 8.0f)
	{
		Translate(4, 0);
		targetX = newX = window->CenterX() - backg->Width() / 2.0f + diff + width / 2.0f;
	}
}

// ---------------------------------------------------------------------------------
