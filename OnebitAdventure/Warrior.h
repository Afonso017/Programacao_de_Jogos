// ------------------------------------------------------------------------------
// Inclusões

#ifndef WARRIOR_H
#define WARRIOR_H

#include "Object.h"						// interface de Object
#include "Character.h"					// interface de Player

// ------------------------------------------------------------------------------

class Warrior : public Character
{
public:
	Warrior(int col, int line);
	~Warrior() override;

	void OnCollision(Object* obj) override;					// resolução de colisões
};

// ---------------------------------------------------------------------------------

#endif // WARRIOR_H
