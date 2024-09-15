// Entity.h

#ifndef ENTITY_H
#define ENTITY_H

// ----------------------------------------------------------------------------------
// Inclusões

#include "Object.h"

enum Direction // Enumeração das direções de uma movimentação
{
	STILL,
	WALKUP,
	WALKDOWN,
	WALKLEFT,
	WALKRIGHT,
	BACKWARD
};

class Entity : public Object
{
protected:
	// Atributos de dimensão e movimentação
	Direction direction;				// direção do movimento
	float width, height;				// largura e altura
	float speed;						// velocidade de movimento
	float vx;							// velocidade x
	float vy;							// velocidade y
	float targetX;						// posição x do destino
	float targetY;						// posição y do destino
	float deltaX;						// deslocamento do x até o destino
	float deltaY;						// deslocamento do y até o destino
	float distance;						// distância euclidiana até o destino
	float slowDownRadius;				// raio de desaceleração
	float newX;							// interpolação do deltaX
	float newY;							// interpolação do deltaY
	float prevX;						// posição x anterior
	float prevY;						// posição y anterior
	float limiar;						// posição do limiar
	float limiarDist;					// distância até o limiar
	float pullStrength;					// força de retorno

	bool playerMoved;					// Flag para indicar se o player se moveu
	bool isHit;							// Flag para indicar se o personagem já atacou
	bool isDead;						// Flag para indicar se o personagem está morto
	bool isMoving;						// verifica se está executando um movimento

	// Atributos de combate
	int maxLife;
	int life;
	int attack;
	int defense;
	int damage;

public:
	Entity();
	~Entity();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void OnCollision(Object* obj) = 0;	// resolução da colisão

	void Move(Direction direction);				// define a direção do próximo movimento
	void Movement();							// realiza a movimentação da entidade
	void CameraMovement();						// realiza a movimentação da câmera
	void ConstrainToScreen();					// limita a movimentação da entidade à tela
	
	// Métodos Get
	bool IsMoving() const;
	float GetTargetX() const;
	float GetTargetY() const;
	float GetPrevX() const;
	float GetPrevY() const;
	int GetLife() const;
	int GetMaxLife() const;
	int GetDamage() const;						// retorna dano recebido
	Direction GetDirection() const;

	void SetDamage(int damage);					// recebe o dano e atualiza a vida
};

// ----------------------------------------------------------------------------------

inline bool Entity::IsMoving() const
{
	return isMoving;
}

inline float Entity::GetTargetX() const
{
	return targetX;
}

inline float Entity::GetTargetY() const
{
	return targetY;
}

inline float Entity::GetPrevX() const
{
	return prevX;
}

inline float Entity::GetPrevY() const
{
	return prevY;
}

inline int Entity::GetLife() const
{
	return life;
}

inline int Entity::GetMaxLife() const
{
	return maxLife;
}

inline int Entity::GetDamage() const
{
	return damage;
}

inline Direction Entity::GetDirection() const
{
	return direction;
}

inline void Entity::SetDamage(int damage)
{
	this->damage = damage - defense;
	if (this->damage > 0)
		life -= this->damage;
}

// ---------------------------------------------------------------------------------

#endif // ENTITY_H
