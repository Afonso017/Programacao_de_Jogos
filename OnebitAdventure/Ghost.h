// ------------------------------------------------------------------------------
// Inclusões

#include "Object.h"							// interface de Object
#include "Enemy.h"							// interface de Enemy

// ---------------------------------------------------------------------------------

class Ghost : public Enemy
{
private:
	// atributos específicos do Ghost (Ghost, pelo que vi, não tem muitos atributos diferentes não!)

public:
	Ghost(float width, float height, Background* backg);
	~Ghost();

	void OnCollision(Object* obj) override;					// resolução da colisão
};