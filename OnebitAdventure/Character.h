// Character.h

#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

// ------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animaçõoes de sprites
#include "OneBitAdventure.h"			// .h do jogo
#include "Font.h"						// fonte para exibir texto na tela
#include "string"						// biblioteca STL
#include <unordered_map>				// biblioteca STL                
using std::unordered_map;				// namespace para unordered_map

// ------------------------------------------------------------------------------

// Os casos WALKUp,WALKDOWN e STILL sao os unicos que nao precisam de um sprite de costas e de frente.
// Logo, sao opcionais, coloquei apenas para o caso de precisar.
// Como o personagem em estado STILL e o mesmo que o personagem em estado WALKRIGHT, nao e necessario esse estado, mas... ne.

// ------------------------------------------------------------------------------
// Classe Character : É a classe base para todos os personagens (classes) do jogo

class Character : public Object
{
protected:
	// são comuns para todos os personagens e tem o mesmo valor

	// --------------------------------------------------------------------------------------------
	// Estados do jogador

	MovementType movementType;			// Próxima animação a ser executada
	DirectingAnimation characterState;	// estado atual do jogador
	DirectingAnimation direction;		// direção do jogador
	bool isHit;							// Flag para indicar se o personagem já atacou
	bool isDead;						// Flag para indicar se o personagem está morto
	bool isMoving;						// verifica se o personagem está se movendo

	// --------------------------------------------------------------------------------------------
	// Atributos de movimentação

	float interpolationSpeed;			// velocidade de interpolação
	float VelX;							// velocidade horizontal do jogador
	float VelY;							// velocidade vertical do jogador
	float targetX;						// posição x do destino do jogador pós movimento
	float targetY;						// posição y do destino do jogador pós movimento
	float prevX;						// posição x anterior do jogador
	float prevY;						// posição y anterior do jogador
	float newX;							// nova posição x do jogador
	float newY;							// nova posição y do jogador

	// --------------------------------------------------------------------------------------------
	// Atributos de sprites e animação

	TileSet* walking = nullptr;         // folha de sprites do personagem
	Animation* anim = nullptr;          // animação do personagem
	uint width;							// largura do Character
	uint height;						// altura do Character

	// --------------------------------------------------------------------------------------------
	// Objetos auxiliares para construções de lógicas

	unordered_map<string, Color> text;  // unordered_map para armazenar o texto a ser exibido na tela
	Timer* timer;						// timer para controlar o tempo de exibição do texto
	Font* press12;						// fonte para exibir texto na tela
	Timer* speedMovement;				// timer para controlar a velocidade de movimento do jogador
	Timer* attackTimer;					// timer para controlar o tempo de ataque do jogador
	Sprite* xpBar;							// sprite para representar a experiência do jogador

	//--------------------------------------------------------------------------------------------
	// Atributos básicos de todo jogador

	int maxLife = 0;
	int vida = 0;						// vida do jogador
	int danoAtaque = 0;					// dano de ataque fisico do jogador (não utiliza mana e todas classes tem)
	int level;							// nível do jogador
	int xp;								// experiência do jogador
	int maxXp;							// experiência máxima do jogador

	// --------------------------------------------------------------------------------------------
	// Métodos protegidos 

	void InitializeBBox();										// inicializa a BBox

public:
	Character(float width, float height);						// construtor
	virtual ~Character() = 0;									// destrutor

	//--------------------------------------------------------------------------------------------
	// Métodos virtuais

	virtual void OnCollision(Object* obj) = 0;					// resolução da colisão

	//--------------------------------------------------------------------------------------------
	// Sobrescrevendo métodos virtuais de Object

	float X() const override;
	float Y() const override;
	float Z() const override;

	//--------------------------------------------------------------------------------------------
	// Métodos de movimentação e animação

	void HandleInput();							// movimentação do jogador
	void SetMovementDirection(DirectingAnimation newDirection, DirectingAnimation newAnimation, float deltaX, float deltaY); // seta a direção do jogador
	void InterpolateMovement(float gameTime);	// interpolação do movimento do jogador
	void UpdateAnimation();						// atualiza a animação do jogador
	void ConstrainToScreen();					// limita o jogador a tela
	void BackMovement();						// lógica de movimento de recuo do jogador

	//--------------------------------------------------------------------------------------------
	// Métodos de recuperação e modificação de atributos

	int GetDamage() const;									// retorna o dano de ataque do enemy
	int GetVida() const;									// retorna a vida do jogador
	void SetVida(int damage);								// retorna a vida do jogador
	int MaxLife() const;									// retorna a vida máxima do jogador
	float GetTargetX() const;								// retorna a posição x do destino do jogador
	float GetTargetY() const;								// retorna a posição y do destino do jogador
	float GetPrevX() const;									// retorna a posição x anterior do jogador
	float GetPrevY() const;									// retorna a posição y anterior do jogador
	float GetVelX() const;									// Retorna a velocidade horizontal do inimigo
	float GetVelY() const;									// Retorna a velocidade vertical do inimigo
	void setXp(int xp);										// seta a experiência do jogador
	DirectingAnimation GetDirection() const;				// retorna a direção do jogador
	void setIsMoving(boolean move);							// seta se o personagem está se movendo
	boolean IsHit() const;									// verifica se o personagem foi atingido
	MovementType GetMovementType() const;					// retorna o tipo de movimento do jogador
	void SetMovementType(MovementType newMovementType);		// seta o tipo de movimento do jogador

	// --------------------------------------------------------------------------------------------
	// Métodos auxiliares

	bool IsMoving() const;									// verifica se o personagem está se movendo
	void Update();											// atualização
	void Draw();											// desenho
	void DrawTextGet();										// desenha o texto na tela
	void DrawExperienceBar();								// desenha a barra de experiência do jogador
	void DrawLevelAndXp();									// desenha o level e a experiência do jogador
};

// --------------------------------------------------------------------------------------------------
// Função Membro Inline

inline bool Character::IsMoving() const
{
	return isMoving;
}

// ---------------------------------------------------------------------------------

inline DirectingAnimation Character::GetDirection() const
{
	return direction;
}

// ---------------------------------------------------------------------------------

inline int Character::GetVida() const
{
	return vida;
}

// ---------------------------------------------------------------------------------

inline void Character::SetMovementType(MovementType newMovementType)
{
	movementType = newMovementType;
}

// ---------------------------------------------------------------------------------

inline MovementType Character::GetMovementType() const
{
	return movementType;
}

// ---------------------------------------------------------------------------------

inline void Character::SetVida(int damage)
{
	vida = vida - damage;
}

// ---------------------------------------------------------------------------------

inline int Character::GetDamage() const
{
	return danoAtaque;
}

// ---------------------------------------------------------------------------------

inline int Character::MaxLife() const
{
	return maxLife;
}

// ---------------------------------------------------------------------------------

inline void Character::setIsMoving(boolean move)
{
	isMoving = move;
}

// ---------------------------------------------------------------------------------

inline float Character::GetTargetX() const
{
	return targetX;
}

// ---------------------------------------------------------------------------------

inline float Character::GetTargetY() const
{
	return targetY;
}

// ---------------------------------------------------------------------------------

inline float Character::GetPrevX() const
{
	return prevX;
}

// ---------------------------------------------------------------------------------

inline float Character::GetPrevY() const
{
	return prevY;
}

// ---------------------------------------------------------------------------------

inline float Character::GetVelX() const
{
	return VelX;       // Retorna a velocidade horizontal do inimigo
}

// ---------------------------------------------------------------------------------

inline float Character::GetVelY() const
{
	return VelY;       // Retorna a velocidade vertical do inimigo
}

// ---------------------------------------------------------------------------------

inline boolean Character::IsHit() const
{
	return isHit;
}

// ---------------------------------------------------------------------------------	

inline void Character::setXp(int xp)
{
	this->xp += xp;
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