// Prop.h

#pragma once
#ifndef PROP_H
#define PROP_H

#include "Object.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "OneBitAdventure.h"

// ----------------------------------------------------------------------------------

class Prop : public Object
{
private:
	Sprite* sprite = nullptr;
	Animation* anim = nullptr;

public:
	Prop(uint type, string image, float col, float line, float width, float height, bool interactable, bool bbox = true);
	~Prop();

	bool interactable;

	void Update();
	void Draw();
	void OnCollision(Object* obj) override;
};

// ----------------------------------------------------------------------------------

inline void Prop::Draw()
{
	if (type == DOOR || type == CHEST)
		anim->Draw(x, y, z);
	else
		sprite->Draw(x, y, z);
}

// ----------------------------------------------------------------------------------

#endif // PROP_H
