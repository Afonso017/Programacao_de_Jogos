// ------------------------------------------------------------------------------
// Inclusões

#pragma once
#ifndef WARRIOR_H
#define WARRIOR_H

#include "Object.h"							// interface de Object
#include "Character.h"						// interface de Player		

// ------------------------------------------------------------------------------

class Warrior : public Character
{
private:
	// --------------------------------------------------------------------------------------------
	// atributos específicos do Warrior

	float chanceCritica;

	// --------------------------------------------------------------------------------------------

public:
	Warrior(float width, float height, Background* backg);
	~Warrior() override;

	void OnCollision(Object* obj) override;					// resolução de colisões
};

// ---------------------------------------------------------------------------------

#endif WARRIOR_H