#include "Prop.h"
#include "Level1.h"

// ----------------------------------------------------------------------------------

// Inicialização do vetor estático fora da classe
std::vector<std::string> Prop::images = {
	"Resources/Props/grass.png",
	"Resources/Props/wall.png",
	"Resources/Props/coin.png",
	"Resources/Props/door.png",
	"Resources/Props/tree.png",
	"Resources/Props/tree2.png",
	"Resources/Props/chest.png",
	"Resources/Props/campfire.png",
	"Resources/Props/fence.png",
	"Resources/Props/pilar.png",
	"Resources/Props/pilar2.png",
};

// ----------------------------------------------------------------------------------

Prop::Prop(OneBitObjects type, int indexImage, float col, float line, float width, float height, bool interactable, bool bbox)
{
	this->type = type;
	this->interactable = interactable;

	if (type == DOOR || type == CHEST)
	{
		Image* image = new Image(images[indexImage], width * 2, height);
		tileSet = new TileSet(image, width, height, 2, 2);
		anim = new Animation(tileSet, 0.0f, false);

		uint seq1[1] = { 0 };
		uint seq2[1] = { 1 };

		// Sequência 0 padrão, 1 quando player interage
		anim->Add(0, seq1, 1); // Estava disperdiçando memória!
		anim->Add(1, seq2, 1);
		anim->Select(0);
	}
	else {
		sprite = new Sprite(images[indexImage]);
	}

	if (type == PILLAR) {
		BBox(new Rect(
			x - width / 2.4f,
			y - 90 / 1.0f,
			x + width / 2.4f,
			y + 90 / 1.0f)
		);
	} else if (interactable || bbox) {
		BBox(new Rect(
			x - width / 2.4f,
			y - height / 2.3f,
			x + width / 2.4f,
			y + height / 2.3f)
		);
	}

	MoveTo(col, line, Layer::LOWER);
}

// ----------------------------------------------------------------------------------

Prop::~Prop()
{
	if (sprite != nullptr) delete sprite;
	if (anim != nullptr) delete anim;
	if (tileSet != nullptr) delete tileSet;

	// images não precisa ser deletado, pois é um vetor estático e será deletado automaticamente ao final do programa
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
