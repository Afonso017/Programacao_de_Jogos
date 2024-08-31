// ---------------------------------------------------------------------------------
// Inclusões

#include "OneBitAdventure.h"
#include "Ghost.h"
#include "Level1.h"
#include "Prop.h"

// ---------------------------------------------------------------------------------

// Construtor da classe Ghost, inicializa tudo especifico do Ghost
Ghost::Ghost(float width, float height, float col, float line)
	: Enemy(width, height) // Chamada do construtor da classe base
{
	Image* img = new Image("Resources/GhostFolha.png", this->width * 3, this->height * 2);	// Carrega a imagem do Ghost
	walking = new TileSet(img, this->width, this->height, 3, 6);							// Cria o TileSet do Ghost
	anim = new Animation(walking, 0.145f, true);
	// Cria a animação do Ghost

	enemyState = WALK;						// Estado inicial do Ghost

	uint Seq1[3] = { 0,1,2 };
	uint Seq2[3] = { 3,4,5 };
	anim->Add(WALK, Seq1, 3);
	anim->Add(ATACK, Seq2, 3);

	vidaMax = 5 + (10 * (level - 1));		// Vida máxima do Ghost por nível
	vida = vidaMax;							// Vida padrão do fastasma (Não tem na wiki informando o máximo nem quanto aumenta)
	danoAtaque = 3 + (2 * (level - 1));		// Dano de ataque de 1	(Não tem na wiki informando o máximo nem quanto aumenta)

	// Inicialize BBox após walking ser definido
	InitializeBBox();

	MoveTo(col, line, Layer::UPPER);

	name = "Ghost";							// Nome do Ghost

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

	if (obj->Type() == PLAYER && isHit) { // Se o objeto colidido for o jogador, ataca o jogador e volta para trás
		anim->Select(ATACK);

		targetX = prevX;
		targetY = prevY;

		Character* player = (Character*)(obj);
		player->SetVida(danoAtaque);

		if (vida <= 0) {
			// Morreu
			// Deleta o objeto
			Level1::scene->Delete(this, MOVING);
			player->setXp(20 * (level));
		}

		isHit = false;
	}
	else if (obj->Type() == ENEMY) {
		targetX = prevX;
		targetY = prevY;
	}
}

// ---------------------------------------------------------------------------------