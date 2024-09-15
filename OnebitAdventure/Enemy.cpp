// ------------------------------------------------------------------------------
// Inclus�es

#include "Enemy.h"

// ------------------------------------------------------------------------------

// Inicializa a BBox para colis�o
void Enemy::InitializeBBox()
{
    // Inicializa a BBox
    BBox(new Rect(
        x - walking->TileWidth() / 4.5f,
        y - walking->TileHeight() / 4.5f,
        x + walking->TileWidth() / 4.5f,
        y + walking->TileHeight() / 4.5f)
    );
}

// ------------------------------------------------------------------------------

// Construtor da classe Enemy
Enemy::Enemy()
    : Entity(), walking(nullptr), anim(nullptr) {

    // --------------------------------------------------------------------------------------------
    // Inicializa as vari�veis de estado do inimigo

    enemyState = WALK;            // Estado inicial do inimigo
    type = ENEMY;                 // Tipo do inimigo
	proximityThreshold = 2.0f * width;   // Dist�ncia para iniciar a persegui��o ao jogador

    // --------------------------------------------------------------------------------------------
    // Inicializa vari�veis de sprites e anima��o

    lifeSprite = new Sprite(new Image("Resources/sangue.png", 86.0f, 6.0f));
    hudLife = new Sprite(new Image("Resources/vida.png", 104.0f, 17.0f));

    // --------------------------------------------------------------------------------------------
    // Inicializa vari�veis auxiliares

    press12 = new Font("Resources/press12.png"); // Fonte para exibir texto na tela
    press12->Spacing("Resources/press12.dat");	 // Espa�amento da fonte

    // --------------------------------------------------------------------------------------------
    // Inicializa atributos b�sicos do inimigo

    level = 1;                    // N�vel do inimigo

    // (Vida e dano de ataque s�o definidos nas subclasses)

    // --------------------------------------------------------------------------------------------
}

// Destrutor da classe Enemy
Enemy::~Enemy()
{
    delete lifeSprite;
    delete hudLife;
    delete press12;
}

// ------------------------------------------------------------------------------

// Atualiza o estado do inimigo
void Enemy::Update()
{
    if (Level1::player->IsMoving())
	{
        HandleMovement();                                   // Define a dire��o de movimento
    }

	CameraMovement();									    // Atualiza a movimenta��o da c�mera
	Movement();											    // Atualiza a movimenta��o do inimigo

    ConstrainToScreen();                                    // Garante que o inimigo n�o ultrapasse os limites da tela

    // Se o inimigo est� a um bloco de dist�ncia do jogador, � exibido a vida do inimigo
    if (PlayerDistance() <= height + 2.0f)
    {
        DisplayEnemyHealth();
    }

	// Se a vida do inimigo for menor ou igual a zero ele vai de base, � deletado e o jogador ganha experi�ncia
    if (life <= 0)
    {
        // Morreu
        // Deleta o objeto
        Level1::scene->Delete(this, MOVING);
        Level1::player->SetXp(20 * (level));
    }

    UpdateAnimation();                                      // Atualiza a anima��o do inimigo
}

// ------------------------------------------------------------------------------

// Move o inimigo aleatoriamente
void Enemy::MoveRandomly() {
    int direction = rand() % 7;         // 4 dire��es poss�veis

    switch (direction) {
    case 0:
        Move(WALKRIGHT);
        break;
    case 1:
        Move(WALKLEFT);
        break;
    case 2:
        Move(WALKDOWN);
        break;
    case 3:
        Move(WALKUP);
        break;
    default:
        Move(STILL);
        break;
    }
}

// ------------------------------------------------------------------------------

// Lida com a movimenta��o do inimigo
void Enemy::HandleMovement()
{
    // Se o inimigo j� chegou ao destino anterior, ent�o, ele pode se mover novamente
    if (!isMoving)
    {
        isHit = true;   // Indica que o inimigo pode atacar o jogador
        isMoving = true;

        if (PlayerDistance() < proximityThreshold) {
            // 85% de chance de mover na dire��o do jogador
            if (rand() % 100 < 90) {
                MoveTowardsPlayer();
            }
            else {
                // 15% de chance de mover aleatoriamente
                MoveRandomly();
            }
        }
        else {
            // Se o jogador est� longe, move aleatoriamente
            MoveRandomly();
        }
    }
}

// ------------------------------------------------------------------------------

// Atualiza a anima��o do inimigo
void Enemy::UpdateAnimation()
{
    anim->Select(enemyState); // Seleciona o estado atual da anima��o
    anim->NextFrame();        // Avan�a para o pr�ximo frame da anima��o
}

// ------------------------------------------------------------------------------

// Move o inimigo em dire��o ao jogador com base nas diferen�as de posi��o
void Enemy::MoveTowardsPlayer()
{
    float deltaX = Level1::player->X() - x;
    float deltaY = Level1::player->Y() - y;

    // Se a diferen�a em X for maior que a diferen�a em Y (em valor absoluto) 
    // o inimigo se move horizontalmente, caso contr�rio, se move verticalmente
    if (abs(deltaX) > abs(deltaY)) {
        //  Move horizontalmente
        if (deltaX > 0) {    // Delta X positivo significa que o jogador est� � direita
			Move(WALKRIGHT); // Atualiza o estado do inimigo
        }
        else {               // Delta X negativo significa que o jogador est� � esquerda
			Move(WALKLEFT);  // Atualiza o estado do inimigo
        }
    }
    else {
        // Move verticalmente
        if (deltaY > 0) {    // Delta Y positivo significa que o jogador est� abaixo
            Move(WALKDOWN);
        }
        else {               // Delta Y negativo significa que o jogador est� acima
            Move(WALKUP);
        }
    }
}

// ------------------------------------------------------------------------------

void Enemy::DisplayEnemyHealth() {
    DrawHealthBar();
    DrawHealthText();
    DrawLevel();
    DrawName();
}

// ------------------------------------------------------------------------------

void Enemy::DrawHealthBar() {
    float barWidth = 86.0f;
    float barHeight = 6.0f;
    float percent = (float)life / maxLife;
    float currentWidth = barWidth * percent;
    float offset = x - (barWidth - currentWidth) / 2;

    hudLife->Draw(x, y - (45.0f + hudLife->Height()));
    lifeSprite->DrawResize(offset, y - (46.0f + hudLife->Height()), currentWidth, barHeight);
}

// ------------------------------------------------------------------------------

void Enemy::DrawHealthText() {
    std::string vidaTexto = std::to_string(life) + "/" + std::to_string(maxLife);
    press12->Draw(x - 13.0f, y - 40.0f, vidaTexto, Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 0.8f);
}

// ------------------------------------------------------------------------------

void Enemy::DrawLevel() {
    press12->Draw((x + 15) - width / 2.0f, y - 80.0f, "Nv:" + std::to_string(level), Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 0.8f);
}

// ------------------------------------------------------------------------------

void Enemy::DrawName() {
    press12->Draw(x - width / 2.0f, y - 100.0f, name, Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.0f);
}

// ------------------------------------------------------------------------------