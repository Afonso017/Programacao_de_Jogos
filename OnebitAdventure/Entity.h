// Entity.h

#ifndef ENTITY_H
#define ENTITY_H

// ----------------------------------------------------------------------------------
// Inclus�es

#include "Object.h"
#include "Timer.h"

class Entity : public Object
{
protected:
	// Atributos de dimens�o e movimenta��o
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
	bool isMoving;

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

	void Movement();							// movimenta��o da entidade
	void CameraMovement();						// movimenta��o da c�mera
	
	// M�todos Get
	float GetTargetX() const;
	float GetTargetY() const;
	float GetPrevX() const;
	float GetPrevY() const;
	int GetLife() const;
	int GetMaxLife() const;
	int GetDamage() const;						// retorna dano recebido

	void SetDamage(int damage);					// recebe o dano e atualiza a vida
};

// ----------------------------------------------------------------------------------

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

inline void Entity::SetDamage(int damage)
{
	this->damage = damage - defense;
	if (this->damage > 0)
		life -= this->damage;
}

// ---------------------------------------------------------------------------------

#endif // ENTITY_H
