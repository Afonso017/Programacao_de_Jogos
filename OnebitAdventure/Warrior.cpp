// ---------------------------------------------------------------------------------
// Inclusões

#include "Warrior.h"
#include "Enemy.h"
#include "Ghost.h"
#include "Level1.h"

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
	chanceCritica = 2.0f;   // Chance de crítico de 2%

    // Inicialize BBox após walking ser definido
    InitializeBBox();

	// Inicializa a posição do Warrior
	MoveTo(window->CenterX(), window->CenterY(), Layer::FRONT);

	targetX = X();
	targetY = Y();
}

// ---------------------------------------------------------------------------------

Warrior::~Warrior()
{
	delete walking;
	delete anim;
}

// ---------------------------------------------------------------------------------

void Warrior::OnCollision(Object* obj)
{
	if (obj->Type() == ENEMY && isHit) {

		Enemy* enemy = (Enemy*)obj;
		vida -= enemy->GetDamage();

		// Distância do inimigo ao player
		float deltaX = enemy->X() - X();
		float deltaY = enemy->Y() - Y();


		// Calcular a distância ao quadrado (mais eficiente do que calcular a distância real)
		float distanceSquared = deltaX * deltaX + deltaY * deltaY;

		switch (direction)
		{
		case WALKUP:
			targetY = prevY;
			break;
		case WALKDOWN:
			targetY = prevY;
			break;
		case WALKLEFT:
			targetX = prevX;
			break;
		case WALKRIGHT:
			targetX = prevX;
			break;
		default:
			break;
		}


		if (vida <= 0) {
			Level1::scene->Delete(this, MOVING);
		}

		isHit = false;
	}
}

// ---------------------------------------------------------------------------------