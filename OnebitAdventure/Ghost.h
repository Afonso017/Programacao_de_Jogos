// ------------------------------------------------------------------------------
// Inclus�es

#ifndef GHOST_H
#define GHOST_H

#include "Object.h"							// interface de Object
#include "Enemy.h"							// interface de Enemy

// ---------------------------------------------------------------------------------

class Ghost : public Enemy
{
private:
	// atributos espec�ficos do Ghost (Ghost, pelo que vi, n�o tem muitos atributos diferentes n�o!)

public:
	Ghost(float col, float line);
	~Ghost() override;

	void OnCollision(Object* obj) override;					// resolu��o da colis�o
};

// ---------------------------------------------------------------------------------

#endif // GHOST_H
