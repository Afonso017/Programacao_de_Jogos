// Enemy.h
// ------------------------------------------------------------------------------
// Inclusões

#ifndef ENEMY_H
#define ENEMY_H

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animaçõoes de sprites
#include "Background.h"					// background do jogo
#include "OneBitAdventure.h"			// .h do jogo
#include "Character.h"					// classe base para todos os personagens

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
	float interpolationSpeed;			// velocidade de interpolação
	float VelX;							// velocidade horizontal do enemy
	float VelY;							// velocidade vertical do enemy
	uint width;							// largura do Enemy
	uint height;						// altura do Enemy
	float proximityThreshold;			// Distância para começar a perseguir o player
	float newX;
	float newY;

	//--------------------------------------------------------------------------------------------
	// Atributos básicos do enemy

	int vida = 0;						// vida do enemy
	float danoAtaque = 0.0f;			// dano de ataque fisico do enemy (não utiliza mana e todas classes tem)
	TileSet* walking = nullptr;         // folha de sprites do personagem
	Animation* anim = nullptr;          // animação do personagem

	void InitializeBBox();				// inicializa a BBox
	void MoveRandomly();				// movimentação aleatória
public:
	Enemy(float width, float height, Background* backg, Character* player);	// construtor
	virtual ~Enemy() = 0;																// destrutor

	// Métodos virtuais
	virtual void OnCollision(Object* obj) = 0;				// resolução da colisão

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

#endif