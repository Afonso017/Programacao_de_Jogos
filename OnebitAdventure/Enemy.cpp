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
Enemy::Enemy(float width, float height, Background* backg, Character* player)
	: width(width), height(height), backg(backg), player(player), walking(nullptr), anim(nullptr) {

	enemyState = WALKLEFT;		// estado inicial do enemy
	type = ENEMY;				// tipo do enemy

	VelX = width;				// velocidade horizontal do enemy (Em pixeis percorridos)
	VelY = height;				// velocidade vertical do enemy (Em pixeis percorridos)

	interpolationSpeed = 18.0f; // velocidade de interpolação

	proximityThreshold = 100.0f; // Distância para começar a perseguir o player
}

Enemy::~Enemy()
{
}

// ---------------------------------------------------------------------------------

void Enemy::Update() {
	if (player->IsMoving()) {
		// Distância do inimigo ao player
		float deltaX = player->X() - X();
		float deltaY = player->Y() - Y();

		// Calcular a distância ao quadrado (mais eficiente do que calcular a distância real)
		float distanceSquared = deltaX * deltaX + deltaY * deltaY;

		// Se o player está próximo, o inimigo tende a se mover em direção ao player
		if (distanceSquared < proximityThreshold * proximityThreshold) {
			// 75% de chance de ir na direção do player
			if (rand() % 100 < 85) {
				if (abs(deltaX) > abs(deltaY)) {
					if (deltaX > 0) targetX += VelX; // Mover para a direita
					else targetX -= VelX;            // Mover para a esquerda
				}
				else {
					if (deltaY > 0) targetY += VelY; // Mover para baixo
					else targetY -= VelY;            // Mover para cima
				}
			}
			else {
				// 15% de chance de se mover aleatoriamente
				MoveRandomly();
			}
		}
		else {
			// Se o player está longe, o inimigo se move aleatoriamente
			MoveRandomly();
		}
	}

		// Interpolação linear e outras lógicas permanecem as mesmas
		newX = X() + (targetX - X()) * interpolationSpeed * gameTime;
		newY = Y() + (targetY - Y()) * interpolationSpeed * gameTime;

		// Garante que o personagem não ultrapasse o alvo
		if (abs(targetX - newX) < 0.5f) newX = targetX;
		if (abs(targetY - newY) < 0.5f) newY = targetY;

		// Move o personagem para a nova posição interpolada
		MoveTo(newX, newY);

		// Atualiza a animação
		anim->Select(enemyState);
		anim->NextFrame();

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

void Enemy::MoveRandomly() {
	int direction = rand() % 4; // 4 direções possíveis
	switch (direction) {
		case 0: targetX = X() + VelX + 1; break; // Direita
		case 1: targetX = X() - VelX - 1; break; // Esquerda
		case 2: targetY = Y() + VelY + 1; break; // Baixo
		case 3: targetY = Y() - VelY - 1; break; // Cima
	}
}