// ---------------------------------------------------------------------------------
// Inclus�es

#include "OneBitAdventure.h"
#include "Ghost.h"
#include "Level1.h"

// ---------------------------------------------------------------------------------

// Construtor da classe Ghost, inicializa tudo especifico do Ghost
Ghost::Ghost(float width, float height)
	: Enemy(width, height) // Chamada do construtor da classe base
{
	Image* img = new Image("Resources/Ghost.png", this->width * 3, this->height * 1);		// Carrega a imagem do Ghost
	walking = new TileSet(img, this->width, this->height, 3, 3);							// Cria o TileSet do Ghost
	anim = new Animation(walking, 0.125f, true);											// Cria a anima��o do Ghost

	uint Seq[3] = { 0,1,2};
	anim->Add(WALKRIGHT, Seq, 3);

	vida = 5;				// Vida padr�o do fastasma (N�o tem na wiki informando o m�ximo nem quanto aumenta)
	danoAtaque = 1.0f;      // Dano de ataque de 1	(N�o tem na wiki informando o m�ximo nem quanto aumenta)

	// Inicialize BBox ap�s walking ser definido
	InitializeBBox();

	// Inicializa a posi��o do Ghost
	MoveTo(window->CenterX(), window->CenterY() - (2.0f * height), Layer::FRONT);

	targetX = X();
	targetY = Y();
}

// ---------------------------------------------------------------------------------

Ghost::~Ghost()
{
	delete anim;
	delete walking;
}

// ---------------------------------------------------------------------------------

void Ghost::OnCollision(Object* obj)
{
	// Implemente a l�gica de resolu��o de colis�o aqui
	if (obj->Type() == PLAYER && isHit) {

		//switch (enemyState)
		//{
		//case WALKUP:						// Se o inimigo estava indo para cima inverta a dire��o
		//	targetY = targetY + VelY;
		//	enemyState = WALKDOWN;          // Move para baixo
		//	break;
		//case WALKDOWN:						// Se o inimigo estava indo para baixo inverta a dire��o
		//	targetY = targetY - VelY;
		//	enemyState = WALKUP;            // Move para cima
		//	break;
		//case WALKLEFT:						// Se o inimigo estava indo para esquerda inverta a dire��o
		//	targetX = targetX + VelX;
		//	enemyState = WALKRIGHT;         // Move para direita
		//	break;
		//case WALKRIGHT:						// Se o inimigo estava indo para direita inverta a dire��o
		//	targetX = targetX - VelX;
		//	enemyState = WALKLEFT;          // Move para esquerda
		//	break;
		//default:
		//	break;
		//}

		targetX = prevX;
		targetY = prevY;
		
		Character* player = (Character*)(obj);
		player->SetVida(danoAtaque);

		if (vida <= 0) {
			// Morreu
			// Deleta o objeto
			Level1::scene->Delete(this, MOVING);
		}

		isHit = false;
	}
}

// ---------------------------------------------------------------------------------