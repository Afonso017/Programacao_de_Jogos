// ---------------------------------------------------------------------------------
// Inclusões

#include "Warrior.h"
#include "OneBitAdventure.h"

// ---------------------------------------------------------------------------------

Warrior::Warrior(float width, float height, Background* backg)
    : Character(width, height, backg)
{
    Image* img = new Image("Resources/WarriorSprite.png", this->width * 4, this->height * 2);
    walking = new TileSet(img, this->width, this->height, 4, 8);
    anim = new Animation(walking, 0.125f, true);

    uint SeqRight[4] = { 0,1,2,3 };
    uint SeqLeft[4] = { 4,5,6,7 };
    anim->Add(WALKRIGHT, SeqRight, 4);
    anim->Add(WALKLEFT, SeqLeft, 4);

    vida = 52;
    danoAtaque = 2.0f;
    chanceCritica = 2.0f;   

    // Inicialize BBox após walking ser definido
    InitializeBBox();
}

Warrior::~Warrior()
{
	delete walking;
	delete anim;
	delete backg;
}

void Warrior::OnCollision(Object* obj)
{
	// Implemente a lógica de resolução de colisão aqui
}

// ---------------------------------------------------------------------------------