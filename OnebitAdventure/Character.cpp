// ------------------------------------------------------------------------------
// Inclus�es

#include "Character.h"
#include <iostream>
#include "Enemy.h"

// ------------------------------------------------------------------------------

void Character::InitializeBBox()
{
	// Inicializa a BBox
	BBox(new Rect(x - walking->TileWidth() / 2.0f, y - walking->TileHeight() / 2.0f,
		x + walking->TileWidth() / 2.0f, y + walking->TileHeight() / 2.0f));
}

// ---------------------------------------------------------------------------------

// construtor para inicializar os atributos gen�ricos do jogador
Character::Character(float width, float height, Background* backg)
	: width(width), height(height), backg(backg), walking(nullptr), anim(nullptr) {

	characterState = WALKLEFT;	// estado inicial do jogador
	direction = WALKLEFT;		// dire��o inicial do jogador
	type = PLAYER;				// tipo do jogador

	VelX = width;				// velocidade horizontal do jogador (Em pixeis percorridos)
	VelY = height;				// velocidade vertical do jogador (Em pixeis percorridos)

	interpolationSpeed = 18.0f; // velocidade de interpola��o

	prevX = x;					// posi��o x anterior do jogador
	prevY = y;					// posi��o y anterior do jogador
}

// ---------------------------------------------------------------------------------

Character::~Character()
{	
}

// ---------------------------------------------------------------------------------

void Character::Update()
{
	// Verifica se uma tecla de movimento foi pressionada e define o alvo
	if (window->KeyDown(VK_UP) && Y() == targetY) {
		prevY = Y();
		direction = WALKUP;
		targetY = Y() - VelY - 1; 
		isMoving = true;
	}
	else if (window->KeyDown(VK_DOWN) && Y() == targetY) {
		prevY = Y();
		direction = WALKDOWN;
		targetY = Y() + VelY + 1;
		isMoving = true;
	}
	else if (window->KeyDown(VK_LEFT) && X() == targetX) {
		prevX = X();
		direction = WALKLEFT;
		characterState = WALKLEFT;
		targetX = X() - VelX - 1;
		isMoving = true;
	}
	else if (window->KeyDown(VK_RIGHT) && X() == targetX) {
		prevX = X();
		direction = WALKRIGHT;
		characterState = WALKRIGHT;
		targetX = X() + VelX + 1;
		isMoving = true;
	}

	// Interpola��o linear para suavizar o movimento
	newX = X() + (targetX - X()) * interpolationSpeed * gameTime;
	newY = Y() + (targetY - Y()) * interpolationSpeed * gameTime;

	// Garante que o personagem n�o ultrapasse o alvo, corrigindo a posi��o caso necess�rio
	if (abs(targetX - newX) < 0.5f) newX = targetX;
	if (abs(targetY - newY) < 0.5f) newY = targetY;

	// Move o personagem para a nova posi��o interpolada
	MoveTo(newX, newY);

	// Atualiza a anima��o
	anim->Select(characterState);
	anim->NextFrame();

	// Move background se o Character passar da metade da tela para cima
	if (y < window->CenterY())
	{
		// Translate n�o � ideal
		//backg->Translate(0, 1);
	}

	// Mant�m personagem dentro da tela
	float diff = 0.067f * backg->Width();	// 49 pixels / largura do background = 0.067 de propor��o

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
		Translate(0,-4);
		targetY = newY = window->Height() - walking->TileHeight() / 2.0f;
	}
	else if (y - walking->TileHeight() / 2.0f < 0) 
	{
		Translate(0,4);
		targetY = newY = walking->TileHeight() / 2.0f;
	}	
}

// ---------------------------------------------------------------------------------