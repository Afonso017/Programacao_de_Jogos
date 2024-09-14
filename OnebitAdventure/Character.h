// Character.h

#ifndef CHARACTER_H
#define CHARACTER_H

// ------------------------------------------------------------------------------

#include "Types.h"
#include "Entity.h"
#include "Animation.h"
#include "OneBitAdventure.h"
#include "Font.h"
#include <string>
#include <unordered_map>

// ------------------------------------------------------------------------------
// Classe Character : É a classe base para todos os personagens (classes) do jogo

class Character : public Entity
{
protected:
	// --------------------------------------------------------------------------------------------
	// Estados do jogador

	MovementType movementType;			// Próxima animação a ser executada
	DirectingAnimation characterState;	// estado atual do jogador
	DirectingAnimation direction;		// direção do jogador
	DirectingAnimation nextMove;		// próxima direção do jogador
	bool isHit;							// Flag para indicar se o personagem já atacou
	bool isDead;						// Flag para indicar se o personagem está morto
	bool isMoving;						// verifica se o personagem está se movendo
	bool isMovingUp;					// verifica se o personagem está se movendo para cima
	float movementTime;					// tempo de movimento do jogador
	float slowDownRadius;				// raio de desaceleração
	int progress;
	int coins;

	// --------------------------------------------------------------------------------------------
	// Atributos de sprites e animação

	TileSet* walking = nullptr;         // folha de sprites do personagem
	Animation* anim = nullptr;          // animação do personagem

	// --------------------------------------------------------------------------------------------
	// Objetos auxiliares para construções de lógicas

	std::unordered_map<string, Color> text;  // unordered_map para armazenar o texto a ser exibido na tela
	Timer* timer;						// timer para controlar o tempo de exibição do texto
	Font* press12;						// fonte para exibir texto na tela
	Timer* speedMovement;				// timer para controlar a velocidade de movimento do jogador
	Timer* attackTimer;					// timer para controlar o tempo de ataque do jogador
	Sprite* xpBar;						// sprite para representar a experiência do jogador
	Timer* stillTimer;					// timer para controlar o tempo de pausa

	//--------------------------------------------------------------------------------------------
	// Atributos básicos de todo jogador

	int level;							// nível do jogador
	int xp;								// experiência do jogador
	int maxXp;							// experiência máxima do jogador
	float criticalChance;				// chance de crítico

	// --------------------------------------------------------------------------------------------
	// Métodos protegidos 

	void InitializeBBox();										// inicializa a BBox

public:
	Character();												// construtor
	virtual ~Character();										// destrutor

	//--------------------------------------------------------------------------------------------
	// Métodos de movimentação e animação

	void HandleInput();							// movimentação do jogador
	//void SetMovementDirection(DirectingAnimation newDirection, DirectingAnimation newAnimation, float deltaX, float deltaY); // seta a direção do jogador
	//void InterpolateMovement(float gameTime);	// interpolação do movimento do jogador
	//void UpdateAnimation();						// atualiza a animação do jogador
	void ConstrainToScreen();					// limita o jogador a tela
	//void BackMovement();						// lógica de movimento de recuo do jogador

	//--------------------------------------------------------------------------------------------
	// Métodos de recuperação e modificação de atributos

	void SetXp(int xp);										// seta a experiência do jogador
	DirectingAnimation GetDirection() const;				// retorna a direção do jogador
	void SetIsMoving(boolean move);							// seta se o personagem está se movendo
	boolean IsHit() const;									// verifica se o personagem foi atingido
	MovementType GetMovementType() const;					// retorna o tipo de movimento do jogador
	void SetMovementType(MovementType newMovementType);		// seta o tipo de movimento do jogador
	void AdjustMovement();
	void NextMove();

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

inline DirectingAnimation Character::GetDirection() const
{
	return direction;
}

inline void Character::SetMovementType(MovementType newMovementType)
{
	movementType = newMovementType;
}

inline MovementType Character::GetMovementType() const
{
	return movementType;
}

inline void Character::SetIsMoving(boolean move)
{
	isMoving = move;
}

inline boolean Character::IsHit() const
{
	return isHit;
}

inline void Character::SetXp(int xp)
{
	this->xp += xp;
}

// -----------------------------------------------------------------------------

#endif // CHARACTER_H
