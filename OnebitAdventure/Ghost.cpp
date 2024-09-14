// ---------------------------------------------------------------------------------
// Inclusões

#include "Ghost.h"
#include "OneBitAdventure.h"
#include "Character.h"
#include "Level1.h"

// ---------------------------------------------------------------------------------

// Construtor da classe Ghost, inicializa tudo especifico do Ghost
Ghost::Ghost(float col, float line)
	: Enemy() // Chamada do construtor da classe base
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

	maxLife = 5 + (10 * (level - 1));		// Vida máxima do Ghost por nível
	life = maxLife;							// Vida padrão do fastasma (Não tem na wiki informando o máximo nem quanto aumenta)
	attack = 3 + (2 * (level - 1));		// Dano de ataque de 1	(Não tem na wiki informando o máximo nem quanto aumenta)

	// Inicialize BBox após walking ser definido
	InitializeBBox();

	// Inicializa a posição
	targetX = prevX = Level1::hud->Col(col);
	targetY = prevY = Level1::hud->Line(line);
	MoveTo(targetX, targetY, Layer::MIDDLE);

	name = "Ghost";							// Nome do Ghost
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
		player->SetDamage(attack);

		if (life <= 0) {
			// Morreu
			// Deleta o objeto
			Level1::scene->Delete(this, MOVING);
			player->SetXp(20 * (level));
		}

		isHit = false;
	}
	else if (obj->Type() == ENEMY) {
		targetX = prevX;
		targetY = prevY;
	}
}

// ---------------------------------------------------------------------------------
