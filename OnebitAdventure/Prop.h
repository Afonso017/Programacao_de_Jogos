// Prop.h

#pragma once
#ifndef PROP_H
#define PROP_H

// ----------------------------------------------------------------------------------
// Inclusões

#include "Object.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "OneBitAdventure.h"

// ----------------------------------------------------------------------------------

class Prop : public Object
{
private:
	Sprite* sprite = nullptr;										// Ponteiro para sprite do objeto
	Animation* anim = nullptr;										// Ponteiro para animação do objeto	(Se ele tiver uma)
	TileSet* tileSet = nullptr;										// Ponteiro para tileset do objeto	(Se ele tiver um)

public:
	static std::vector<std::string> images;							// Vetor de ponteiros para imagens que serão usadas no mapa
	bool interactable;												// Flag para indicar se o objeto é interagível

	Prop(OneBitObjects type, int imagem, float col, float line, float width, float height, bool interactable, bool bbox = true);
	~Prop();

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