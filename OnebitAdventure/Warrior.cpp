// ---------------------------------------------------------------------------------
// Inclus�es

#include "Warrior.h"
#include "OneBitAdventure.h"

// ---------------------------------------------------------------------------------

// Construtor da classe Warrior, inicializa tudo especifico do Warrior
Warrior::Warrior(float width, float height, Background* backg) 
	: Character(width, height, backg) // Chamada do construtor da classe base
{
	Image* img = new Image("Resources/WarriorSprite.png", this->width * 4, this->height * 2); // Carrega a imagem do Warrior
	walking = new TileSet(img, this->width, this->height, 4, 8);                              // Cria o TileSet do Warrior
    anim = new Animation(walking, 0.125f, true);

    uint SeqRight[4] = { 0,1,2,3 };
    uint SeqLeft[4] = { 4,5,6,7 };
    anim->Add(WALKRIGHT, SeqRight, 4);
    anim->Add(WALKLEFT, SeqLeft, 4);

    vida = 52;				
	danoAtaque = 2.0f;      // Dano de ataque de 2
	chanceCritica = 2.0f;   // Chance de cr�tico de 2%

    // Inicialize BBox ap�s walking ser definido
    InitializeBBox();

	// Inicializa a posi��o do Warrior
	MoveTo(window->CenterX(), window->CenterY(), Layer::FRONT);

	targetX = X();
	targetY = Y();
}

Warrior::~Warrior()
{
	delete walking;
	delete anim;
}

void Warrior::OnCollision(Object* obj)
{
	// Implemente a l�gica de resolu��o de colis�o aqui
}

// ---------------------------------------------------------------------------------