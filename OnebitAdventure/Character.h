// Character.h

#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

// ------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animaçõoes de sprites
#include "Background.h"					// background do jogo
#include "OneBitAdventure.h"			// .h do jogo
#include "Font.h"						// fonte para exibir texto na tela

// ------------------------------------------------------------------------------

// Os casos WALKUp,WALKDOWN e STILL s�o os �nicos que n�o precisam de um sprite de costas e de frente.
// Logo, são opcionais, coloquei apenas para o caso de precisar.
// Como o personagem em estado STILL é o mesmo que o personagem em estado WALKRIGHT, não é necessário esse estado, mas... ne.

// ------------------------------------------------------------------------------
// Classe Character : É a classe base para todos os personagens (classes) do jogo

class Character : public Object
{
protected:
	// são comuns para todos os personagens e tem o mesmo valor
	steeringState characterState;				// estado atual do jogador
	Background* backg;					// background variável para obter informações do background do jogo
	float targetX = x;					// posição x do destino do jogador pós movimento
	float targetY = y;					// posição y do destino do jogador pós movimento
	float prevX = x;					// posição x anterior do jogador
	float prevY = y;					// posição y anterior do jogador
	float newX = x;						// nova posição x do jogador
	float newY = y;						// nova posição y do jogador
	steeringState direction;			// direção do jogador
	float interpolationSpeed;			// velocidade de interpolação
	float VelX;							// velocidade horizontal do jogador
	float VelY;							// velocidade vertical do jogador
	uint width;							// largura do Character
	uint height;						// altura do Character
	boolean isMoving = false;			// verifica se o personagem está se movendo
	bool isHit;							// Flag para indicar se o personagem já foi atingido
	bool isDead = false;				// Flag para indicar se o personagem está morto
	Font* consolas = new Font("Resources/consolas12.png");

	//--------------------------------------------------------------------------------------------
	// Atributos básicos do jogador

	int vida = 0;						// vida do jogador
	float danoAtaque = 0.0f;			// dano de ataque fisico do jogador (não utiliza mana e todas classes tem)
	TileSet* walking = nullptr;         // folha de sprites do personagem
	Animation* anim = nullptr;          // animação do personagem
	
	void InitializeBBox();				// inicializa a BBox
public:
	Character(float width, float height, Background* backg);	// construtor
	virtual ~Character() = 0;									// destrutor

	//--------------------------------------------------------------------------------------------

	// Métodos virtuais
	virtual void OnCollision(Object* obj) = 0;					// resolução da colisão

	//--------------------------------------------------------------------------------------------

	// Sobrescrevendo métodos virtuais de Object
	float X() const override;
	float Y() const override;
	float Z() const override;

	// Métodos de recuperação

	float GetDamage() const;	// retorna o dano de ataque do enemy
	int GetVida() const;		// retorna a vida do jogador
	void SetVida(float damage);	// retorna a vida do jogador
	boolean IsHit();			// verifica se o personagem foi atingido

	boolean IsMoving();			// verifica se o personagem está se movendo
	void Update();				// atualização
	void Draw();				// desenho
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Character::Draw()	
{
	anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

inline boolean Character::IsMoving()
{
	boolean move = isMoving;
	isMoving = false;
	return move;
}

// ---------------------------------------------------------------------------------

inline int Character::GetVida() const
{
	return vida;
}

// ---------------------------------------------------------------------------------

inline void Character::SetVida(float damage)
{
	vida = vida - damage;
}

// ---------------------------------------------------------------------------------

inline float Character::GetDamage() const
{
	return danoAtaque;
}

// ---------------------------------------------------------------------------------

inline boolean Character::IsHit()
{
	return isHit;
}

// ---------------------------------------------------------------------------------
// Métodos Inline sobrescritos de Object

inline float Character::X() const
{
	return x; // Ou você pode modificar se a lógica de posição for diferente
}

inline float Character::Y() const
{
	return y; // Ou você pode modificar se a lógica de posição for diferente
}

inline float Character::Z() const
{
	return z; // Ou você pode modificar se a lógica de posição for diferente
}

// -----------------------------------------------------------------------------

#endif // CHARACTER_H