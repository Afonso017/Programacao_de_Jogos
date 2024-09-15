// Entity.h

#ifndef ENTITY_H
#define ENTITY_H

// ----------------------------------------------------------------------------------
// Inclus�es

#include "Object.h"

enum Direction // Enumera��o das dire��es de uma movimenta��o
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
	// Atributos de dimens�o e movimenta��o
	Direction direction;				// dire��o do movimento
	float width, height;				// largura e altura
	float speed;						// velocidade de movimento
	float vx;							// velocidade x
	float vy;							// velocidade y
	float targetX;						// posi��o x do destino
	float targetY;						// posi��o y do destino
	float deltaX;						// deslocamento do x at� o destino
	float deltaY;						// deslocamento do y at� o destino
	float distance;						// dist�ncia euclidiana at� o destino
	float slowDownRadius;				// raio de desacelera��o
	float newX;							// interpola��o do deltaX
	float newY;							// interpola��o do deltaY
	float prevX;						// posi��o x anterior
	float prevY;						// posi��o y anterior
	float limiar;						// posi��o do limiar
	float limiarDist;					// dist�ncia at� o limiar
	float pullStrength;					// for�a de retorno

	bool playerMoved;					// Flag para indicar se o player se moveu
	bool isHit;							// Flag para indicar se o personagem j� atacou
	bool isDead;						// Flag para indicar se o personagem est� morto
	bool isMoving;						// verifica se est� executando um movimento

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
	virtual void OnCollision(Object* obj) = 0;	// resolu��o da colis�o

	void Move(Direction direction);				// define a dire��o do pr�ximo movimento
	void Movement();							// realiza a movimenta��o da entidade
	void CameraMovement();						// realiza a movimenta��o da c�mera
	void ConstrainToScreen();					// limita a movimenta��o da entidade � tela
	
	// M�todos Get
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
