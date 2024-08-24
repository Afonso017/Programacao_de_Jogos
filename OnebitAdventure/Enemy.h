// Enemy.h
// ------------------------------------------------------------------------------
// Inclusões

#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animaçõoes de sprites
#include "Background.h"					// background do jogo
#include "OneBitAdventure.h"			// .h do jogo
#include "Character.h"					// classe base para todos os personagens
#include "Font.h"						// fonte para exibir texto na tela

// ------------------------------------------------------------------------------

class Enemy : public Object
{
protected:
	// são comuns para todos os personagens e tem o mesmo valor
	steeringState enemyState;			// estado atual do enemy
	Background* backg;					// background variável para obter informações do background do jogo
	Character* player;					// enemy do jogo
	float targetX = x;					// posição x do destino do enemy pós movimento
	float targetY = y;					// posição y do destino do enemy pós movimento
	float prevX = x;					// posição x anterior do jogador
	float prevY = y;					// posição y anterior do jogador
	float newX = x;						// nova posição x do jogador
	float newY = y;						// nova posição y do jogador
	float interpolationSpeed;			// velocidade de interpolação
	float VelX;							// velocidade horizontal do enemy
	float VelY;							// velocidade vertical do enemy
	uint width;							// largura do Enemy
	uint height;						// altura do Enemy
	float proximityThreshold;			// Distância para começar a perseguir o player
	bool isHit;							// Flag para indicar se o personagem já foi atingido
	Font* consolas = new Font("Resources/consolas12.png");

	//--------------------------------------------------------------------------------------------
	// Atributos básicos do enemy
	float danoAtaque = 0.0f;			// dano de ataque fisico do enemy (não utiliza mana e todas classes tem)
	int vida = 0;						// vida do enemy
	TileSet* walking = nullptr;         // folha de sprites do personagem
	Animation* anim = nullptr;          // animação do personagem

	void InitializeBBox();				// inicializa a BBox
	void MoveRandomly();				// movimentação aleatória
public:
	Enemy(float width, float height, Background* backg, Character* player);	// construtor
	virtual ~Enemy() = 0;													// destrutor

	// Métodos virtuais
	virtual void OnCollision(Object* obj) = 0;				// resolução da colisão

	// Métodos de recuperação

	float GetDamage() const;								// retorna o dano de ataque do enemy
	void SetVida(float damage);								// retorna a vida do enemy
	int GetVida() const;									// retorna a vida do enemy
	boolean IsHit();										// verifica se o personagem foi atingido

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

inline float Enemy::GetDamage() const
{
	return danoAtaque;
}

// ---------------------------------------------------------------------------------

inline void Enemy::SetVida(float damage)
{
	vida = vida - damage;
}

// ---------------------------------------------------------------------------------

inline int Enemy::GetVida() const
{
	return vida;
}

// ---------------------------------------------------------------------------------

inline boolean Enemy::IsHit()
{
	return isHit;
}

// ---------------------------------------------------------------------------------

#endif