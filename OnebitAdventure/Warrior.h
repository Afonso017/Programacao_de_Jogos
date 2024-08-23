// ------------------------------------------------------------------------------
// Inclusões

#include "Object.h"							// interface de Object
#include "Character.h"						// interface de Player

// ------------------------------------------------------------------------------

class Warrior : public Character
{
private:
	// atributos específicos do Warrior
	float chanceCritica;

public:
	Warrior(float width, float height, Background* backg);
	~Warrior();

	void OnCollision(Object* obj) override;					// resolução da colisão
};

// ---------------------------------------------------------------------------------