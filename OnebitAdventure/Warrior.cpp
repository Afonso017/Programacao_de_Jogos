// ---------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Warrior.h"
#include "Enemy.h"
#include "Ghost.h"
#include "Sprite.h"
#include "Image.h"
#include "Animation.h"

// ---------------------------------------------------------------------------------

// Construtor da classe Warrior, inicializa tudo especifico do Warrior
Warrior::Warrior(int col, int line)
	: Character() // Chamada do construtor da classe base
{
	// Cria o TileSet do Warrior
	walking = new TileSet("Resources/WarriorSprite.png", width * 4, height * 2, 
		width, height, 4, 8);

	// Cria a animação do Warrior
	anim = new Animation(walking, 0.125f, true);

    uint SeqRight[4] = { 0,1,2,3 };
    uint SeqLeft[4] = { 4,5,6,7 };
    anim->Add(WALKLEFT, SeqRight, 4);
    anim->Add(WALKRIGHT, SeqLeft, 4);

	maxLife = 52 + (10 * (level - 1));	// Vida máxima do Warrior por nível
	life = maxLife;						// Vida padrão do Warrior
	attack = 2;							// Dano de ataque de 2
	criticalChance = 2.0f;				// Chance de crítico de 2%

    // Inicialize BBox após walking ser definido
    InitializeBBox();

	// Inicializa a posição
	targetX = prevX = Level1::hud->Col(col);
	targetY = prevY = Level1::hud->Line(line);
	MoveTo(targetX, targetY, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Warrior::~Warrior()
{
	delete anim;
	delete walking;
}

// ---------------------------------------------------------------------------------

void Warrior::OnCollision(Object* obj)
{
	uint type = obj->Type();

	// Se o objeto colidido for um inimigo
	if (type == ENEMY && isHit)
	{
		Enemy* enemy = (Enemy*)obj;

		timer->Start();			// Inicia o timer para o cálculo de tempo de exibição da mensagem!

		// Reinicia o timer de ataque
		attackTimer->Reset();	// Inicia o timer para o cálculo de tempo de pausa entre os ataques!

		// Se o player mover na direção do inimigo

		Direction enemyDirection = enemy->GetDirection();

		bool verticalCollision = direction == WALKUP || direction == WALKDOWN 
			&& enemyDirection == WALKUP || enemyDirection == WALKDOWN;
		bool horizontalCollision = direction == WALKLEFT || direction == WALKRIGHT
			&& enemyDirection == WALKLEFT || enemyDirection == WALKRIGHT;

		// O player está atacando o inimigo
		if (verticalCollision || horizontalCollision) 
		{
			int dano = attack;

			// Gera um número aleatório entre 0 e 100
			int randomValue = rand() % 100;

			// Se o valor gerado for menor que a chance crítica, aplica o crítico
			if (randomValue < criticalChance) {
				dano *= 2; // Dano crítico, multiplicado por 2
			}

			// Aplica o dano ao inimigo
			enemy->SetDamage(dano);

			// seta a mensagem de dano no unored_map
			// Dano que o personagem causou
			text.insert({ std::to_string(enemy->GetDamage()), Color(1.0f,1.0f,1.0f,1.0f) });

			// Dano que o inimigo causou
			text.insert({ std::to_string(GetDamage()), Color(1.0f, 0.0f, 0.0f, 1.0f) });
		}
		else {
			// Dano que o inimigo causou
			text.insert({ std::to_string(GetDamage()), Color(1.0f, 0.0f, 0.0f, 1.0f) });
		}

		// Evita que o Warrior continue a ser atingido até que a próxima colisão seja registrada
		isHit = false;
	}
	else if (type == COIN)
	{
		Level1::scene->Delete(obj, STATIC);
	}
	else if (type != DOOR)
	{
		// Se o objeto colidido for diferente de uma porta, o Warrior volta para a posição anterior
		Move(BACKWARD);

		if (type == BOX)
		{
			// Implementar interação com a caixa: sprite de vida e itens dropados
		}
	}
}

// ---------------------------------------------------------------------------------
