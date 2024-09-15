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
	width = Level1::hud->tileWidth;
	height = Level1::hud->tileHeight;

	walking = new TileSet("Resources/GhostFolha.png", width * 3, height * 2,
		width, height, 3, 6);							// Cria o TileSet do Ghost
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
	MoveTo(targetX, targetY, Layer::FRONT);

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
	uint type = obj->Type();

	// Se o objeto colidido for o jogador
	if (type == PLAYER && isHit)
	{
		Character* player = (Character*)(obj);

		// Se o ghost estiver parado, o player que está atacando
		if (direction == STILL) {

			SetDamage(player->GetDamage());		// Recebe o dano do jogador
			anim->Select(ATACK);				// Seleciona a animação de dano

			// Atualiza a vida do ghost
			if (life <= 0) {
				// Morreu
				// Deleta o objeto
				Level1::scene->Delete(this, MOVING);
				player->SetXp(20 * (level));
			}

			isHit = false;
		}
		else {
			player->SetDamage(attack);			// Ataca o jogador
			Move(BACKWARD);						// Volta o fantasma
		}
	}
	else if (type == ENEMY) {
		Move(BACKWARD);
	}
}

// ---------------------------------------------------------------------------------
