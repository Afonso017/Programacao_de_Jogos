// Prop.h

#ifndef PROP_H
#define PROP_H

#include "Object.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"

// ----------------------------------------------------------------------------------

class Prop : public Object
{
private:
	Sprite * sprite = nullptr;
	TileSet * tileSet = nullptr;		// alguns props como porta e baú tem mais de um sprite
	Animation * anim = nullptr;

public:
	Prop(string path, float x, float y, float width, float height, bool interactable, bool bbox = true);
	Prop(Image * image, float x, float y, float width, float height, bool interactable, bool bbox = true);
	~Prop();

	void Update();
	void Draw();
};

// ----------------------------------------------------------------------------------

inline void Prop::Draw()
{
	sprite->Draw(x, y, Layer::MIDDLE);
}

// ----------------------------------------------------------------------------------

#endif // PROP_H
