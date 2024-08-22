// ------------------------------------------------------------------------------
// Inclus�es

#include "Object.h"                     // interface de Object
#include "Character.h"						// interface de Player

// ------------------------------------------------------------------------------

class Warrior : public Character
{
private:
	TileSet* walking = nullptr;         // folha de sprites do personagem
	Animation* anim = nullptr;          // anima��o do personagem
	
public:

	void init() override;									// inicializa��o
	void OnCollision(Object* obj) override;					// resolu��o da colis�o
};

// ---------------------------------------------------------------------------------