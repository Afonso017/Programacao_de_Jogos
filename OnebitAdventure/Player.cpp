// ------------------------------------------------------------------------------
// Inclusões

#include "OneBitAdventure.h"
#include "Player.h"
#include <iostream>

// ------------------------------------------------------------------------------

Player::Player(int widthT, int heightT)
{
	walking = new TileSet("Resources/WizardSprite.png", 70, 70, 4, 8);  // 4x8 sprites de 70x70
	anim = new Animation(walking, 0.125f, true);						// 0.125f é o tempo de troca de frames

	BBox(new Rect(x - walking->TileWidth() / 2.0f, y - walking->TileHeight() / 2.0f, x + walking->TileWidth() / 2.0f, y + walking->TileHeight() / 2.0f));

	uint SeqRight[4] = { 0,1,2,3 }; // sequência de sprites para andar para a direita
	uint SeqLeft[4] = { 4,5,6,7 };  // sequência de sprites para andar para a esquerda

	anim->Add(WALKRIGHT, SeqRight, 4); // adiciona a sequência de sprites para andar para a direita
	anim->Add(WALKLEFT, SeqLeft, 4);   // adiciona a sequência de sprites para andar para a esquerda

	state = WALKLEFT;   // estado inicial do jogador

	type = PLAYER;      // tipo do jogador

	VelX = 57.0f;       // Esses foram os valores ideias que encontrei para o movimento do player
	VelY = 60.0f;	    // Esses foram os valores ideias que encontrei para o movimento do player
	vel = 5.0f;

	width = widthT;     // largura da tela
	height = heightT;   // altura da tela

	
	// 700 (tamanho da janela) / 70 (tamanho do player) = 10 (tamanho do quadro)
	// a janela tem 70 quadros de dimensão 10x10

	MoveTo(window->CenterX(), window->CenterY() - 3, Layer::FRONT);

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
	float interpolationSpeed = 12.0f; // Velocidade de interpolação

	// Verifica se uma tecla de movimento foi pressionada e define o alvo
	if (window->KeyDown(VK_UP) && Y() == targetY) {
		targetY = Y() - 60.0f; // Movimenta exatamente 60 pixels para cima
	}
	else if (window->KeyDown(VK_DOWN) && Y() == targetY) {
		targetY = Y() + 60.0f; // Movimenta exatamente 60 pixels para baixo
	}
	else if (window->KeyDown(VK_LEFT) && X() == targetX) {
		state = WALKLEFT;
		targetX = X() - 57.0f; // Movimenta exatamente 57 pixels para a esquerda
	}
	else if (window->KeyDown(VK_RIGHT) && X() == targetX) {
		state = WALKRIGHT;
		targetX = X() + 57.0f; // Movimenta exatamente 57 pixels para a direita
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

	// Mantém personagem dentro da tela
	if (x + walking->TileWidth() / 2.0f > (window->CenterX() + (width - 85) / 2.0f)) {
		MoveTo(window->CenterX() + (width - 160) / 2.0f, y);
		newX = window->CenterX() + ((width - 160) / 2.0f);
		targetX = newX;
	}
		

	if (x - walking->TileWidth() / 2.0f < window->CenterX() - ((width - 85) / 2.0f)) {
		MoveTo(window->CenterX() - ((width - 160) / 2.0f), y);
		newX = window->CenterX() - ((width - 160) / 2.0f);
		targetX = newX;
	}
		

	if (y + walking->TileHeight() / 2.0f > window->Height())
		MoveTo(x, window->Height() - walking->TileHeight() / 2.0f);

	if (y - walking->TileHeight() / 2.0f < 0)
		MoveTo(x, walking->TileHeight() / 2.0f);
}

// ---------------------------------------------------------------------------------
