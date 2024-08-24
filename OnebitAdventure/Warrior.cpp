// ---------------------------------------------------------------------------------
// Inclus�es

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

    vida = 1;				
	danoAtaque = 2.0f;      // Dano de ataque de 2
	chanceCritica = 2.0f;   // Chance de cr�tico de 2%

    // Inicialize BBox ap�s walking ser definido
    InitializeBBox();

	// Inicializa a posi��o do Warrior
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

		//// Dist�ncia do inimigo ao player
		//float deltaX = enemy->X() - X();
		//float deltaY = enemy->Y() - Y();


		//// Calcular a dist�ncia ao quadrado (mais eficiente do que calcular a dist�ncia real)
		//float distanceSquared = deltaX * deltaX + deltaY * deltaY;

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

		// Recupera a refer�ncia ao inimigo colidido
		Enemy* enemy = (Enemy*)obj;
		float dano = danoAtaque;

		// Gera um n�mero aleat�rio entre 0 e 100
		float randomValue = static_cast<float>(rand() % 100);

		// Se o valor gerado for menor que a chance cr�tica, aplica o cr�tico
		if (randomValue < chanceCritica) {
			dano *= 2.0f; // Dano cr�tico, multiplicado por 2
		}

		// Aplica o dano ao inimigo
		enemy->SetVida(dano);

		// deveria exibir o dano, mas � t�o r�pido, que n�o aparece.
		//consolas->Draw(x, y - 10, std::to_string(dano), Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.0f, 0.0f);

		// Se a vida do personagem for menor ou igual a 0, remove-o da cena
		if (vida <= 0) {
			//Level1::scene->Delete(this, MOVING);

			Image* img = new Image("Resources/morte.png", 64, 64); // Carrega a imagem do Warrior
			walking = new TileSet(img, 64, 64, 1, 1);              // Cria o TileSet do Warrior
			anim = new Animation(walking, 0.125f, true);		   //
			isDead = true;										   // foi de base
		}

		// Evita que o Warrior continue a ser atingido at� que a pr�xima colis�o seja registrada
		isHit = false;
	}
}

// ---------------------------------------------------------------------------------