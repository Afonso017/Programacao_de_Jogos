// Entity.h

#ifndef ENTITY_H
#define ENTITY_H

// ----------------------------------------------------------------------------------
// Inclusões

#include "Object.h"
#include "Timer.h"

class Entity : public Object
{
protected:
	// Atributos de dimensão e movimentação
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
	virtual void OnCollision(Object* obj) = 0;	// resolução da colisão

	void Movement();							// movimentação da entidade
	void CameraMovement();						// movimentação da câmera
	
	// Métodos Get
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
