// ---------------------------------------------------------------------------------
// Inclus�es

#include "OneBitAdventure.h"
#include "Ghost.h"

// ---------------------------------------------------------------------------------

// Construtor da classe Ghost, inicializa tudo especifico do Ghost
Ghost::Ghost(float width, float height, Background* backg)
	: Enemy(width, height, backg) // Chamada do construtor da classe base
{
	Image* img = new Image("Resources/Ghost.png", this->width * 3, this->height * 1);		// Carrega a imagem do Ghost
	walking = new TileSet(img, this->width, this->height, 3, 3);  // Cria o TileSet do Ghost
	anim = new Animation(walking, 0.125f, true);

	uint Seq[3] = { 0,1,2};
	anim->Add(WALKRIGHT, Seq, 3);

	vida = 5;				// Vida padr�o do fastasma (N�o tem na wiki informando o m�ximo nem quanto aumenta)
	danoAtaque = 1.0f;      // Dano de ataque de 1	(N�o tem na wiki informando o m�ximo nem quanto aumenta)

	// Inicialize BBox ap�s walking ser definido
	InitializeBBox();

	// Inicializa a posi��o do Ghost
	MoveTo(window->CenterX(), window->CenterY(), Layer::FRONT);

	targetX = X();
	targetY = Y();
}

// ---------------------------------------------------------------------------------

Ghost::~Ghost()
{
	delete walking;
	delete anim;
}

// ---------------------------------------------------------------------------------

void Ghost::OnCollision(Object* obj)
{
	// Implemente a l�gica de resolu��o de colis�o aqui
}

// ---------------------------------------------------------------------------------