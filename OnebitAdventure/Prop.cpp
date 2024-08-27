#include "Prop.h"
#include "Level1.h"

// ----------------------------------------------------------------------------------

Prop::Prop(uint type, string image, float col, float line, float width, float height, bool interactable, bool bbox) : interactable(interactable)
{
	this->type = type;

	if (type == DOOR || type == CHEST)
	{
		anim = new Animation(new TileSet(new Image(image, width * 2, height), 1, 2), 0.0f, false);

		// Sequência 0 padrão, 1 quando player interage
		anim->Add(0, new uint{ 0 }, 1);
		anim->Add(1, new uint{ 1 }, 1);
		anim->Select(0);
	}
	else sprite = new Sprite(image);

	if (interactable || bbox)
		BBox(new Rect(
			x - width / 2.4f,
			y - height / 2.3f,
			x + width / 2.4f,
			y + height / 2.3f)
		);

	MoveTo(col, line, Layer::LOWER);
}

// ----------------------------------------------------------------------------------

Prop::~Prop()
{
	if (type == DOOR || type == CHEST) {
		delete anim;
	}
	else delete sprite;
}

// ----------------------------------------------------------------------------------

void Prop::Update()
{
	// Verifica se o player passou pela porta
	if (type == DOOR && anim->Frame() == 1)
	{
		if (!Level1::hud->Collision(this, Level1::player))
		{
			// Fecha a porta
			anim->Select(0);
		}
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
