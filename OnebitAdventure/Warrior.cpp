// ---------------------------------------------------------------------------------
// Inclus�es

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
	Image* img = new Image("Resources/WarriorSprite.png", (uint)width * 4, (uint)height * 2); // Carrega a imagem do Warrior
	walking = new TileSet(img, (uint)width, (uint)height, 4, 8);                              // Cria o TileSet do Warrior
	anim = new Animation(walking, 0.125f, true);											  // Cria a anima��o do Warrior

    uint SeqRight[4] = { 0,1,2,3 };
    uint SeqLeft[4] = { 4,5,6,7 };
    anim->Add(WALKLEFT, SeqRight, 4);
    anim->Add(WALKRIGHT, SeqLeft, 4);

	maxLife = 52 + (10 * (level - 1));	// Vida m�xima do Warrior por n�vel
	life = maxLife;						// Vida padr�o do Warrior
	attack = 2;							// Dano de ataque de 2
	criticalChance = 2.0f;				// Chance de cr�tico de 2%

    // Inicialize BBox ap�s walking ser definido
    InitializeBBox();

	// Inicializa a posi��o
	targetX = prevX = Level1::hud->Col(col);
	targetY = prevY = Level1::hud->Line(line);
	MoveTo(targetX, targetY, Layer::MIDDLE);
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
	Enemy* enemy = (Enemy*)obj;
	uint type = obj->Type();

	if (type == ENEMY && isHit) {

		timer->Start();			// Inicia o timer para o c�lculo de tempo de exibi��o da mensagem!

		// Reinicia o timer de ataque
		attackTimer->Reset();
		attackTimer->Stop();
		attackTimer->Start();	// Inicia o timer para o c�lculo de tempo de pausa entre os ataques!

		int EnemyX = enemy->GetPrevX();
		int EnemyY = enemy->GetPrevY();
		int PlayerX = targetX;
		int PlayerY = targetY;

		// Se o player vai para a posi��o anterior do inimigo, ele ataca o inimigo e vice-versa
		if (PlayerX == EnemyX && PlayerY == EnemyY) {

			SetMovementType(BACK);

			// Recupera a refer�ncia ao inimigo colidido
			int dano = attack;

			// Gera um n�mero aleat�rio entre 0 e 100
			int randomValue = rand() % 100;

			// Se o valor gerado for menor que a chance cr�tica, aplica o cr�tico
			if (randomValue < criticalChance) {
				dano *= 2; // Dano cr�tico, multiplicado por 2
			}

			// Aplica o dano ao inimigo
			enemy->SetDamage(dano);

			// seta a mensagem de dano no unored_map
			// Dano que o personagem causou
			text.insert({ std::to_string((int)dano), Color(1.0f,1.0f,1.0f,1.0f) });

			// Dano que o inimigo causou
			text.insert({ std::to_string((int)enemy->GetDamage()), Color(1.0f, 0.0f, 0.0f, 1.0f) });
		}
		else {
			// Se o player n�o vai para a posi��o anterior do inimigo, ele � atingido pelo inimigo
			SetMovementType(WALK);
			// Dano que o inimigo causou
			text.insert({ std::to_string((int)enemy->GetDamage()), Color(1.0f, 0.0f, 0.0f, 1.0f) });
		}

		// Evita que o Warrior continue a ser atingido at� que a pr�xima colis�o seja registrada
		isHit = false;

		// Se a vida do personagem for menor ou igual a 0, remove-o da cena
		if (life <= 0) {

			Image* img = new Image("Resources/morte.png", 64, 64); // Carrega a imagem do Warrior
			walking = new TileSet(img, 64, 64, 1, 1);              // Cria o TileSet do Warrior
			anim = new Animation(walking, 0.125f, true);		   //
			isDead = true;										   // foi de base
		}
	}
	else if (type == COIN)
	{
		Level1::scene->Delete(obj, STATIC);
	}
	else if (type != DOOR)
	{
		targetX = prevX;
		targetY = prevY;

		if (type == BOX)
		{
			// Implementar intera��o com a caixa: sprite de vida e itens dropados
		}
	}
}

// ---------------------------------------------------------------------------------
