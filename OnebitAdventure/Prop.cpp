#include "Prop.h"
#include "Level1.h"

// ----------------------------------------------------------------------------------

Prop::Prop(uint type, Image* image, float col, float line, bool interactable, bool bbox)
	: Entity(), interactable(interactable)
{
	this->type = type;

	uint width, height;

	if (type == DOOR || type == CHEST)
	{
		width = image->Width() / 2;
		height = image->Height();

		tileSet = new TileSet(image, width, height, 2, 2, false);
		anim = new Animation(tileSet, 0.0f, false);

		uint seq1[1] = { 0 };
		uint seq2[1] = { 1 };

		// Sequência 0 padrão, 1 quando player interage
		anim->Add(0, seq1, 1);
		anim->Add(1, seq2, 1);
		anim->Select(0);
	}
	else if (type == CAMPFIRE)
	{
		width = image->Width() / 2;
		height = image->Height();

		tileSet = new TileSet(image, width, height, 2, 2, false);
		anim = new Animation(tileSet, 1.0f, true);
	}
	else {
		sprite = new Sprite(image);
		width = sprite->Width();
		height = sprite->Height();
	}

	if (bbox)
	{
		BBox(new Rect(
			x - width / 2.4f,
			y - height / 2.3f,
			x + width / 2.4f,
			y + height / 2.3f)
		);
	}

	if (type == PILLAR)
	{
		MoveTo(col, line, Layer::MIDDLE - 0.1f);
		targetX = prevX = line = x;
		targetY = prevY = col = y;
	}
	else
	{
		MoveTo(col, line, Layer::LOWER);
		targetX = prevX = line = x;
		targetY = prevY = col = y;
	}
}

// ----------------------------------------------------------------------------------

Prop::~Prop()
{
	if (sprite) delete sprite;
	if (anim) delete anim;
	if (tileSet) delete tileSet;
}

// ----------------------------------------------------------------------------------

void Prop::Update()
{
	Entity::CameraMovement();

	// Verifica se o player passou pela porta
	if (type == DOOR && anim->Frame() == 1)
	{
		if (!Level1::hud->Collision(this, Level1::player))
		{
			// Fecha a porta
			anim->Select(0);
		}
	}

	if (type == CAMPFIRE)
	{
		anim->NextFrame();
	}
}

// ----------------------------------------------------------------------------------

void Prop::OnCollision(Object* obj)
{
	if (!interactable) return;
	if (type == DOOR || type == CHEST)
	{
		// Se player interagir com a porta
		if (obj->Type() == PLAYER)
		{
			// Se a porta estiver fechada
			if (anim->Frame() == 0)
			{
				// Abre a porta
				anim->Select(1);
			}
		}
	}
}

// ----------------------------------------------------------------------------------
