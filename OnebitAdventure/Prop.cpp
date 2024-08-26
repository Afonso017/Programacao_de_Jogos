#include "Prop.h"

// ----------------------------------------------------------------------------------

Prop::Prop(string path, float x, float y, float width, float height, bool interactable, bool bbox)
{
	sprite = new Sprite(new Image(path, width, height));

	MoveTo(x, y, Layer::MIDDLE);

	if (interactable || bbox)
		BBox(new Rect(x - sprite->Width() / 5.0f, y - sprite->Height() / 5.0f,
			x + sprite->Width() / 5.0f, y + sprite->Height() / 5.0f));
}

// ----------------------------------------------------------------------------------

Prop::Prop(Image * image, float x, float y, float width, float height, bool interactable, bool bbox)
{
	//image->Resize(width, height);
	sprite = new Sprite(image);

	MoveTo(x, y, Layer::MIDDLE);

	if (interactable || bbox)
		BBox(new Rect(x - sprite->Width() / 5.0f, y - sprite->Height() / 5.0f,
			x + sprite->Width() / 5.0f, y + sprite->Height() / 5.0f));
}

// ----------------------------------------------------------------------------------

Prop::~Prop()
{
	delete sprite;
}

// ----------------------------------------------------------------------------------

void Prop::Update()
{
}

// ----------------------------------------------------------------------------------
