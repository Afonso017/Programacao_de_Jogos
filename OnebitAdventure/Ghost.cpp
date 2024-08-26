// ---------------------------------------------------------------------------------
// Inclusões

#include "OneBitAdventure.h"
#include "Ghost.h"
#include "Level1.h"

// ---------------------------------------------------------------------------------

// Construtor da classe Ghost, inicializa tudo especifico do Ghost
Ghost::Ghost(float width, float height)
	: Enemy(width, height) // Chamada do construtor da classe base
{
	Image* img = new Image("Resources/GhostFolha.png", this->width * 3, this->height * 2);	// Carrega a imagem do Ghost
	walking = new TileSet(img, this->width, this->height, 3, 6);							// Cria o TileSet do Ghost
	anim = new Animation(walking, 0.125f, true);	
	// Cria a animação do Ghost

	enemyState = WALK;	// Estado inicial do Ghost

	uint Seq1[3] = { 0,1,2};
	uint Seq2[3] = { 3,4,5 };
	anim->Add(WALK, Seq1, 3);
	anim->Add(ATACK, Seq2, 3);

	vida = 5;				// Vida padrão do fastasma (Não tem na wiki informando o máximo nem quanto aumenta)
	danoAtaque = 1;			// Dano de ataque de 1	(Não tem na wiki informando o máximo nem quanto aumenta)

	// Inicialize BBox após walking ser definido
	InitializeBBox();

	// Inicializa a posição do Ghost
	MoveTo(window->CenterX(), window->CenterY() - (4.0f * height), Layer::UPPER);

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
	// Implemente a lógica de resolução de colisão aqui
	if (obj->Type() == PLAYER && isHit) {
		//enemyState = ATACK;

		/*targetX = prevX;
		targetY = prevY;*/

		switch (direction)
		{
		case STILL:						// Se estiver parado, não faz nada
			break;
		case WALKUP:
			targetY = targetY + VelY;	// Se estiver andando para cima, volta para a posição anterior
			break;
		case WALKDOWN:
			targetY = targetY - VelY;	// Se estiver andando para baixo, volta para a posição anterior
			break;
		case WALKLEFT:
			targetX = targetX + VelX;	// Se estiver andando para a esquerda, volta para a posição anterior
			break;
		case WALKRIGHT:
			targetX = targetX - VelX;	// Se estiver andando para a direita, volta para a posição anterior
			break;
		default:
			break;
		}
		
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