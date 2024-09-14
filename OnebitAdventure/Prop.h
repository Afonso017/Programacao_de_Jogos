// Prop.h

#ifndef PROP_H
#define PROP_H

// ----------------------------------------------------------------------------------
// Inclusões

#include "Entity.h"
#include "Image.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "OneBitAdventure.h"

// ----------------------------------------------------------------------------------

class Prop : public Entity
{
private:
	Sprite* sprite = nullptr;										// Ponteiro para sprite do objeto
	Animation* anim = nullptr;										// Ponteiro para animação do objeto	(Se ele tiver uma)
	TileSet* tileSet = nullptr;										// Ponteiro para tileset do objeto	(Se ele tiver um)

public:
	bool interactable;												// Flag para indicar se o objeto é interagível

	Prop(uint type, Image * image, float col, float line, bool interactable, bool bbox = true);
	~Prop();

	void Update();
	void Draw();
	void OnCollision(Object* obj) override;
};

// ----------------------------------------------------------------------------------

inline void Prop::Draw()
{
	if (type == DOOR || type == CHEST || type == CAMPFIRE)
		anim->Draw(x, y, z);
	else
		sprite->Draw(x, y, z);
}

// ----------------------------------------------------------------------------------

#endif // PROP_H
