// Enemy.h
#pragma once
// ------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animaçõoes de sprites
#include "Background.h"					// background do jogo
#include "OneBitAdventure.h"

// ------------------------------------------------------------------------------

class Enemy : public Object
{
protected:
	// são comuns para todos os personagens e tem o mesmo valor
	steeringState state;				// estado atual do enemy
	Background* backg;					// background variável para obter informações do background do jogo
	float targetX = x;					// posição x do destino do jogador pós movimento
	float targetY = y;					// posição y do destino do jogador pós movimento
	float interpolationSpeed;			// velocidade de interpolação
	float VelX;							// velocidade horizontal do jogador
	float VelY;							// velocidade vertical do jogador
	uint width;							// largura do Enemy
	uint height;						// altura do Enemy

	//--------------------------------------------------------------------------------------------
	// Atributos básicos do jogador

	int vida = 0;						// vida do jogador
	float danoAtaque = 0.0f;			// dano de ataque fisico do jogador (não utiliza mana e todas classes tem)
	TileSet* walking = nullptr;         // folha de sprites do personagem
	Animation* anim = nullptr;          // animação do personagem

	void InitializeBBox();				// inicializa a BBox
public:
	Enemy(float width, float height, Background* backg);	// construtor
	~Enemy();												// destrutor

	// Métodos virtuais
	virtual void OnCollision(Object* obj) = 0;					// resolução da colisão

	// Métodos
	void Update();											// atualização
	void Draw();											// desenho
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Enemy::Draw() {
	// Desenha o inimigo
	anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------