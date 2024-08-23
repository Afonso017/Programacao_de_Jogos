// ------------------------------------------------------------------------------
// Inclus�es

#include "Object.h"							// interface de Object
#include "Character.h"						// interface de Player		

// ------------------------------------------------------------------------------

class Warrior : public Character
{
private:
	// atributos espec�ficos do Warrior
	float chanceCritica;

public:
	Warrior(float width, float height, Background* backg);
	~Warrior() override;

	void OnCollision(Object* obj) override;					// resolu��o da colis�o
};

// ---------------------------------------------------------------------------------