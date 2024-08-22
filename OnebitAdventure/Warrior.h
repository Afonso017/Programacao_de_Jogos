// ------------------------------------------------------------------------------
// Inclusões

#include "Object.h"                     // interface de Object
#include "Character.h"						// interface de Player

// ------------------------------------------------------------------------------

class Warrior : public Character
{
private:
	TileSet* walking = nullptr;         // folha de sprites do personagem
	Animation* anim = nullptr;          // animação do personagem
	
public:

	void init() override;									// inicialização
	void OnCollision(Object* obj) override;					// resolução da colisão
};

// ---------------------------------------------------------------------------------