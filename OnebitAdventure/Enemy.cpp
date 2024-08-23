// ------------------------------------------------------------------------------
// Inclusões

#include <iostream>
#include "Enemy.h"

// ------------------------------------------------------------------------------

void Enemy::InitializeBBox()
{
	// Inicializa a BBox
	BBox(new Rect(x - walking->TileWidth() / 2.0f, y - walking->TileHeight() / 2.0f,
		x + walking->TileWidth() / 2.0f, y + walking->TileHeight() / 2.0f));
}

// ---------------------------------------------------------------------------------

// construtor para inicializar os atributos genéricos do enemy
Enemy::Enemy(float width, float height, Background* backg)
	: width(width), height(height), backg(backg), walking(nullptr), anim(nullptr) {

	state = WALKLEFT;			// estado inicial do enemy
	type = ENEMY;				// tipo do enemy

	VelX = width;				// velocidade horizontal do enemy (Em pixeis percorridos)
	VelY = height;				// velocidade vertical do enemy (Em pixeis percorridos)

	interpolationSpeed = 18.0f; // velocidade de interpolação
}

// ---------------------------------------------------------------------------------

Enemy::~Enemy()
{
	delete walking;
	delete anim;
}

// ---------------------------------------------------------------------------------

void Enemy::Update()
{
	// Verifica se uma tecla de movimento foi pressionada e define o alvo
	//if (window->KeyDown(VK_UP) && Y() == targetY) {
	//	targetY = Y() - VelY - 1;
	//}
	//else if (window->KeyDown(VK_DOWN) && Y() == targetY) {
	//	targetY = Y() + VelY + 1;
	//}
	//else if (window->KeyDown(VK_LEFT) && X() == targetX) {
	//	state = WALKLEFT;
	//	targetX = X() - VelX - 1;
	//}
	//else if (window->KeyDown(VK_RIGHT) && X() == targetX) {
	//	state = WALKRIGHT;
	//	targetX = X() + VelX + 1;
	//}

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

	// Move background se o Character passar da metade da tela para cima
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

	if (y + walking->TileHeight() / 2.0f > window->Height())
	{
		Translate(0, -4);
		targetY = newY = window->Height() - walking->TileHeight() / 2.0f;
	}
	else if (y - walking->TileHeight() / 2.0f < 0)
	{
		Translate(0, 4);
		targetY = newY = walking->TileHeight() / 2.0f;
	}
}

// ---------------------------------------------------------------------------------